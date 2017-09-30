
type t 'err 'ok =
  | NotAsked
  | Pending
  | Error 'err
  | Ready 'ok
  ;

let ready : 'a => t 'x 'a;

let error : 'x => t 'x 'a;

let pending : t 'x 'a;

let notAsked : t 'x 'a;

let map : ('a => 'b ) => t 'err 'a => t 'err 'b;
let map2 : ('a => 'b => 'c) => t 'err 'a => t 'err 'b => t 'err 'c;
let map3 : ('a => 'b => 'c => 'd) => t 'err 'a => t 'err 'b => t 'err 'c => t 'err 'd;

let flatten : t 'x (t 'x 'a) => t 'x 'a;
let flatMap : ('a => t 'err 'b ) => t 'err 'a => t 'err 'b;

let withDefault : 'a => t 'x 'a => 'a;

let fromResult : StdResult.t 'x 'a => t 'x 'a;
let fromOption : option 'a => t 'x 'a;
  
let isNotAsked : t 'err 'value => bool;
let isPending : t 'err 'value => bool;
let isError : t 'err 'value => bool;
let isReady : t 'err 'value => bool;