const users = require('../models/users.js');
const bcrypt = require('bcrypt');
const fs = require('fs');
const ratelimit = require('express-rate-limit');

const checkname =((req,res,next)=>
{
    const {name}=req.body;
    for(let i=0;i<name.length;i++)
    {
        if(name.charCodeAt(i)<65 || (name.charCodeAt(i)>90 && name.charCodeAt(i)<97) || name.charCodeAt(i)>122)
            return res.status(400).json({msg:"name is inappropriate!"});
    }
    next();
})

const checkemail =((req,res,next)=>
{
    const {email}=req.body;
    if(!email.endsWith('@gmail.com') && !email.endsWidth('@yahoo.com'))
        return res.status(400).json({msg:"email is incorrect!"});
    if(email.indexOf('@')!==email.lastIndexOf('@'))
        return res.status(400).json({msg:"email incorrect!"});
    let a=email.indexOf('@');
    for(let i=0;i<a;i++)
    {
        if(email.charCodeAt(i)<48 || (email.charCodeAt(i)>57 && email.charCodeAt(i)<65) || (email.charCodeAt(i)>90 && email.charCodeAt(i)<97) || email.charCodeAt(i)>122)
          
            return res.status(400).json({msg:"email is incorrect!"});
    }
    next();
})

const register = (async(req,res)=>
{
    const {name,email,password,age} = req.body;

    const b= await users.findOne({email});
    if(b)
        res.status(400).json({msg:'user already exits'});
    else{
    bcrypt.hash(password,10,async function(err,hash){
    const newuser = new users({
        name,
        email,
        password:hash,
        age
    })
    const c = await newuser.save();
    if(c)
        res.status(201).json({msg:'user registered!'});
    else
        res.status(500).json(err);
    })
    }
})

const login =((req,res)=>
{
    const {email,password}=req.body;
    const data = users.findOne({email});
    if(data && bcrypt.compare(password,data.password))
    {
        res.status(200).json({msg:'user loginned!'});
    }
    else
    {
        res.status(404).json({msg:'User does not exist!'});
    }
})

const getusers = (async(req,res)=>
{
    try{
        let sort=req.query.sort;
        let orderby=req.query.orderby;
        let search=req.query.search;
        let on=req.query.searchon;
        let pg=req.query.page;
        let psize=req.query.psize;
        let obj={};
        obj[`${sort}`]=orderby==='Asc' ? 1 : -1;
        let obj1={};
        obj1[`${on}`]={$regex:'.*'+search+'.*',$options:'i'};
        const u = await users.find(obj1).sort(obj).limit(psize).skip((pg-1)*psize);
        if(u)
        {
            res.status(200).json({msg:'users fetched',users:u});
        }
        else
        {
            res.status(200).json({msg:'no user'});
        }
    }
    catch(err){
        res.status(500).json(err);
    }
})

const getuserbyid = (async(req,res)=>
{
    try{
    const u = await users.findById(req.params.id);
        res.status(200).json({msg:'user fetched!',user:u});
    }
    catch(err){
        res.status(500).json({msg:'user not found'});
    }
})

const updateuserbyid = (async(req,res)=>
{
    const {name,email} = req.body;
    try{
        const u = await users.findByIdAndUpdate(req.params.id,{name,email});
        res.status(200).json({msg:'user updated!',update:u});
    }
    catch(err)
    {
        res.status(500).json({msg:'user not found'});
    }
})

const deleteuserbyid = (async(req,res)=>
{
    try{
        const u = await users.findByIdAndDelete(req.params.id);
        res.status(200).json({msg:'user deleted!'});
    }
    catch(err){
        res.status(500).json({msg:'user not found'});
    }
})

const limit = ratelimit({
    windowMs: 5*60*1000,
    max:2,
    message:'Too many requests from this IP address'
});

const uploadfile = (async(req,res)=>
{
    try{
        console.log(__dirname);
       await res.status(200).json(req.file);
    }
    catch(err)
    {
        console.log(err);
        res.status(500).json(err);
    }
})

const filenam =(async(req,res)=>
{
    const path="C:/Users/kashaf Ali/Documents/Node_Tasks/uploads/";
    fs.readdir(path,(err,files)=>
{
    if(err)
        res.status(500).json(err);
    else
    {
        res.status(200).json({msg:"file names fetched",filenames:files});
    }
})
})

const downloadfile = (async(req,res)=>
{
    const file = req.params.name;
    const path = `C:/Users/kashaf Ali/Documents/Node_Tasks/uploads/${file}`;

    res.download(path,function(err){
        if(err)
            console.log(err);
        else
        {
            console.log('down');
        }
    })
})

module.exports ={register,login,checkname,checkemail,getusers,getuserbyid,updateuserbyid,deleteuserbyid,limit,uploadfile,filenam,downloadfile};