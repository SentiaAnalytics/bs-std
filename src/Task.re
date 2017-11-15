open Prelude;

[@bs.send] external _resolvePromise : (Js.Promise.t('a), 'a => unit, 'err => unit) => unit =
  "then";

let make = (create, fail, success) => create(fail, success);

let succeed = (a) => make((_, success) => success(a));

let fail = (x) => make((fail, _) => fail(x));

let fork = (fail, success, task) => task(fail, success);

let map = (f, task) => make((fail, success) => task(fail, (x) => f(x) |> success));

let map2 = (f, t1, t2) =>
  make((fail, success) => t1(fail, (a1) => t2(fail, (a2) => f(a1, a2) |> success)));

let map3 = (f, t1, t2, t3) =>
  make(
    (fail, success) =>
      t1(fail, (a1) => t2(fail, (a2) => t3(fail, (a3) => f(a1, a2, a3) |> success)))
  );

let flatMap = (f, task) => make((fail, success) => task(fail, (x) => (f(x))(fail, success)));

let biMap = (mapFail, mapSuccess, task) =>
  make((fail, success) => task((err) => mapFail(err) |> fail, (ok) => mapSuccess(ok) |> success));

let fold = (mapFail, mapSuccess, task) =>
  make((_, success) => task((err) => mapFail(err) |> success, (ok) => mapSuccess(ok) |> success));

let fromLazyPromise = (f) => make((fail, success) => _resolvePromise(f(), success, fail));

let fromOption = (err, opt) =>
  switch opt {
  | None => fail(err)
  | Some(x) => succeed(x)
  };

let fromResult = (res) =>
  switch res {
  | Error(err) => fail(err)
  | Ok(v) => succeed(v)
  };
