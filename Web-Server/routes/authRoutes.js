const express = require('express');
const {MongoClient} = require('mongodb');
const passport = require('passport');
const debug = require('debug')('app:authRoutes');
const app = express();
//const http = require('http').Server(app)
//require('../chat.js')(http);

const authRouter = express.Router();

function router(nav){
    authRouter.route('/signUp')
    .post((req,res)=>{
        console.log('--------request---------');
        console.log(req.body);
        const { username , password } = req.body;
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
    });

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
        }).post(passport.authenticate('local',{
            successRedirect: '/services',
            failureRedirect: '/'
        }));

    return authRouter;
    
}
module.exports = router;