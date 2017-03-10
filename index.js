const DSensor = require('bindings')('DistanceSensor');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;

/**
 * Creates an instance of DistanceSensor.
 * @param {int} portNumber The port number where the sensors is connected.
 * @returns {DistanceSensor} DistanceSensor object.
 */
function DistanceSensor(portNumber) {
  const self = this;
  EventEmitter.call(this);

  this.distance = new DSensor(portNumber);

  process.on('SIGINT', () => {
    self.distance.release();
  });

  process.on('SIGTERM', () => {
    self.distance.release();
  });
}

DistanceSensor.prototype.getValue = function getValue() {
  return this.distance.getValue();
};

DistanceSensor.prototype.getBasicValue = function getBasicValue() {
  return this.distance.getBasicValue();
};

DistanceSensor.prototype.enableEvents = function enableEvents() {
  let dist;
  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => { // Mediciones cada 100ms
      dist = this.getBasicValue();
      // console.log('Distancia: ' + dist);
      this.emit('value', dist);
    }, 200);
  }
};

DistanceSensor.prototype.distToString = function distToString(dist) {
  return (`     ${dist.toFixed(1).toString()}`).slice(-5);
};

DistanceSensor.prototype.when = function when(value, callback) {
  let dist;
  if (!this.interval) {
    setInterval(() => { // Tomar mediciones cada 200ms
      dist = this.distance.getBasicValue();
      /* eslint-disable no-console */
      console.log(`Distancia: ${dist}`);
      if (dist === value) {
        callback();
      }
    }, 500);
  }
};

DistanceSensor.prototype.release = function release() {
  clearInterval(this.interval);
  clearInterval(this.eventInterval);
  this.distance.release();
};

inherits(DistanceSensor, EventEmitter);

module.exports = DistanceSensor;
