const mongo = require('mongoose');
const schema = mongo.Schema;

const userSchema = new schema({
    name:{type:String, required:true},
    email:{type:String, required:true, unique:true},
    password:{type:String, required:true, minlength:6},
    role:{type:String, required:true}
});

const Users = mongo.model('Users',userSchema);

module.exports = Users;