var express = require('express');
var chalk = require('chalk');
var debug = require('debug')('app');
var morgan = require('morgan');
var path = require('path');
const bodyParser = require('body-parser');
const passport = require('passport')
const cookieParser = require('cookie-parser');
const session = require('express-session');
const crypto = require('crypto');
const mongoose = require('mongoose');
const multer = require('multer');
const {GridFsStorage} = require('multer-gridfs-storage');
const methoOverride = require('method-override');
const Grid = require("gridfs-stream");

// var jsdom = require("jsdom");
// const { JSDOM } = jsdom;
// const { window } = new JSDOM();
// const { document } = (new JSDOM('')).window;
// global.document = document;
// var $ = require("jquery")(window);

const app = express();
//const server = require('http').Server(app);
//const io = require('socket.io')(server); 


app.use(morgan('tiny'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true}));
app.use(cookieParser());
app.use(session({secret : 'library'}));
app.use(methoOverride('_method'));

app.use(express.static(path.join(__dirname, '/public/')));
app.use('/css', express.static(path.join(__dirname, '/css')));
app.use('/js', express.static(path.join(__dirname, '/js')));
app.use('/img', express.static(path.join(__dirname, '/img')));
app.use('/fonts', express.static(path.join(__dirname, '/fonts')));
app.use('/assets', express.static(path.join(__dirname, '/assets')));
app.use('/assets2', express.static(path.join(__dirname, '/assets2')));
app.use('/assets3', express.static(path.join(__dirname, '/assets3')));
app.use('/', express.static(path.join(__dirname, '/')));
//app.use('/js', express.static(path.join(__dirname, '/node_modules/jquery/dist')));

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

//let namespaces = require('./data/namespaces')

const expressServer = app.listen(8080, function () {
    debug(`listening to port'${chalk.green(' 4000')}`);

});
const io = require('socket.io')(expressServer); 
app.set('socketio',io);
const nav = [{link : '/books', title : 'Books'},
{link : '/authors', title : 'Authors'}
];
const bookRouter = require('./routes/bookRoutes')(nav);
const authRouter = require('./routes/authRoutes')(nav);
const socketRouter = require('./routes/socketRouter');
const { data } = require('jquery');

require('./public/config/Passportx.js')(app);

app.use('/books',bookRouter);
app.use('/auth',authRouter);
//app.use('/terminal',socketRouter);
//app.locals.io = io;
//app.use('/auth/profile',io);
app.get('/', function (req, res) {
    res.render('index');
    //res.render('signup');
});

// const express = require('express');
// const app = express();
// const sockectio = require('socket.io');

// app.use(express.static(__dirname + '/public'));

// const expressServer = app.listen(4000);
// const io = sockectio(expressServer);


//  io.on('connection',(socket)=>{
//         console.log('app.js');
//         socket.on("arduino",(data)=>{
//         console.log("message is",data.message);
//         console.log("type of message is",typeof(data.message));
//         // // const newmsg = buildHTML(data.message);
//         // let x = document.querySelector('#messages');
//         // console.log(x,typeof(x));
//      })
//  });
var x = 0;
var y;
var socket1 ;
function ParseJson(jsondata) {
    try {
        return JSON.parse(jsondata);
    } catch (error) {
        return null;
    }
}
function sendTime(data) {
    io.sockets.emit('atime', { messages: data.message });
}
io.on('connection', function (socket , data) {
    socket1 = socket;
    socket.on("diagnoses",function(data){
        socket.join("diagnostics");
        console.log("got it from html : ", {message: data.message});
        io.sockets.emit('diagnose', { message: data.message });
    })
   
    
//   socket.on("he5a",data=>{
//       console.log(data);
//       io.sockets.emit('he5a', { message: data.Name });
//   })

  socket.on("diagnose",data=>{
      console.log(data);
      io.sockets.emit('diagnose', { data });
  })
  
//   socket.emit("he5a2",{ message: 'Message from server!' });
  socket.on('connection', function (data) {
    console.log(data);
    io.sockets.emit('connected', { message: data.Name });
   });

let timeout = setTimeout(client_disconnected , 4000);

  socket.on('stillConnected', function (data) {
    console.log(data);
    clearInterval(timeout);
    timeout = setTimeout(client_disconnected , 4000);
    io.sockets.emit('connected', { message: data.Name });
   });

function client_disconnected(){
    console.log("disconnected");
    io.sockets.emit('notConnected');
}

  socket.on('atime', function (data) {
	  sendTime(data);
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
	  io.sockets.emit('arduino', { message: data.Name });
    console.log(data);
  });
});
