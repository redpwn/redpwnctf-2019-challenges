const crypto = require('crypto')
const http = require('http')
const mustache = require('mustache')
const getRawBody = require('raw-body')
const _ = require('lodash')
const flag = require('./flag')

const indexTemplate = `
<!doctype html>
<style>
  body {
    background: #172159;
  }
  * {
    color: #fff;
  }
</style>
<h1>your public blueprints!</h1>
<i>(in compliance with military-grade security, we only show the public ones. you must have the unique URL to access private blueprints.)</i>
<br>
{{#blueprints}}
  {{#public}}
    <div><br><a href="/blueprints/{{id}}">blueprint</a>: {{content}}<br></div>
  {{/public}}
{{/blueprints}}
<br><a href="/make">make your own blueprint!</a>
`

const blueprintTemplate = `
<!doctype html>
<style>
  body {
    background: #172159;
    color: #fff;
  }
</style>
<h1>blueprint!</h1>
{{content}}
`

const notFoundPage = `
<!doctype html>
<style>
  body {
    background: #172159;
    color: #fff;
  }
</style>
<h1>404</h1>
`

const makePage = `
<!doctype html>
<style>
  body {
    background: #172159;
    color: #fff;
  }
</style>
<div>content:</div>
<textarea id="content"></textarea>
<br>
<span>public:</span>
<input type="checkbox" id="public">
<br><br>
<button id="submit">create blueprint!</button>
<script>
  submit.addEventListener('click', () => {
    fetch('/make', {
      method: 'POST',
      headers: {
        'content-type': 'application/json',
      },
      body: JSON.stringify({
        content: content.value,
        public: public.checked,
      })
    }).then(res => res.text()).then(id => location='/blueprints/' + id)
  })
</script>
`

// very janky, but it works
const parseUserId = (cookies) => {
  if (cookies === undefined) {
    return null
  }
  const userIdCookie = cookies.split('; ').find(cookie => cookie.startsWith('user_id='))
  if (userIdCookie === undefined) {
    return null
  }
  return decodeURIComponent(userIdCookie.replace('user_id=', ''))
}

const makeId = () => crypto.randomBytes(16).toString('hex')

// list of users and blueprints
const users = new Map()

http.createServer((req, res) => {
  let userId = parseUserId(req.headers.cookie)
  let user = users.get(userId)
  if (userId === null || user === undefined) {
    // create user if one doesnt exist
    userId = makeId()
    const bpProto = {}
    const flagBp = {
      content: flag,
    }
    flagBp.constructor = {prototype: bpProto}
    flagBp.__proto__ = bpProto
    user = {
      bpProto,
      blueprints: {
        [makeId()]: flagBp,
      },
    }
    users.set(userId, user)
  }

  // send back the user id
  res.writeHead(200, {
    'set-cookie': 'user_id=' + encodeURIComponent(userId) + '; Path=/',
  })

  if (req.url === '/' && req.method === 'GET') {
    // list all public blueprints
    res.end(mustache.render(indexTemplate, {
      blueprints: Object.entries(user.blueprints).map(([k, v]) => ({
        id: k,
        content: v.content,
        public: v.public,
      })),
    }))
  } else if (req.url.startsWith('/blueprints/') && req.method === 'GET') {
    // show an individual blueprint, including private ones
    const blueprintId = req.url.replace('/blueprints/', '')
    if (user.blueprints[blueprintId] === undefined) {
      res.end(notFoundPage)
      return
    }
    res.end(mustache.render(blueprintTemplate, {
      content: user.blueprints[blueprintId].content,
    }))
  } else if (req.url === '/make' && req.method === 'GET') {
    // show the static blueprint creation page
    res.end(makePage)
  } else if (req.url === '/make' && req.method === 'POST') {
    // API used by the creation page
    getRawBody(req, {
      limit: '1mb',
    }, (err, body) => {
      if (err) {
        throw err
      }
      let parsedBody
      try {
        // default values are easier to do than proper input validation
        const mergeObj = {}
        mergeObj.constructor = {prototype: user.bpProto}
        mergeObj.__proto__ = user.bpProto
        parsedBody = _.defaultsDeep(mergeObj, JSON.parse(body))
      } catch (e) {
        res.end('bad json')
        return
      }

      // make the blueprint
      const blueprintId = makeId()
      user.blueprints[blueprintId] = {
        content: parsedBody.content,
        public: parsedBody.public,
      }

      res.end(blueprintId)
    })
  } else {
    res.end(notFoundPage)
  }
}).listen(80, () => {
  console.log('listening on port 80')
})
