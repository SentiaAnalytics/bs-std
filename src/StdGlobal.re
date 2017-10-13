
let identity a => a;

type remote 'err 'ok = StdRemote.t 'err 'ok;

type result 'x 'a = StdResult.t 'x 'a;

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