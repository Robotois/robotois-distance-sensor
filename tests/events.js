var _usonic = require('../index.js'),
  usonic = new _usonic(5); // Especificar conector
usonic.enableEvents();

usonic.on('value',(dist)=>{
  console.log("La distancia es: " + dist);
})

// setInterval(()=>{ // Estado ocioso
//
// },10000);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
