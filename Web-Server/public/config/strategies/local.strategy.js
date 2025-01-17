const passport = require('passport');
const {Strategy} = require('passport-local');
const {MongoClient} = require('mongodb');

function localStrategy(){
    passport.use(new Strategy({
        userNameField : 'username',
        passwordField : 'password'
    },(username , password , done)=>{
        const url = 'mongodb://localhost:27017';
        const dbName = 'libraryApp';
        (async function mongo(){
            let client;
            try {
                client = await MongoClient.connect(url);
                const db = client.db(dbName);
                const col = db.collection('users');
                const user = await col.findOne({ username });
                if (user.password === password){
                    done(null , user);
                }
                else{
                    done(null , false);
                }
            } catch (error) {
                //debug(error);
            }
            client.close();
        }()) 
    }
    ));
}
module.exports = localStrategy;