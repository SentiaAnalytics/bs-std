
let id : 'a => 'a;

let always : 'a => 'b => 'a;
let noOp : 'a => unit;

let (>>) : ('a => 'b ) => ('b => 'c) => ('a => 'c);

let flip : ('a => 'b => 'c) => 'b => 'a => 'c;

let tap : ('a => unit) => 'a => 'a;
