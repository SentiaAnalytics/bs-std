let some : 'a => option 'a;
let none : option 'a;
let map : ('a => 'b) =>  option 'a => option 'b;
let map2 : ('a => 'b => 'c) =>  option 'a => option 'b => option 'c;
let map3 : ('a => 'b => 'c => 'd) =>  option 'a => option 'b => option 'c => option 'd;
let chain : ('a  => option 'b) => option 'a => option 'b;
let bind : ('a  => option 'b) => option 'a => option 'b;
let withDefault : 'a => option 'a => 'a;
let fromResult : Result.t 'x 'a => option 'a;
let fromRemote : Remote.t 'x 'a => option 'a;
let isNone : option 'a => bool;
let isSome : option 'a => bool;