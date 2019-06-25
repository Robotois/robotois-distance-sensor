const addon = require('bindings')('DistanceSensor');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;

/**
 * Creates an instance of DistanceSensor.
 * @param {int} portNumber The port number where the sensors is connected.
 * @returns {DistanceSensor} DistanceSensor object.
 */
function DistanceSensor(portNumber = 0) {
  const self = this;
  EventEmitter.call(this);

  this.distance = new addon.MyObject(portNumber);

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

DistanceSensor.prototype.publishNow = function publishNow() {
  this.mqttClient.publish(this.myTopic, this.getBasicValue().toString());
};

DistanceSensor.prototype.enableEvents = function enableEvents(mqttConfig) {
  let prevValue = this.getBasicValue();
  if (mqttConfig) {
    this.mqttClient = mqttConfig.mqttClient;
    this.myTopic = `sensors/distance${mqttConfig.instance}`;
    this.mqttClient.publish('registerTopic', this.myTopic);
  }
  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => {
      const currentValue = this.getBasicValue();
      if (currentValue !== prevValue) {
        this.emit('medicion', currentValue);
        if (this.mqttClient) {
          this.mqttClient.publish(this.myTopic, currentValue.toString());
        }
        prevValue = currentValue;
      }
    }, 500);
  }
};

DistanceSensor.prototype.release = function release() {
  clearInterval(this.eventInterval);
  this.distance.release();
};

inherits(DistanceSensor, EventEmitter);

module.exports = DistanceSensor;
