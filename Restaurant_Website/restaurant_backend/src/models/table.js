const mongo = require('mongoose');
const schema = mongo.Schema;

const tableSchema = new schema({
    capacity:{type:Number, required:true}
});

const Table = mongo.model('Table',tableSchema);

module.exports = Table;