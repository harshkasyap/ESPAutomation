const Nexmo = require('nexmo');

// Create own nexmo details
const nexmo = new Nexmo({
  apiKey: '274802f8',
  apiSecret: 'tvWz4zzoLfnGAzXt',
  applicationId: '7e07cc48-55f7-4b80-ba21-f5ab1fe913e9',
  privateKey: 'private.key',
});

function createCall(number, ncco) {
  nexmo.calls.create(
  {
    to: [{ type: 'phone', number: number }],
    from: { type: 'phone', number: '917276393663' },
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

  createCall('917276393663', ncco);
}

module.exports = {
    makeACall
}