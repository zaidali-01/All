const express = require('express');
const bodyparser = require('body-parser');
const cors = require('cors');
const {connectdb} = require('./src/config/database');
const routes = require('./src/routes/social');

const app = express();
const port = 3000;

app.use(cors());
app.use(bodyparser.json());
app.use('/api',routes);

connectdb().then((res)=>
{
    app.listen(port,()=>
    {
        console.log('social media ready');
    })
}).catch((err)=>
{
    console.log(err);
})