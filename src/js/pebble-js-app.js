 Pebble.addEventListener("ready",
  function(e) {
    //App is ready to receive JS messages
  }
);

var speed; 
var speedMPH;
var speedKPH;
var locationOptions = {timeout: 15000, maximumAge: 60000};

function fetch_speed(position) {
     speed  = position.coords.speed;
    
     speedMPH = speed * 0.000621371192;
    speedKPH = speed * 0.001;
  Pebble.sendAppMessage({speed_key: speedMPH});
 console.log ( speedMPH + ' ' );
  };
 
function fetch_speed_error(err) {
  console.log(err);
  Pebble.sendAppMessage({speed_key: 999});
}
 
Pebble.addEventListener('ready', function(e) {
 locationWatcher = window.navigator.geolocation.watchPosition(fetch_speed, fetch_speed_error, locationOptions);
 // speedWatcher = window.navigator.coords.speed;
});