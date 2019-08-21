const addon = require('bindings')('DistanceSensor');
const EventEmitter = require('events').EventEmitter;
const inherits = require('util').inherits;

/**
 * Creates an instance of DistanceSensor.
 * @param {int} portNumber The port number where the sensors is connected.
 * @returns {DistanceSensor} DistanceSensor object.
 */
function DistanceSensor(portNumber = 0) {
  EventEmitter.call(this)
  const emitter = this

  const distance = new addon.MyObject(portNumber)
  let publish = null
  let eventInterval = null
  let toiId = null
  let updateTopic= null

  this.getValue = function() {
    return distance.getValue();
  }
  
  this.getBasicValue = function() {
    return distance.getBasicValue();
  }

  this.getState = function() {
    return `{"state":{"reported":{"${toiId}":${this.getBasicValue()}}}}`
  }
  
  this.enableEvents = function(mqttConfig) {
    let prevValue = distance.getBasicValue()
    if (mqttConfig) {
      publish = mqttConfig.publish;
      updateTopic = mqttConfig.updateTopic;
      toiId = `distance${mqttConfig.instance}`
      publish(updateTopic, this.getState());
    }
    if (!eventInterval) {
      eventInterval = setInterval(() => {
        const currentValue = distance.getBasicValue();
        emitter.emit('medicion', currentValue);
        if (publish) {
          publish(updateTopic, this.getState());
        }
      }, 1000);
    }
  };
  
  this.release = function() {
    clearInterval(eventInterval);
    distance.release();
  }

  process.on('SIGINT', () => {
    distance.release();
  });
  
  process.on('SIGTERM', () => {
    distance.release();
  });
}

inherits(DistanceSensor, EventEmitter);

module.exports = DistanceSensor;
