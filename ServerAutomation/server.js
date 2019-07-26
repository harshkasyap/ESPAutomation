var express = require('express');
var fs = require('fs');
var fss = require('file-system');
var bodyParser = require("body-parser");
var dateTime = require('node-datetime');
const { makeACall } = require('./api/makeACall');

var app = express();
app.use(bodyParser.urlencoded({ extended: true }));

function getDateTime(){
  var dt = dateTime.create();
  var formatted = dt.format('Y-m-d H:M:S');
  return formatted;
}

var roomTemp = 0;
var msgDate = 0;
var arrChart = [];

app.get('/data', function (req, res) {
  res.json({arrChart : arrChart, time: getDateTime(), temp:roomTemp});
});

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

app.post('/submitData', function (req, res) {
  console.log(req.body);
  if (String(req.body.temp_sensor) === "nan") {
    return;
  } else {
    roomTemp = req.body.temp_sensor;
    res.send('POST Request');
  
    // Send Alert Msg
    if (Number(roomTemp) > 30 && (new Date() - msgDate) > 1800000) {
      msgDate = new Date();
      makeACall(`Alert! Temperature has reached ${roomTemp} degree, Repeating! Temperature has reached ${roomTemp} degree, Please do the needful in Lab.`);
    }
  
    // Make a record
    var dateTime = getDateTime();
    var fileName = __dirname + '/record/' + dateTime.split(" ")[0];
    var prevData = "";
    arrChart = [];
    if (fs.existsSync(fileName)) {
      prevData = fs.readFileSync(fileName).toString();
      var data = prevData.split("\n");
      data.map((temp) => {
        var parts = temp.split(" : ");
        if (parts.length === 2) {
          arrChart.push({label:parts[0].substring(1),y:Number(parts[1].substring(0, parts[1].length-1))});
        }
      });
    }
  
    fss.writeFileSync(fileName, `${prevData}\n{${dateTime.split(" ")[1]} : ${req.body.temp_sensor}}`)
  }
});

var server = app.listen(5000, function () {
  console.log('Node server is running..');
});
