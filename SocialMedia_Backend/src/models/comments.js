const mongo = require('mongoose');
const schema = mongo.Schema;

const commentSchema = new schema({
    uid: {type:schema.Types.ObjectId, ref:'Users', required:true},
    pid: {type:schema.Types.ObjectId, ref:'Posts', required:true},
    text: {type:String, required:true}
});


const Comments = mongo.model('Comments',commentSchema);

module.exports = Comments;