const DSensor = require('../index.js');

const distance = new DSensor(5); // Especificar conector

setInterval(() => {
  const dist = distance.distToString(distance.getValue());
  console.log(`La distancia es: ${dist}`);
}, 500);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
