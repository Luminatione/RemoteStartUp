const express = require('express');
const ws = require('ws');
const app = express();
const port = 3000;

let server = app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
}
);

const wss = new ws.WebSocketServer({server: server});
console.log('WebSocket server started');

wss.on('connection', function connection(ws) {
    console.log('ws connection');
  ws.on('error', console.error);

  ws.on('message', function message(data) {
    console.log('received: %s', data);
  });

  ws.send('something');
});