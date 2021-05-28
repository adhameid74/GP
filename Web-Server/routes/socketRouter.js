const express = require('express');
// var cmd = require("../js/terminal")
// const app = express();
// const server = require('http').Server(app);
// const io = require('socket.io')(server); 

const socketRouter = express.Router

const router = new socketRouter();

router.get('/', (req, res, next) => {
    //const io = req.app.locals.io
    const io = req.app.get('socketio');
    //console.log(io);    
    res.render('terminal');
    //res.send("OK")
    io.on('connection',(socket)=>{
        console.log('socketRouter');
        socket.on("arduino",(data)=>{
            console.log(data.message);
        })
        //console.log(socket);
        socket.on("command",(cmd)=>{
            console.log("command from socketRouter.js :" + cmd);
        })
    });
});

module.exports = router