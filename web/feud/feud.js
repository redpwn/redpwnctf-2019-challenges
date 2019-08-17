const crypto = require('crypto')
const http = require('http')
const getRawBody = require('raw-body')
const B2 = require('backblaze-b2')
const keys = require('./keys')

const puppeteer = require('puppeteer')

const restaurants = new Map()

const b2 = new B2({
  applicationKeyId: keys.b2Id,
  applicationKey: keys.b2Key,
})

const makeId = () => crypto.randomBytes(16).toString('hex')

let uploadTokens

const getUploadTokens = async () => {
  await b2.authorize()
  const { status: urlStatus, data: urlData } = await b2.getUploadUrl({
    bucketId: '1b6aacf1736556e360c10e11',
  })
  if (urlStatus !== 200) {
    throw new Error()
  }
  uploadTokens = urlData
}

const singleRestaurantPage = `
<!doctype html>
<h1 id=namei></h1>
<img id=image>
<div><a id=order><button>ORDER NOW!!1</button></a></div>
<br><br><br><a href="/submit">submit your URL to the admin</a>
<script>
  (async () => {
    const restaurantId = (new URLSearchParams(location.search)).get('id')
    const res = await fetch('/api/restaurants/' + restaurantId + '.json')
    if (res.headers.get('content-type') !== 'application/json') {
      return
    }
    const body = await res.json()
    if (body.error !== undefined) {
      alert('error: ' + body.error)
    } else {
      namei.textContent = body.data.name
      image.src = '/api/images/image%252Fpng/' + body.data.imageId,
      order.href = body.data.orderUrl
    }
  })()
</script>
`

const makeRestaurantPage = `
<!doctype html>
<h1>make restaurant</h1>
<div>name: <input id=namei type=text></div>
<div>restaurant image (max 1MB, PNG only): <input id=image type=file accept="image/png"></div>
<div><button id=submit>make restaurant</button></div>
<span id=msg></span>
<br><br><br><a href="/submit">submit your URL to the admin</a>
<script>
  submit.addEventListener('click', () => {
    if (namei.value.length === 0) {
      alert('no name')
      return
    }
    if (image.files.length === 0) {
      alert('no file selected')
      return
    }
    const fr = new FileReader()
    fr.addEventListener('load', async () => {
      msg.textContent = 'loading...'
      const res1 = await (await fetch('/api/images', {
        method: 'POST',
        body: fr.result,
      })).json()
      if (res1.error !== undefined) {
        msg.textContent = ''
        alert('error: ' + res1.error)
      } else {
        const res2 = await (await fetch('/api/restaurants', {
          method: 'POST',
          body: JSON.stringify({
            name: namei.value,
            imageId: res1.data.id,
          }),
        })).json()
        if (res2.error !== undefined) {
          msg.textContent = ''
          alert('error: ' + res2.error)
        } else {
          location = '/restaurants?id=' + res2.data.id
        }
      }
    })
    fr.readAsArrayBuffer(image.files[0])
  })
</script>
`

const orderPage = `
<!doctype html>
<h1>sadly, ordering is not implemented yet</h1>
<br><br><br><a href="/submit">submit your URL to the admin</a>
`

const submitPage = `
<!doctype html>
<h1>have the admin visit a URL</h1>
<div>enter url here: <input id=url type=text></div>
<button id=submit>submit!</button>
<script>
  submit.addEventListener('click', async () => {
    const res = await (await fetch('/api/submit', {
      method: 'POST',
      body: JSON.stringify({
        url: url.value,
      })
    })).json()
    if (res.error !== undefined) {
      alert('error: ' + res.error)
    } else {
      document.body.textContent = res.data.msg
    }
  })
</script>
`

const browser = puppeteer.launch({
  args: ['--no-sandbox', '--disable-setuid-sandbox'],
})

