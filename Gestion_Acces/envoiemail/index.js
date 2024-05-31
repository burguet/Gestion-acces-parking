const express = require('express');
const app = express();
const cors = require('cors');
const axios = require('axios');
const bodyParser = require('body-parser');

app.use(cors());
app.use(bodyParser.json());

const port = 3000;

const apiKey = "e3e80a1ca2511d109b2ed173feb08af4";
const apiSecret = "f0cd99c4d1500f5da7010685f7e0b1c5";

async function sendMail(senderEmail, senderName, destEmail, destName, subject, message) {
    const data = {
        Messages: [
            {
                From: {
                    Email: senderEmail,
                    Name: senderName
                },
                To: [
                    {
                        Email: destEmail,
                        Name: destName
                    }
                ],
                Subject: subject,
                TextPart: message
            }
        ]
    };

    try {
        const response = await axios.post("https://api.mailjet.com/v3.1/send", data, {
            headers: {
                "Authorization": "Basic " + Buffer.from(apiKey + ":" + apiSecret).toString('base64'),
                "Content-Type": "application/json",
            }
        });
        return response.data;
    } catch (error) {
        console.error("Erreur lors de l'envoi de l'e-mail :", error);
        throw error;
    }
}

app.post('/sendmail', (req, res) => {
    const { senderEmail, senderName, destEmail, destName, subject, message } = req.body;
    sendMail(senderEmail, senderName, destEmail, destName, subject, message)
        .then((data) => {
            console.log(data);
            res.send("E-mail envoyé avec succès !");
        })
        .catch((error) => {
            res.status(500).send("Une erreur s'est produite lors de l'envoi de l'e-mail.");
        });
});

app.listen(port, () => {
    console.log(`L'application écoute sur http://localhost:${port}`);
});
