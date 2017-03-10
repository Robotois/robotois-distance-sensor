const DSensor = require('../index.js');

const distance = new DSensor(5); // Especificar conector

distance.when(15, () => {
  /* eslint-disable no-console */
  console.log('lol la distancia es 15cm!!');
});

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
