module.exports = (promise) => {
  if (!(promise instanceof Promise)) return promise;
  let res, val;
  promise.then((v) => {
    res = 1;
    val = v;
  });
  require("process")._tickCallback();
  return res ? val : promise;
};

module.exports.status = (promise) => {
  if (!(promise instanceof Promise)) return;

  let status;
  promise.then(
    () => (status = "fulfilled"),
    () => (status = "rejected")
  );
  require("process")._tickCallback();
  return status ?? "pending";
};
