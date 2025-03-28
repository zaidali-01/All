const mongo = require('mongoose');
const url = 'mongodb://localhost:27017/socialdb';

module.exports.connectdb = () =>
{
    return mongo.connect(url);
}