const DSensor = require('../index.js');

const distance = new DSensor(1); // Especificar conector

setInterval(() => {
  const dist = distance.getBasicValue();
  console.log(`La distancia es: ${dist}`);
}, 500);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
