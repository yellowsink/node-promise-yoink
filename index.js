module.exports = (promise) => {
  if (!(promise instanceof Promise)) return promise;
  let res, val;
  promise.then((v) => {
    res = 1;
    val = v;
  });
  process._tickCallback();
  return res ? val : promise;
};

module.exports.status = (promise) => {
  if (!(promise instanceof Promise)) return;

  let status;
  promise.then(
    () => (status = "fulfilled"),
    () => (status = "rejected")
  );
  process._tickCallback();
  return status ?? "pending";
};
