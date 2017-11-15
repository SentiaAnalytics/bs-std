open Prelude;

[@bs.send] external _then : Js.Promise.t('a) => ('a => unit) => ('x => unit) => unit = "then";
let none = (_) => ();
let make = (a) => ((cb) => cb(a));
let map = (f, a) => (cb) => a(f >> cb);
let flatten = (a) => (cb) => a((b) => b(cb));
let flatMap = (f, a) => flatten @@ map(f, a);
let fromPromise = (f) => (cb) => _then(f(), (a) => cb @@ Ok(a), (err) => cb @@ Error(err));
