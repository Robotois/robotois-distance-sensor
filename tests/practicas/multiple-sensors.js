const DSensor = require('../../index.js');
const Rotary = require('robotois-rotary-sensor');

const rotary = new Rotary(2);
const distance = new DSensor(5); // Especificar conector

rotary.enableEvents();
distance.enableEvents();

distance.on('medicion', (value) => {
  console.log(`Distancia: ${value}`);
  // lcd.message(`Distancia: ${value}`);
});

rotary.on('medicion', (value) => {
  console.log(`R: ${value}`);
});
