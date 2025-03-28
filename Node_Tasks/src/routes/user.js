const express = require('express');
const router = express.Router();
const upload = require('../controllers/multer.js');
const {register,login,checkname,checkemail,getusers,getuserbyid,updateuserbyid,deleteuserbyid,limit,uploadfile,downloadfile,filenam} = require('../controllers/user.js');
const {JWTauth} = require('../middleware/JWTauth.js');

router.post('/register',checkname,checkemail,register);
router.post('/login',login);
router.get('/users',JWTauth,getusers);
router.get('/user/:id',JWTauth,getuserbyid);
router.put('/update/:id',JWTauth,checkname,checkemail,updateuserbyid);
router.delete('/delete/:id',JWTauth,deleteuserbyid);
router.post('/upload',limit,upload.single('file'),uploadfile);
router.get('/download/:name',limit,downloadfile);
router.get('/filenames',filenam);

module.exports =router;