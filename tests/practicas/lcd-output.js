const DSensor = require('../../index.js');
const LCD = require('robotois-lcd-display');

const lcd = new LCD();
const distance = new DSensor(5); // Especificar conector

distance.enableEvents();

distance.on('medicion', (value) => {
  // console.log(`Distancia: ${value}`);
  lcd.message(`Distancia: ${value}`);
});
