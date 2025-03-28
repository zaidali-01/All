const express = require('express');
const routes = express.Router();
const {register, checkname, checkusername,login,createpost,getposts,commentonpost,likeonpost,followuser,getuserbyid,getcommentsonpost} = require('../controllers/media');
const {JWTauth} = require('../middleware/jwtauth')

routes.post('/register',checkname,checkusername,register);
routes.post('/login',login);
routes.post('/post/:id',JWTauth,createpost);
routes.get('/posts',JWTauth,getposts);
routes.post('/comment',commentonpost);
routes.post('/like',likeonpost);
routes.put('/follow/:uid/:fid',followuser);
routes.get('/user/:id',getuserbyid);
routes.get('/comments/:id',getcommentsonpost);

module.exports=routes;