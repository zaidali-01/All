const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
    host: 'smtp.gmail.com',
    port: 587,
    secure: false,
    auth: {
        user: '', //your email
        pass: '' //your passkey
    }
});

async function sendEmail(userEmail,data) 
{
        const mailOptions = {
            from: '"" <>', //your username and email
            to: userEmail,
            subject: 'Fusion Bytes',
            html: data,
            //attachments: [
             //   {
             //       filename: 'file.txt', // File name to be sent
              //      path: './file.txt' // Path to the file
              //  }
            //]
        };

        try {
            const info = await transporter.sendMail(mailOptions);
            console.log('Email sent successfully:', info);
            return true;
          } catch (error) {
            console.error('Error sending email:', error);
            throw new Error('Email sending failed');
          }
}

module.exports = sendEmail;
