type async('a) = ('a => unit) => unit;

type remote('x, 'a) = 
  | NotAsked
  | Pending
  | Failed('x)
  | Ready('a);
  
type result('x, 'a) =
  | Error('x)
  | Ok('a);
  
type task('err, 'ok) = ('err => unit) => ('ok => unit) => unit;

type dict('k, 'v) = list(('k, 'v));
let identity = (a) => a;

let always = (a, _) => a;

let void = (_) => ();

let (>>) = (f, g, x) => g(f(x));

let flip = (f, a, b) => f(b, a);

let curry = (f, a, b) => f((a, b));

let uncurry = (f, (a, b)) => f(a, b);

let tap = (f, a) => {
  f(a);
  a
};

let decodeJSON = (decoder, json) =>
  try (Ok(json |> decoder)) {
  | Json_decode.DecodeError(err) => Error(err)
  };

let parseJSON = (jsonString) =>
  try (Ok(jsonString |> Js.Json.parseExn)) {
    | Js.Exn.Error(err) => switch (Js.Exn.message(err)) {
        | None => Error("Could not parse JSON")
        | Some(err) => Error(err)
    };
};
