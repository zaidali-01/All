const mongo = require('mongoose');
const schema = mongo.Schema;

const menuSchema = new schema({
    name:{type:String, required:true},
    category:{type:String, required:true},
    price:{type:Number, required:true},
    path:{type:String, required:true}
});

const Menu = mongo.model('Menu',menuSchema);

module.exports = Menu;