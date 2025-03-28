const Users = require('../models/user.js');
const bcrypt = require('bcrypt');
const sendEmail = require('./mail.js');
const Table = require('../models/table.js')
const Reserve = require('../models/reservation.js')
const jwt = require('jsonwebtoken');
const Menu = require('../models/menu.js');
const Order = require('../models/order.js');

const register = async (req, res) =>
{
  const { name, email, password } = req.body;
  const role = "customer";

  try {
    const existingUser = await Users.findOne({ email });
    if (existingUser) {
      return res.status(400).json({ msg: 'User already exists!'});
    }

    const hashedPassword = await bcrypt.hash(password, 10);

    const newUser = new Users({
      name,
      email,
      password: hashedPassword,
      role
    });

    const savedUser = await newUser.save();


    try 
    {
      let data = `<p>Dear ${name}:<br>Thank you for registering at Fusion Bytes.<br>Regards</p>`;
      await sendEmail(email,data); 
      res.status(200).json({msg:'User registered successfully and email sent!'});
    } 
    catch (emailError) 
    {
      await Users.findByIdAndDelete(savedUser._id);
      return res.status(500).json({msg:'Email sending failed'});
    }

  } catch (err) {
    console.error('Error during registration:', err);
    res.status(500).json({ msg: 'Error during registration', error: err });
  }
};

const login = async (req,res) =>
{
    const {email, password} = req.body;
    try
    {
        const u = await Users.findOne({email});
        if(u && bcrypt.compare(password,u.password))
        {
            const token = jwt.sign({ uid: u._id , role:u.role }, 'ZAID1100' , {
                expiresIn: '1h',
            });
            res.status(200).json({msg:'user loginned!',token});
        }
        else
        {
            res.status(200).json({msg:'user does not exist!'});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:'error'});
    }
}

const createtable = async (req,res) =>
{
    const capacity = req.body.capacity;
    try{
        const newtable = new Table({
            capacity
        });
        const t = await newtable.save();
        res.status(201).json({msg:"table created!"});
    }
    catch(err)
    {
        res.status(500).json({msg:"table cannot be created!"});
    }
}

const createmenu = async (req, res) => {
    const { name, category, price } = req.body;
    const path = req.file.path;
    try {
        const newMenu = new Menu({
            name,
            category,
            price,
            path
        });

        const savedMenu = await newMenu.save();
        if (savedMenu) {
            res.status(201).json({ msg: "Menu Item Added" });
        } else {
            res.status(200).json({ msg: "Cannot add menu item" });
        }
    } catch (err) {
        res.status(500).json({ msg: "Cannot add menu item" });
    }
}

const getmenubycategory = async (req,res) =>
{
    const category = req.query.category;
    try
    {
        const m = await Menu.find({category});
        if(m)
        {
            res.status(200).json({msg:"menu fetched",items:m})
        }
        else
        {
            res.status(200).json({msg:"no menu item"});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:"cannot get menu"});
    }
}

const getuserid = async (req,res) =>
{
    const email = req.params.email;

    try
    {
        const u = await Users.findOne({email});
        if(u)
        {
            res.status(200).json({msg:'user id found',uid:u?._id});
        }
        else
        {
            res.status(200).json({msg:'user not found'});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:"cannot find user"});
    }
}

const reservation = async (req,res) =>
{
    const {members,date,time} = req.body;
    const uid = req.params.uid;
    let d = new Date(date);

    try{
    const t = await Table.find().sort({"capacity":1});

    let a;
    if(t?.length>0)
    {
        a = t.filter((b)=>b.capacity>=members);
    }
    else
    {
        res.status(200).json({msg:"no tables available!"});
    }

    if(a?.length == 0)
    {
        res.status(200).json({msg:"capacity exceded!"});
    }

    let x;
    for(let i=0;i<a.length;i++)
    {
        const r = await Reserve.findOne({
            tableid:a[i]._id,
            date:d,
            time
        })
        if(!r)
        {
            x = a[i];
            break;
        }
    }

    if(!x)
    {
        res.status(200).json({msg:"no table available!"});
    }

    const newReserve = new Reserve({
        userid:uid,
        tableid:x._id,
        members,
        date,
        time
    })

    const savedreserve = await newReserve.save();
    if(!savedreserve)
    {
        res.status(500).json({msg:"cannot reserve at the moment"});
    }
    try 
    {
      const u = await Users.findById(uid);
      let data = `<p>Dear ${u.name}:<br>Thank you for reservation at Fusion Bytes. Your table has been reserved at ${d.toLocaleDateString('en-US', {year: 'numeric',month: 'long',day: 'numeric'})} from ${time}.<br>Regards</p>`;
      await sendEmail(u.email,data); 
      res.status(200).json({msg:'Table reserved successfully and email sent!'});
    } 
    catch (emailError) 
    {
      console.log(emailError);
      return res.status(500).json({msg:'Email sending failed'});
    }
}
catch(err)
{
    console.error('Error during reservation:', err);
    res.status(500).json({ msg: 'Error during reservation', error: err });
}
}

const allreservations = async (req,res) =>
{
    try
    {
        let r = await Reserve.find();
        if(r)
        {
            r = await Promise.all(
                r.map(async (a) => {
                    const user = await Users.findById(a.userid);
                    return { ...a.toObject(), email: user.email };
                })
            );
            res.status(200).json({msg:"reservations fetched!",reserve:r});
        }
        else
        {
            res.status(200).json({msg:"no reservations"});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:"server error"});
    }
}

const reservationsbyid = async (req,res) =>
{
    const uid = req.params.uid;
    try
    {
        const r = await Reserve.find({userid:uid});
        if(r)
        {
            res.status(200).json({msg:"reservations fetched!",reserve:r});
        }
        else
        {
            res.status(200).json({msg:"no reservations"});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:"server error"});
    }
}

const makeorder = async (req,res) =>
{
    const {name,category,quantity} = req.body;
    const rid = req.params.rid;
    try
    {
        const m = await Menu.findOne({name,category});
        if(m)
        {
            const newOrder = new Order({
                reservationid:rid,
                menuid:m._id,
                quantity
            });
            const result = await newOrder.save();
            if(result)
            {
                res.status(201).json({msg:"order made"});
            }
        }
        else
        {
            res.status(200).json({msg:"no such item exist in this category"});
        }
    }
    catch(err)
    {
        res.status(500).json({msg:"cannot order"})
    }
}


module.exports = {register,login,createtable,reservation,getuserid,allreservations,makeorder,reservationsbyid,createmenu,getmenubycategory}