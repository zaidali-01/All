const express = require('express');
const bodyparser = require('body-parser');
const {connectdb} = require('./config/database.js');
const userRoutes = require('./src/routes/user.js');
const cors = require('cors');

const app = express();
const port = 3000;

app.use(cors());
app.use(bodyparser.json());
app.use('/api',userRoutes);

connectdb().then((res)=>
{
    app.listen(port,()=>{
        console.log('server is running');
    })
}).catch((err)=>{
    console.log(err);
});