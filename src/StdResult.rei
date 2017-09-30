type t 'x 'a = 
  | Error 'x
  | Ok 'a; 

let map : ('a => 'b) =>  t 'x 'a => t 'x 'b;
let map2 : ('a => 'b => 'c) =>  t 'x 'a => t 'x 'b => t 'x 'c;
let map3 : ('a => 'b => 'c => 'd) =>  t 'x 'a => t 'x 'b => t 'x 'c => t 'x 'd;
let flatten : t 'x (t 'x 'a) => t 'x 'a;
let flatMap : ('a  => t 'x 'b) => t 'x 'a => t 'x 'b;
let withDefault : 'a => t 'x 'a => 'a;
let fromOption : 'x => option 'a =>  t 'x 'a;
let isError : t 'x 'a => bool;
let isOk : t 'x 'a => bool;