http.createServer((req, res) => {
  const respondGood = json => {
    res.writeHead(200, {
      'content-type': 'application/json',
    })
    res.end(JSON.stringify({
      data: json,
    }))
  }
  const respondBad = (code, error) => {
    res.writeHead(code, {
      'content-type': 'application/json',
    })
    res.end(JSON.stringify({
      error,
    }))
  }
  if (req.url.startsWith('/api/restaurants/') && req.url.endsWith('.json') && req.method === 'GET') {
    const restaurantId = decodeURIComponent(req.url.replace('/api/restaurants/', '').slice(0, -5))
    const restaurant = restaurants.get(restaurantId)
    if (restaurant === undefined) {
      respondBad(404, 'restaurant not found')
      return
    }
    respondGood({
      name: restaurant.name,
      imageId: restaurant.imageId,
      orderUrl: '/order/' + restaurantId,
    })
  } else if (req.url === '/api/restaurants' && req.method === 'POST') {
    getRawBody(req, {
      limit: '1mb',
    }, (err, body) => {
      if (err !== null) {
        respondBad(400, 'request body error')
        return
      }
      let name, imageId
      try {
        ({ name, imageId } = JSON.parse(body))
      } catch (e) {
        respondBad(400, 'bad json')
        return
      }
      if (typeof name != 'string' || typeof imageId !== 'string') {
        respondBad(400, 'bad attributes')
        return
      }
      const restarurantId = makeId()
      restaurants.set(restarurantId, {
        name,
        imageId,
      })
      respondGood({
        id: restarurantId,
      })
    })
  } else if (req.url.startsWith('/api/images/') && req.method === 'GET') {
    const imageId = decodeURIComponent(req.url.replace('/api/images/', ''))
    res.writeHead(302, {
      location: 'https://web4.2019.redpwn.net/' + imageId,
    })
    res.end('')
  } else if (req.url === '/api/images' && req.method === 'POST') {
    getRawBody(req, {
      limit: '1mb',
    }, async (err, body) => {
      if (err !== null) {
        respondBad(400, 'request body error')
        return
      }
      const imageId = makeId()
      try {
        const tryUpload = async () => {
          const { status } = await b2.uploadFile({
            uploadUrl: uploadTokens.uploadUrl,
            uploadAuthToken: uploadTokens.authorizationToken,
            fileName: imageId,
            mime: 'text/plain',
            data: body,
          })
          return status
        }
        if (uploadTokens === undefined) {
          await getUploadTokens()
        }
        let uploadStatus
        uploadStatus = await tryUpload()
        if (uploadStatus === 401) {
          await getUploadTokens()
          uploadStatus = await tryUpload()
        }
        if (uploadStatus !== 200) {
          throw new Error()
        }
      } catch (e) {
        respondBad(500, 'upload error')
        return
      }
      respondGood({
        id: imageId,
      })
    })
  } else if (req.url === '/restaurants/make' && req.method === 'GET') {
    res.writeHead(200, {
      'content-type': 'text/html',
    })
    res.end(makeRestaurantPage)
  } else if (/^\/restaurants\/?\?/.test(req.url) && req.method === 'GET') {
    res.writeHead(200, {
      'content-type': 'text/html',
    })
    res.end(singleRestaurantPage)
  } else if (req.url.startsWith('/order/') && req.method === 'GET') {
    res.writeHead(200, {
      'content-type': 'text/html',
    })
    res.end(orderPage)
  } else if (req.url === '/' && req.method === 'GET') {
    res.writeHead(302, {
      location: '/restaurants/make',
    })
    res.end('')
  } else if (req.url === '/submit' && req.method === 'GET') {
    res.writeHead(200, {
      'content-type': 'text/html',
    })
    res.end(submitPage)
  } else if (req.url === '/api/submit' && req.method === 'POST') {
    getRawBody(req, {
      limit: '512kb'
    }, async (err, body) => {
      if (err !== null) {
        respondBad(400, 'request body error')
        return
      }
      let parsed
      try {
        parsed = JSON.parse(body)
      } catch (e) {
        respondBad(400, 'bad json')
        return
      }
      if (typeof parsed.url !== 'string') {
        respondBad(400, 'bad attributes')
        return
      }
      const context = await (await browser).createIncognitoBrowserContext()
      const page = await context.newPage()
      await page.setCookie({
        name: 'flag',
        value: keys.flag,
        url: 'https://web3.2019.redpwn.net',
      })
      await page.goto(parsed.url)
      let parsedUrl
      try {
        parsedUrl = new URL(parsed.url)
      } catch (e) {
        respondBad(400, 'invalid url')
        return
      }
      if (parsedUrl.origin === 'https://web3.2019.redpwn.net') {
        const waitProm = page.waitForSelector('#order[href]')
        try {
          await Promise.race([waitProm, new Promise((_, reject) => {
            setTimeout(() => reject(), 5000)
          })])
        } catch (e) {
          await context.close()
          respondBad(400, 'timeout')
          return
        }
      }
      const orderBtn = await page.$('#order')
      if (orderBtn !== null) {
        await orderBtn.click()
      }
      await context.close()
      respondGood({
        msg: 'the admin has visited your site!',
      })
    })
  } else {
    respondBad(404, 'endpoint not found')
  }
}).listen(80, () => {
  console.log('listening on port 80')
})
