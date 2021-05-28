const express = require('express');
bookRouter = express.Router();
function router(nav){
    bookRouter.use((req , res , next)=>{
        if (req.user)
        {
            next();
        }
        else{
            res.redirect('/');
        }
    })
    bookRouter.route('/')
        .get((req,res)=>{
            res.render('index')
            // ,
            // {
            //     nav,
            //     title: 'Library',
            //     books
            // });
        })
        return bookRouter;
}

    module.exports = router;