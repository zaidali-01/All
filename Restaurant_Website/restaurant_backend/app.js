const express = require('express');
const bodyparser = require('body-parser');
const cors = require('cors');
const {connectdb} = require('./src/config/db.js');
const router = require('./src/routes/routes.js');
const path = require('path');

const app = express();
const port = 5000;

app.use(cors());
app.use(bodyparser.json());
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));
app.use('/api',router);

connectdb().then((res)=>
{
    app.listen(port,()=>
    {
        console.log("server is running!");
    })
}).catch((err)=>
{
    console.log(err);
})