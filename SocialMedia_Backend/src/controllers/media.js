const Users = require('../models/user');
const bcrypt = require('bcrypt');
const Posts = require('../models/post');
const Comments = require('../models/comments');
const Likes = require('../models/likes');
const jwt = require('jsonwebtoken');

const register = ( async (req,res) =>
{
    const {name, username, password} = req.body;
    const b = await Users.findOne({username});
    if(b)
        res.status(400).json({msg:'user already exist!'});
    else
    {
        const f = [];
        bcrypt.hash(password,10,async function(err,hash){
            const newuser = new Users({
                name,
                username,
                password:hash,
                followers:f,
                following:f
            })
            console.log(newuser);
            try{
            const c = await newuser.save();
         if(c)
             res.status(201).json({msg:'user registered!'});
         else
             res.status(500).json({msg:'cannot register!',err});
    }
    catch(err)
    {
        res.status(500).json({msg:'error',err});
    }
})}
})

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
    
    const checkusername =((req,res,next)=>
    {
        const {username}=req.body;
        if(username.includes(" "))
            return res.status(400).json({msg:"username is incorrect!"});
        next();
    })

    const login = ( async (req,res)=>{
        const {username, password} = req.body;
        try{
        const u = await Users.findOne({username});
        if(u && bcrypt.compare(password,u.password))
        {
            const token = jwt.sign({ uid: u._id }, 'ZAID1100' , {
                expiresIn: '1h',
            });
            res.status(200).json({msg:'user loginned!',token});
        }
        else
        {
            res.status(200).json({msg:'user does not exists!'});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:'error'});
    }
    })

const createpost = ( async (req,res)=>{
    const {content} = req.body;
    const uid = req.params.id;
    const newpost = new Posts({
        content,
        uid
    })
    try{
    const c = await newpost.save();
    if(c)
    {
        res.status(201).json({msg:'post created!'});
    }
}
    catch(err)
    {
        res.status(500).json({msg:'cannot post',err});
    }
})

const getposts = ( async (req,res)=>{
    const posts = await Posts.find();
    if(posts)
    {
        res.status(200).json({msg:'posts fetched!', posts});
    }
    else
    {
        res.status(200).json({msg:'no post found!'});
    }
})

const commentonpost = ( async (req,res)=>{
    const {text} = req.body;
    const uid = req.query.uid;
    const pid = req.query.pid;
    const newcomment = new Comments({
        uid,
        pid,
        text
    })
    try{
    const d = await newcomment.save();
    if(d)
    {
        res.status(201).json({msg:'commented on post!'});
    }
    else{
        res.status(200).json({msg:'cannot comment!'});
    }
}
catch(err)
{
    res.status(500).json(err)
}
})

const likeonpost = ( async (req,res)=>
{
    const pid = req.query.pid;
    const uid = req.query.uid;

    const l = await Likes.find({pid});
    let a;
    if(l?.length>0)
    {
       a = l.filter((i)=>i.uid===uid);
    }
    if(a)
    {
        res.status(200).json({msg:'already liked by user'});
    }
    else
    {
    const newlike = new Likes({
        uid,
        pid
    })
    const c = await newlike.save();
    if(c)
    {
        res.status(201).json({msg:'liked on post!'});
    }
    else
    {
        res.status(500).json({msg:'cannot like!'});
    }
    }
})

const followuser = ( async (req,res)=>
{
    const uid = req.params.uid;
    const fid = req.params.fid;
    const u = await Users.findById(uid);
    const f = await Users.findById(fid);
    const b = u.following.filter((a)=>a===fid);
    const c = f.followers.filter((a)=>a===uid);
    if(b || c)
    {
        res.status(200).json({msg:'already followed!'});
    }
    else
    {
        let x = u.following;
        x.push(fid);
        let y = f.followers;
        y.push(uid);
        const follower = await Users.findByIdAndUpdate(uid,{following:x});
        const followed = await Users.findByIdAndUpdate(fid,{followers:y});
        if(follower && followed)
        {
            res.status(200).json({msg:'followed!', follow:{follower,followed}});
        }
        else
        {
            res.status(500).json({msg:'cannot follow!'});
        }
    }
})

const getuserbyid = ( async (req,res)=>{
    try{
    const u = await Users.findById(req.params.id);
    if(u)
        res.status(200).json({msg:'user fetched',user:u});
    }
    catch(err)
    {
        res.status(500).json({msg:'something went wrong'});
    }
})

const getcommentsonpost = ( async (req,res)=>{
    try{
        const c = await Comments.find({pid:req.params.id});
        if(c)
            res.status(200).json({msg:'comments gotten',comments:c});
    }
    catch(err)
    {
        res.status(500).json({msg:'something went wrong'});
    }
})

module.exports = {register, checkname, checkusername, login, createpost, getposts, commentonpost, likeonpost, followuser, getuserbyid, getcommentsonpost};
