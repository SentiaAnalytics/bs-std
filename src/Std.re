module Option = StdOption;
module Remote = StdRemote;
module Result = StdResult;
module Task = StdTask;
module List = StdList;

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



