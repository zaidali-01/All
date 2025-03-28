const express = require('express');
const router = express.Router();
const {register,login,createtable,reservation,getuserid,allreservations,makeorder,reservationsbyid,createmenu, getmenubycategory} = require('../controllers/rest.js');
const upload = require('../controllers/multer.js');

router.post('/register',register);
router.post('/login',login);
router.post('/createtable',createtable);
router.post('/createmenu',upload.single('img'),createmenu);
router.post('/reserve/:uid',reservation);
router.get('/getuserid/:email',getuserid);
router.get('/getreservations',allreservations);
router.post('/makeorder/:rid',makeorder);
router.get('/getreservationsbyid/:uid',reservationsbyid);
router.get('/getmenu',getmenubycategory)

module.exports = router;