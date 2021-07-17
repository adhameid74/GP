const express = require('express');
const {MongoClient} = require('mongodb');
const passport = require('passport');
const debug = require('debug')('app:authRoutes');
const app = express();
const crypto = require('crypto');
const mongoose = require('mongoose');
const multer = require('multer');
const {GridFsStorage} = require('multer-gridfs-storage');
const methoOverride = require('method-override');
const Grid = require("gridfs-stream");
const path = require('path');

//const http = require('http').Server(app)
//require('../chat.js')(http);

const authRouter = express.Router();
let gfs;
function router(nav){
    authRouter.route('/signUp')
    .post((req,res)=>{
        console.log('--------request header---------');
        console.log(req.header);
        console.log('--------request body---------');
        console.log(req.body);
        let { username , password } = req.body;
        if(!username)
        {
            const myJSON = JSON.stringify(req.body);
            console.log(myJSON); 
            console.log(myJSON.slice(13,21));
            console.log(myJSON.slice(35,39));
            username = myJSON.slice(13,18);
            password = myJSON.slice(32,36);
        }
        console.log("-------- signup params -------")
        console.log(username , password);
        const url = 'mongodb://localhost:27017';
        const dbName = 'libraryApp';
        (async function addUser(){
            let client;
            try {
                client = await MongoClient.connect(url);
                const db = client.db(dbName);
                const col = db.collection('users');
                const user = {username , password};
                const results = await col.insertOne(user);
                //console.log(results.ops[0]);
                req.login(results.ops[0] , ()=>{
                    res.redirect('/auth/dashboard');
                })
            } catch (error) {
                //debug(error);
            }
        }()) 
    });
    authRouter.route('/signin')
        .get((req,res)=>{
            res.render('signin2');
            console.log("-------- signin params -------")
            console.log(req.body);
        }).post(passport.authenticate('local',{
            successRedirect: '/auth/dashboard',
            failureRedirect: '/auth/signUp'
        }));
        
    authRouter.route('/dashboard')
    .all((req, res , next)=>{
        if (req.user)
        {
            next();
        }
        else{
            res.redirect('/auth/signUp');
        }
    })
    .get((req,res)=>{
        //res.json(req.user);
        res.render('dashboard');
        const dbName = 'code_uploads';
        const url = 'mongodb://localhost:27017/'+dbName;
        const conn = mongoose.createConnection(url);
        
        conn.once('open', () => {
            // Init stream
            console.log('-------------------------- test1 ---------------------------');
            gfs = Grid(conn.db, mongoose.mongo);
            gfs.collection('uploads');
        });
    });
    authRouter.route('/diagnose')
    .all((req, res , next)=>{
        if (req.user)
        {
            next();
        }
        else{
            res.redirect('/auth/signUp');
        }
    })
    .get((req,res)=>{
        //res.json(req.user);
        res.render('diagnose');
        const dbName = 'code_uploads';
        const url = 'mongodb://localhost:27017/'+dbName;
        const conn = mongoose.createConnection(url);
        
        conn.once('open', () => {
            // Init stream
            console.log('-------------------------- test1 ---------------------------');
            gfs = Grid(conn.db, mongoose.mongo);
            gfs.collection('uploads');
        });
    });
// --------------------------------------------------------------------------------
    authRouter.route('/upload')
    // .all((req, res , next)=>{
    //     if (req.user)
    //     {
    //         next();
    //     }
    //     else{
    //         res.redirect('/auth/signUp');
    //     }
   // })
    .get((req,res)=>{
        //res.json(req.user);
        const dbName = 'code_uploads';
        const url = 'mongodb://localhost:27017/'+dbName;
        const storage = new GridFsStorage({
            url: url,   
            file: (req, file) => {
            return new Promise((resolve, reject) => {
                crypto.randomBytes(16, (err, buf) => {
                if (err) {
                    return reject(err);
                }
                const filename = buf.toString('hex') + path.extname(file.originalname);
                const fileInfo = {
                    filename: filename,
                    bucketName: 'uploads'
                };
                resolve(fileInfo);
                });
            });
            }
        });
        const upload = multer({ storage });
        gfs.files.find().toArray((err, files) => {
            // Check if files
            if (!files || files.length === 0) {
            res.render('uploads', { files: false });
            } else {
            files.map(file => {
                if (
                file.contentType === 'image/jpeg' ||
                file.contentType === 'image/png'
                ) {
                file.isImage = true;
                } else {
                file.isImage = false;
                }
            });
            res.render('uploads', { files: files });
            }
            });
            authRouter.route('/upload/uploading')
            // .all((req, res , next)=>{
            // if (req.user)
            //     {
            //         next();
            //     }
            // else{
            //         res.redirect('/auth/signUp');
            //     }
            // })
            .post(upload.single('file'),(req,res)=>{
                res.redirect('/auth/upload');
            });

            authRouter.route('/upload/files')
            // .all((req, res , next)=>{
            // if (req.user)
            //     {
            //         next();
            //     }
            // else{
            //         res.redirect('/auth/signUp');
            //     }
            // })
            .get((req, res) => {
                gfs.files.find().toArray((err, files) => {
                  // Check if files
                  if (!files || files.length === 0) {
                    return res.status(404).json({
                      err: 'No files exist'
                    });
                  }
                  
                  // Files exist
                  return res.json(files);
                  
                });
              });

            authRouter.route('/upload/files/:filename')
            // .all((req, res , next)=>{
            // if (req.user)
            //     {
            //         next();
            //     }
            // else{
            //         res.redirect('/auth/signUp');
            //     }
            // })
            .get((req, res) => {
            gfs.files.findOne({ filename: req.params.filename }, (err, file) => {
            // Check if file
            if (!file || file.length === 0) {
                return res.status(404).json({
                err: 'No file exists'
                });
            }
            // File exists
            console.log(file);
            var readStream = gfs.createReadStream({
                _id: file._id
            });
            readStream.pipe(res)
            })
        });

            authRouter.route('/upload/files/:id')
            // .all((req, res , next)=>{
            // if (req.user)
            //     {
            //         next();
            //     }
            // else{
            //         res.redirect('/auth/signUp');
            //     }
            // })
            .delete((req, res) => {
            gfs.remove({ _id: req.params.id, root: 'uploads' }, (err, gridStore) => {
            if (err) {
                return res.status(404).json({ err: err });
            }
        
            res.redirect('/auth/upload');
            });
        });
    });
// ------------------------------------------------------------------------------------------------------------
    authRouter.route('/signUp')
        .get((req,res)=>{
            res.render('signup2');
        }).post(passport.authenticate('local',{
            successRedirect: '/diagnose',
            failureRedirect: '/'
        }));

    authRouter.route('/services')
        .get((req,res)=>{
        res.render('services-list');
        const dbName = 'code_uploads';
        const url = 'mongodb://localhost:27017/'+dbName;
        const conn = mongoose.createConnection(url);
        
        conn.once('open', () => {
            // Init stream
            console.log('-------------------------- test1 ---------------------------');
            gfs = Grid(conn.db, mongoose.mongo);
            gfs.collection('uploads');
        });
    }).post(passport.authenticate('local',{
        successRedirect: '/services',
        failureRedirect: '/'
    }));
    authRouter.route('/signUp')
        .get((req,res)=>{
            res.render('signup2');
        }).post(passport.authenticate('local',{
            successRedirect: '/diagnose',
            failureRedirect: '/'
        }));

    authRouter.route('/services')
        .get((req,res)=>{
        res.render('services-list');
        const dbName = 'code_uploads';
        const url = 'mongodb://localhost:27017/'+dbName;
        const conn = mongoose.createConnection(url);
        
        conn.once('open', () => {
            // Init stream
            console.log('-------------------------- test1 ---------------------------');
            gfs = Grid(conn.db, mongoose.mongo);
            gfs.collection('uploads');
        });
    }).post(passport.authenticate('local',{
        successRedirect: '/services',
        failureRedirect: '/'
    }));

    return authRouter;
    
}
module.exports = router;