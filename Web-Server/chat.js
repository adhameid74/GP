var util  = require('util');
var app = require('http').createServer(handler);
var io = require('socket.io')(app);
var fs = require('fs');
app.listen(8080);

function handler (req, res) {
  fs.readFile(__dirname + '/index.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading index.html');
    }

    res.writeHead(200);
    res.end(data);
  });
}
function ParseJson(jsondata) {
    try {
        return JSON.parse(jsondata);
    } catch (error) {
        return null;
    }
}
function sendTime() {
    io.sockets.emit('atime', { time: new Date().toJSON() });
}
io.on('connection', function (socket , data) {
  socket.emit('welcome', { message: 'Connected !!!!' });
  socket.on("he5a",data=>{
      console.log(data.message);
      
  })
  socket.emit("he5a2",{ message: 'Message from server!' });
  socket.on('connection', function (data) {
    console.log(data);   });
  socket.on('atime', function (data) {
	  sendTime();
    console.log(data);
    });
socket.on('JSON', function (data) {
	console.log(data);
	var jsonStr = JSON.stringify(data);
	    var parsed = ParseJson(jsonStr);
console.log(parsed);
	console.log(parsed.sensor);
  });
    socket.on('arduino', function (data) {
	  io.sockets.emit('arduino', { message: 'R0' });
    console.log(data);
  });
});
