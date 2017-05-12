const DSensor = require('../index.js');

const distance = new DSensor(1); // Especificar conector

setInterval(() => {
  const dist = distance.getValue();
  console.log(`La distancia es: ${dist}`);
}, 250);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
