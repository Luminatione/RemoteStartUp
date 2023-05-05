const express = require('express');
const ws = require('ws');
const app = express();
const port = 3000;
let boardLastRegsterTime = -1;
let boardWS = null;

function restartBoard(res)
{
  if (boardWS) 
  {
    boardWS.send('restart');
    res.json({success: true});
  } 
  else
  {
    res.json({success: false});
  }
}

let server = app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});

app.get('/boardLastRegisterTime', (req, res) => {
    res.json({boardLastRegisterTime: boardLastRegsterTime});
});

app.get('/notifyBoard', (req, res) => {
    if (boardWS) 
    {
        boardWS.send('notify');
        res.json({success: true});
    } 
    else 
    {
        res.json({success: false});
    }
});

app.get('/restartBoard', (req, res) => {
  restartBoard(res);
});

app.get('/shutdown', (req, res) => {
  restartBoard(res);
  server.close(() => {
    console.log('Server closed');
    process.exit(0);
  });
});
 
const wss = new ws.WebSocketServer({server: server});
console.log('WebSocket server started');

wss.on('connection', function connection(ws) {
    console.log('ws connection');
  ws.on('error', console.error);

  ws.on('message', function message(data) {
    console.log('received: %s', data);
    boardLastRegsterTime = Date.now();
    boardWS = ws;
  });
});
