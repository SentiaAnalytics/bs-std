
let identity a => a;
let always a _ => a;

let void  _ => ();

let (>>) f g x => g (f x);

let flip f a b => f b a;

let curry f a b => f (a, b);

let uncurry f (a, b) => f a b;

let tap f a =>  {
  f a;
  a;
};

let decodeJSON decoder json => {
  try (Ok (json |> decoder)) {
  | Json_decode.DecodeError err => Error err
  }
};

let parseJSON jsonString => {
  try (Ok (jsonString |> Js.Json.parseExn)) {
  | Js.Exn.Error err => Error (Js.Exn.message err |> Option.withDefault "Could not parse JSON")
  }
};

include Types;

module Option = {
  include Option
};


module Remote = {
  include Remote;
};

module Result = {
  include Result;
};

module List = {
  include List;
};

module Dict = {
  include Dict;
};

module String = {
  include String;
};

module Task = {
  include Task;
};


