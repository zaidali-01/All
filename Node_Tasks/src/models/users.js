const mongo = require('mongoose');
const schema =mongo.Schema; 

const userSchema=new schema({
    name: {type:String, required:true},
    email: {type:String, required:true,unique:true},
    password: {type:String, required:true, minlength:8},
    age :{type:Number, min:0}
});

const Users=mongo.model('Users',userSchema);

module.exports =Users;