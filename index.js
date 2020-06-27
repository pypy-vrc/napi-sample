var sample = require('bindings')('napi_sample');

console.log('sample', sample.sample());
console.log('sum', sample.sum(1, 2, 3, 4, 5, '6'));