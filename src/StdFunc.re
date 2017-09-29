
let id a => a;



let always a _ => a;

let noOp  _ => ();

let (>>) f g x => g (f x);

let flip f a b => f b a;

let tap f a =>  {
  f a;
  a;
};

StdList.length [];
List.length [];