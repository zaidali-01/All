const jwt = require('jsonwebtoken');

module.exports.JWTauth = async (req,res,next)=>
{
    const token = req.headers.authorization;
    try{
        jwt.verify(token,process.env.JWT_KEY);
        next();
    }
    catch(err)
    {
        res.status(401).json({msg: 'Unautherized'});
    }
}