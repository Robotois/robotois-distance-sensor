var uSensor = require('bindings')('DistanceSensor')
var EventEmitter = require('events').EventEmitter;
var inherits = require('util').inherits;

function DistanceSensor(_header){
  var _self = this;
  EventEmitter.call(this);

  this.distance = new uSensor(_header);

  process.on('SIGINT', function () {
    _self.distance.release();
  });

  process.on('SIGTERM', function () {
    _self.distance.release();
  });
}

DistanceSensor.prototype.getValue = function (){
  return this.distance.getValue();
}

DistanceSensor.prototype.getBasicValue = function (){
  return this.distance.getBasicValue();
}

DistanceSensor.prototype.enableEvents = function(){
  var dist;
  if(!this.eventInterval){
    this.eventInterval = setInterval(()=>{ // Mediciones cada 100ms
      dist = this.getBasicValue();
      // console.log('Distancia: ' + dist);
      this.emit('value',dist);
    },200);
  }
}

DistanceSensor.prototype.distToString = function(_dist){
  return ("     " + _dist.toFixed(1).toString()).slice(-5);
};

DistanceSensor.prototype.when = function(value, callback){
  var dist;
  if (!this.interval) {
    setInterval(()=>{ // Tomar mediciones cada 200ms
      dist = this.distance.getBasicValue();
      console.log('Distancia: ' + dist);
      if (dist === value) {
        callback();
      }
    }, 500);
  }
}

DistanceSensor.prototype.release = function (){
  clearInterval(this.interval);
  clearInterval(this.eventInterval);
  this.distance.release();
}

inherits(DistanceSensor,EventEmitter);

module.exports = DistanceSensor;
