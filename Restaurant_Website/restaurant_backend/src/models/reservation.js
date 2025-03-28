const mongo = require('mongoose');
const schema = mongo.Schema;

const reserveSchema = new schema({
    userid:{type:schema.Types.ObjectId, ref:'Users', required:true},
    tableid:{type:schema.Types.ObjectId, ref:'Table', required:true},
    members:{type:Number, required:true},
    date:{type:Date, required:true},
    time:{type:String, required:true}
});

const Reserve = mongo.model('Reserve',reserveSchema);

module.exports = Reserve;