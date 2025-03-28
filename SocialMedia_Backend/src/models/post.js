const mongo = require('mongoose');
const schema = mongo.Schema;

const postSchema = new schema({
    content: {type:String, required:true},
    uid: {type:schema.Types.ObjectId, ref:'Users', required:true}
},{timestamps:true});


const Posts = mongo.model('Posts',postSchema);

module.exports = Posts;