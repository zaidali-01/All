const mongo = require('mongoose');
const schema = mongo.Schema;

const orderSchema = new schema({
    reservationid:{type:schema.Types.ObjectId, ref:'Reserve', required:true},
    menuid:{type:schema.Types.ObjectId, ref:'Menu', required:true},
    quantity:{type:Number, required:true}
});

const Order = mongo.model('Order',orderSchema);

module.exports = Order;