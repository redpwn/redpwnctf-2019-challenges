const http = require('http')
const net = require('net')
const getRawBody = require('raw-body')

const indexPage = `
<!doctype html>
<style>
  div {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
</style>
<div>
  <h3><i>red pwn is</i> figures out what redpwn is doing! give <i>red pwn is</i> a URL, and <i>red pwn is</i> will ping you to say what redpwn is doing!</h3>
  <form method="POST">
    url:
    <input type="text" name="url">
  </form>
</div>
`

const redpwnDoing = 'installing arch on all computers\n'

http.createServer((req, res) => {
  if (req.url === '/' && req.method === 'GET') {
    res.writeHead(200)
    res.end(indexPage)
  } else if (req.url === '/' && req.method === 'POST') {
    getRawBody(req, {
      limit: '1mb',
    }, (err, body) => {
      if (err) {
        throw err
      }
      if (!body.toString('utf8').startsWith('url=')) {
        res.writeHead(400)
        res.end('bad form')
        return
      }
      const url = decodeURIComponent(body.toString('utf8').replace('url=', ''))
      let parsedUrl
      try {
        parsedUrl = new URL(url)
      } catch (e) {
        res.writeHead(400)
        res.end('bad url')
        return
      }
      if (parsedUrl.protocol !== 'http:') {
        res.writeHead(400)
        res.end('only the http protocol is supported')
        return
      }
      let port = parseInt(parsedUrl.port)
      if (Number.isNaN(port)) {
        port = 80
      }
      res.writeHead(200, {
        'content-type': 'text/plain',
        'transfer-encoding': 'chunked',
      })
      res.write('debug response:\n\n\n')
      const client = new net.Socket()
      client.connect(port, parsedUrl.hostname, () => {
        // forcing space to + makes people use the binary RESP, for a bit more challenge
        client.write(`GET ${decodeURIComponent((parsedUrl.pathname + parsedUrl.search).replace(/ /g, '+'))} HTTP/1.1\r\n`)
        client.write(`Host: ${parsedUrl.host}\r\n`)
        client.write(`User-Agent: red-pwn-is\r\n`)
        client.write(`Content-Length: ${redpwnDoing.length}\r\n\r\n`)
        client.write(redpwnDoing)
      })
      client.on('error', () => {})
      client.on('data', (data) => {
        res.write(data)
      })
      let ended = false
      client.on('end', () => {
        if (!ended) {
          ended = true
          res.end()
        }
      })
      setTimeout(() => {
        if (!ended) {
          ended = true
          res.end()
        }
      }, 2000)
    })
  } else {
    res.writeHead(404)
    res.end('')
  }
}).listen(80, () => {
  console.log('listening on port 80')
})
