
type async('a) = ('a => unit) => unit;

type remote('a, 'x) = 
  | NotAsked
  | Pending
  | Failed('x)
  | Ready('a);
  
type result('a, 'b) = Js.Result.t('a, 'b) = | Ok('a) | Error('b);
  

type dict('k, 'v) = list(('k, 'v));
let identity : 'a => 'a;

let always : ('a, 'b) => 'a;

let void : ('a) => unit;

let (>>) : ('a => 'b) => ('b => 'c) => ('a => 'c);

let flip : ('a => 'b => 'c) => ('b => 'a => 'c);

let curry : ((('a, 'b)) => 'c) => 'a => 'b => 'c;

let uncurry : ('a => 'b => 'c) => ((('a, 'b)) => 'c);

let tap : ('a => unit) => 'a => 'a;
let decodeJSON : (Js.Json.t => 'a) => Js.Json.t => result('a, string);

let parseJSON : string => result(Js.Json.t, string);
