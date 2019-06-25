const DSensor = require('../src/index.js');

const distance = new DSensor(5); // Especificar conector

setInterval(() => {
  const dist = distance.getBasicValue();
  console.log(`La distancia es: ${dist}`);
}, 250);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
