const DSensor = require('../index.js');

const distance = new DSensor(5); // Especificar conector
distance.enableEvents();

distance.on('medicion', (dist) => {
  /* eslint-disable no-console */
  console.log(`La distancia es: ${dist} cm`);
});

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
