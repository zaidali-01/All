const mongo = require('mongoose');
const url = 'mongodb://localhost:27017/mydb';
module.exports.connectdb =()=>
{
    return mongo.connect(url);
}