type t 'x 'a;

let make : (('x => unit) => ('a => unit) => unit) => t 'x 'a;

let succeed : 'a => t 'x 'a;

let fail : 'x => t 'x 'a;

let map : ('a => 'b) => t 'x 'a => t 'x 'b;

let map2 : ('a => 'b => 'c) => t 'x 'a => t 'x 'b => t 'x 'c;

let map3 : ('a => 'b => 'c => 'd) => t 'x 'a => t 'x 'b => t 'x 'c => t 'x 'd;

let biMap : ('x => 'y) => ('a => 'b) => t 'x 'a => t 'y 'b;

let flatMap : ('a => t 'x 'b) => t 'x 'a => t 'x 'b;

let fold : ('x => 'b) => ('a => 'b) => t 'x 'a => t unit 'b;

let fromResult : StdResult.t 'x 'a => t 'x 'a;

let fromOption : 'x => option 'a => t 'x 'a;

let fork : ('x => unit) => ('a => unit) => t 'x 'a => unit;

let fromLazyPromise : (unit => Js.Promise.t 'a) =>  t 'x 'a;

let delay : int => t unit unit; 