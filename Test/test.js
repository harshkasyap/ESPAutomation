const Nexmo = require('nexmo');

// Create own nexmo details, follow https://dashboard.nexmo.com/getting-started/voice
const nexmo = new Nexmo({
  apiKey: '********',
  apiSecret: '****************',
  applicationId: '********-****-****-****-************',
  privateKey: 'private.key',
});

const funnyText = 'Hello Mr xyx!.';

const ncco = [
  {
    action: 'talk',
    voiceName: 'Raveena',
    text: funnyText,
  },
];


nexmo.calls.create(
  {
    to: [{ type: 'phone', number: '91xxxxxxxxxx' }],
    from: { type: 'phone', number: '91xxxxxxxxxx' },
    ncco,
  },
  (err, result) => {
    console.log(err || result);
  },
);
