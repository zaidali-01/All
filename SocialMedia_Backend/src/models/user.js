const mongo = require('mongoose');
const schema = mongo.Schema;

const userSchema = new schema({
    name: {type:String, required:true},
    username: {type:String, required:true, unique:true},
    password: {type:String, required:true, minlength:6},
    followers: [{type:schema.Types.ObjectId, ref:'Users'}],
    following: [{type:schema.Types.ObjectId, ref:'Users'}]
});

const Users = mongo.model('Users',userSchema);

module.exports = Users;