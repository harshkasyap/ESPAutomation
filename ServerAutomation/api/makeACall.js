const Nexmo = require('nexmo');

// Create own nexmo details
const nexmo = new Nexmo({
  apiKey: '********',
  apiSecret: '****************',
  applicationId: '********-****-****-****-************',
  privateKey: 'private.key',
});

function createCall(number, ncco) {
  nexmo.calls.create(
  {
    to: [{ type: 'phone', number: number }],
    from: { type: 'phone', number: '919999999999' },
    ncco,
  },
  (err, result) => {
    console.log(err || result);
  });
}

function makeACall(msg) {
  const ncco = [
    {
      action: 'talk',
      voiceName: 'Raveena',
      text: msg,
    },
  ];

  createCall('919999999999', ncco);
}

module.exports = {
    makeACall
}
