const http = require('http')
const https = require('https')

http.createServer((req, res) => {
  let [mime, id] = req.url.slice(1).split('/')
  if (req.method !== 'GET' && typeof mime !== 'string' || typeof id !== 'string' || mime.length === 0 || id.length === 0) {
    res.writeHead(400)
    res.end('bad request')
    return
  }
  mime = decodeURIComponent(mime)
  id = decodeURIComponent(id)
  if (!['image/png', 'application/json'].includes(mime)) {
    res.writeHead(400)
    res.end('mime is not one of the valid values')
    return
  }
  const b2Req = https.request({
    host: 'f002.backblazeb2.com',
    port: 443,
    path: '/file/redpwnctf-feud/' + encodeURIComponent(id),
    method: 'GET',
  }, (b2Res) => {
    if (b2Res.statusCode !== 200) {
      res.writeHead(404)
      res.end('')
      return
    }
    res.writeHead(200, {
      'access-control-allow-origin': '*',
      'content-type': mime,
    })
    b2Res.on('data', (data) => {
      res.write(data)
    })
    b2Res.on('end', () => {
      res.end()
    })
  })
  b2Req.on('error', () => {
    try {
      res.writeHead(500)
      res.end('')
    } catch (e) {}
  })
  b2Req.end()
}).listen(80, () => {
  console.log('listening on port 80')
})
