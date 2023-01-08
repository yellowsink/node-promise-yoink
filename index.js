module.exports = require("bindings")("promise-yoink").yoink;

console.log(
  module.exports(Promise.resolve("it works!"))
);