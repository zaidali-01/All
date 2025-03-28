let mul = require('multer');

const storage = mul.diskStorage({
    destination: (req,file,cb)=>
    {
        cb(null,'uploads/');
    },
    filename: (req,file,cb)=>
    {
        cb(null,file.originalname);
    }
});

const upload = mul({storage});

module.exports = upload