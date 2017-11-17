open Prelude;

let some = (a) => Some(a);

let none = None;

let map = (f, opt) =>
  switch opt {
  | None => None
  | Some(x) => Some(f(x))
  };

let map2 = (f, opt1, opt2) =>
  switch (opt1, opt2) {
  | (Some(a1), Some(a2)) => Some(f(a1, a2))
  | _ => None
  };

let map3 = (f, opt1, opt2, opt3) =>
  switch (opt1, opt2, opt3) {
  | (Some(a1), Some(a2), Some(a3)) => Some(f(a1, a2, a3))
  | _ => None
  };

let flatten = (opt) =>
  switch opt {
  | None => None
  | Some(a) => a
  };

let flatMap = (f, opt) =>
  switch opt {
  | None => None
  | Some(x) => f(x)
  };

let withDefault = (defaultValue, opt) =>
  switch opt {
  | Some(x) => x
  | None => defaultValue
  };

let fromResult = (res) =>
  switch res {
  | Error(_) => None
  | Ok(v) => Some(v)
  };

let fromRemote = (res) =>
  switch res {
  | Ready(a) => Some(a)
  | _ => None
  };

let isNone =
  fun
  | None => true
  | _ => false;

let isSome =
  fun
  | None => false
  | _ => true;

let encode = (encoder) =>
  fun
  | None => Js.Json.null
  | Some(v) => encoder(v);

let decode = Json.Decode.optional;
