# Mediciones sin Eventos

Como hemos visto en la sección anterior, las mediciones de Distancia usando eventos porporcionan un punto de inicio para realizar algunas tareas. No obstante, en esta librería se proporcionan las funciones para realizar mediciones de manera directa.


## Función `getValue()`
A diferencia de las mediciones por eventos y usando la función `when()`, la función `getValue()` permite obtener las mediciones de distancia con puntos decimales. Esto en cierta forma puede mejorar la precisión en las mediciones.

Un ejemplo del uso de esta función es el siguiente:

```javascript
const DSensor = require('robotois-distance-sensor');

const distance = new DSensor(5); // Especificar conector

setInterval(() => {
  const dist = distance.getValue();
  console.log(`La distancia es: ${dist}`);
}, 500);
```

El resultado de ejecutar el código anterior es similar al siguiente:

```
La distancia es: 16.70689582824707
La distancia es: 16.267240524291992
La distancia es: 16.439655303955078
La distancia es: 16.732759475708008
```
Como se puede observar, ahora las mediciones tienen una cantidad considerable de dígitos despues del punto decimal, ello debido a la conversión *Análogo-Digital*. Una forma sencilla de obtener mediciones más agradables a la vista, es reducir la cantidad de digitos.

Por lo anterior, en la librería se cuenta con la función `distToString()`, la cual establece un formato de 3 dígitos antes del punto decimal y un dígito después. Con ello se pueden obtener mediciones más adecuadas (para ciertas aplicaciones).

```javascript
const dist = distance.distToString(distance.getValue());
```
En este caso el resultado será similar al siguiente:

```
La distancia es:   7.5
La distancia es:   8.9
La distancia es:   9.8
La distancia es:  10.7
La distancia es:  11.9
La distancia es:  12.9
La distancia es:  13.9
```

## Función `getBasicValue()`
La función `getBasicValue()` permite obtener mediciones sin punto decimal, es decir que solo enteros, de hecho esta función es la que se utiliza en las mediciones con eventos. Por lo tanto, un ejemplo básico de cómo utilizar esta función es tomar el ejemplo anterior y cambiar la función que obtiene la medición:

```javascript
  const dist = distance.getBasicValue();
```
El resultado será similar al siguiente:
```
La distancia es: 4
La distancia es: 6
La distancia es: 9
La distancia es: 12
La distancia es: 16
```
