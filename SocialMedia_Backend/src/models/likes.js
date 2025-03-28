const mongo = require('mongoose');
const schema = mongo.Schema;

const likeSchema = new schema({
    uid: {type:schema.Types.ObjectId, required:true, ref:'Users'},
    pid: {type:schema.Types.ObjectId, required:true, ref:'Posts'}
});

const Likes = mongo.model('Likes',likeSchema);

module.exports = Likes;