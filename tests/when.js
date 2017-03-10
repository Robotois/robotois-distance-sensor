var _usonic = require('../index.js'),
  usonic = new _usonic(5); // Especificar conector

usonic.when(15,()=>{
  console.log("lol la distancia es 15cm!!");
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
