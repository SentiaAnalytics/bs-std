
let identity: 'a => 'a;
let always: 'a => 'b => 'a;

let void : 'a => unit;

let (>>) : ('a => 'b) => ('b => 'c) => ('a => 'c);

let flip : ('a => 'b => 'c) => ('b => 'a => 'c);

let curry: (('a, 'b) => 'c) => 'a => 'b => 'c;

let uncurry:  ('a => 'b => 'c) => ('a, 'b) => 'c;

let tap: ('a => unit) => 'a =>  'a;

type remote 'x 'a = 
  | NotAsked
  | Pending
  | Failed 'x
  | Ready 'a;
  
type result 'x 'a =
  | Error 'x
  | Ok 'a;
  
type task 'err 'ok;

module Remote: {
  let ready : 'a => remote 'x 'a;
  
  let error : 'x => remote 'x 'a;
  
  let pending : remote 'x 'a;
  
  let notAsked : remote 'x 'a;
  
  let map : ('a => 'b ) => remote 'x 'a => remote 'x 'b;
  let map2 : ('a => 'b => 'c) => remote 'x 'a => remote 'x 'b => remote 'x 'c;
  let map3 : ('a => 'b => 'c => 'd) => remote 'x 'a => remote 'x 'b => remote 'x 'c => remote 'x 'd;
  
  let flatten : remote 'x (remote 'x 'a) => remote 'x 'a;
  let flatMap : ('a => remote 'x 'b ) => remote 'x 'a => remote 'x 'b;
  
  let withDefault : 'a => remote 'x 'a => 'a;
  
  let fromResult : result 'x 'a => remote 'x 'a;
  let fromOption : option 'a => remote 'x 'a;
    
  let isNotAsked : remote 'x 'a => bool;
  let isPending : remote 'x 'a => bool;
  let isFailed : remote 'x 'a => bool;
  let isReady : remote 'x 'a => bool;
};

module Result: {
  
  let map : ('a => 'b) =>  result 'x 'a => result 'x 'b;
  let map2 : ('a => 'b => 'c) =>  result 'x 'a => result 'x 'b => result 'x 'c;
  let map3 : ('a => 'b => 'c => 'd) =>  result 'x 'a => result 'x 'b => result 'x 'c => result 'x 'd;
  let flatten : result 'x (result 'x 'a) => result 'x 'a;
  let flatMap : ('a  => result 'x 'b) => result 'x 'a => result 'x 'b;
  let withDefault : 'a => result 'x 'a => 'a;
  let fromOption : 'x => option 'a =>  result 'x 'a;
  let isError : result 'x 'a => bool;
  let isOk : result 'x 'a => bool;
};

module List : {
  let length: list 'a => int; 
  
  let isEmpty: list 'a => bool; 
  
  let reverse: list 'a => list 'a;
  
  let merge: ('a => 'a => int) => list 'a => list 'a => list 'a;
  
  /* create */
  
  let repeat : int => 'a => list 'a;
  
  let range : int => int => list int;
  
  /* combining lists*/
  
  let append: 'a => list 'a => list 'a;
  
  let concat: list 'a =>  list 'a => list 'a;
  
  let flatten: list (list 'a) => list 'a;
  
  let zip: list 'a => list 'b => list ('a, 'b); 
  
  
  /* Sub lists */
  
  let head: list 'a => option 'a;
  
  let tail: list 'a => list 'a;
  
  let nth: int => list 'a => option 'a;
  
  let take: int => list 'a => list 'a;
  
  let takeLast: int => list 'a => list 'a;
  
  let takeWhile: ('a => bool) => list 'a => list 'a;
  
  let takeUntil: ('a => bool) => list 'a => list 'a;
  
  let drop: int => list 'a => list 'a;
  
  let dropLast: int => list 'a => list 'a;
  
  let dropWhile: ('a => bool) => list 'a => list 'a;
  
  let dropUntil: ('a => bool) => list 'a => list 'a;
  
  let filter: ('a => bool) => list 'a => list 'a;
  
  
  /* map */
  
  let map: ('a => 'b) => list 'a => list 'b;
  
  let mapIndexed: (int => 'a => 'b) => list 'a => list 'b;
  
  let map2: ('a => 'b => 'c) => list 'a => list 'b => list 'c;
  
  let flatMap: ('a => list 'b) => list 'a => list 'b;
  
  let flatMap2: ('a => 'b => list 'c) => list 'a => list 'b => list 'c;
  
  
  /* iterate */
  
  
  let iter: ('a => unit) => list 'a => unit;
  
  let iter2: ('a  => 'b => unit) => list 'a => list 'b => unit;
  
  let iterIndexed: (int => 'a => unit) => list 'a => unit;
  
  
  /* fold */
  
  let foldLeft: ('a => 'b => 'a) => 'a => list 'b => 'a;
  
  let foldRight: ('a => 'b => 'b) => 'b => list 'a => 'b;
  
  let foldLeft2: ('a => 'b => 'c => 'a) => 'a => list 'b => list 'c => 'a;
  
  let foldRight2: ('a => 'b => 'c => 'c) => 'c => list 'a => list 'b => 'c;
  
  
  /* scan */
  
  let find: ('a => bool) => list 'a => option 'a;
  
  let all: ('a => bool) => list 'a => bool;
  
  let any: ('a => bool) => list 'a => bool;
  
  let contains: 'a => list 'a => bool;
  
  /* misc */
  
  let partition: ('a => bool) => list 'a => (list 'a, list 'a);
  
  let split: list ('a, 'b) => (list 'a, list 'b);
  
  let sort: ('a => 'a => int) => list 'a => list 'a;
  
};

module String : {
  let length: string => int;
  /* Return the length (number of characters) of the given string. */
  
  let isEmpty : string => bool;
  
  let fromChar: char => string;
  
  let fromInt : int => string;
  
  let fromFloat : float => string;
  
  let fromChars : list char => string;
  
  let escaped: string => string;
  
  let reverse: string => string;
  
  let uppercase: string => string;
  
  let lowercase: string => string;
  
  let capitalize: string => string;
  
  let uncapitalize: string => string;
  
  /* substrings */
  
  let get: int => string => option char;
  
  let substring: int => int => string => string;
  
  let trim: string => string;
  
  let take : int => string => string;
  
  let drop : int => string => string;
  
  let takeLast : int => string => string;
  
  let dropLast : int => string => string;
  
  let takeUntil : (char => bool) => string => string;
  
  let takeWhile : (char => bool) => string => string;
  
  let dropUntil : (char => bool) => string => string;
  
  let dropWhile : (char => bool) => string => string;
  
  /* splitting strings */
  
  let split: string => string => list string;
  
  let words: string => list string;
  
  let lines: string => list string;
  
  /* combining strings */
  
  let cons: char => string => string;
  
  let uncons: string => option (char, string);
  
  let concat : string => string => string;
  
  let join: string => list string => string;
  
  let pad: int => string => string => string;
  
  let leftPad: int => string => string => string;
  
  let rightPad: int => string => string => string;
  
  /* iterate */
  
  let iter: (char => unit) => string => unit;
  
  let iterIndexed: (int => char => unit) => string => unit;
  
  let map: (char => char) => string => string;
  
  let mapIndexed: (int => char => char) => string => string;
  
  /* find ind string */
  
  let indexOf: char => string => option int;
  
  let lastIndexOf: char => string => option int;
  
  let indexFrom: int => char => string => option int;
  
  let lastIndexFrom: int => char => string => option int;
  
  let contains: char => string => bool;
  
};

module Task : {
  
  let make : (('x => unit) => ('a => unit) => unit) => task 'x 'a;
  
  let succeed : 'a => task 'x 'a;
  
  let fail : 'x => task 'x 'a;
  
  let map : ('a => 'b) => task 'x 'a => task 'x 'b;
  
  let map2 : ('a => 'b => 'c) => task 'x 'a => task 'x 'b => task 'x 'c;
  
  let map3 : ('a => 'b => 'c => 'd) => task 'x 'a => task 'x 'b => task 'x 'c => task 'x 'd;
  
  let biMap : ('x => 'y) => ('a => 'b) => task 'x 'a => task 'y 'b;
  
  let flatMap : ('a => task 'x 'b) => task 'x 'a => task 'x 'b;
  
  let fold : ('x => 'b) => ('a => 'b) => task 'x 'a => task unit 'b;
  
  let fromResult : result 'x 'a => task 'x 'a;
  
  let fromOption : 'x => option 'a => task 'x 'a;
  
  let fork : ('x => unit) => ('a => unit) => task 'x 'a => unit;
  
  let fromLazyPromise : (unit => Js.Promise.t 'a) =>  task 'x 'a;
  
};

module Option : {
  let some : 'a => option 'a; 
  /** returns an optional with the value 'a */
  
  
  let none : option 'a;
  let map : ('a => 'b) =>  option 'a => option 'b;
  let map2 : ('a => 'b => 'c) =>  option 'a => option 'b => option 'c;
  let map3 : ('a => 'b => 'c => 'd) =>  option 'a => option 'b => option 'c => option 'd;
  
  let flatten : option (option 'a) => option 'a;
  let flatMap : ('a  => option 'b) => option 'a => option 'b;
  let withDefault : 'a => option 'a => 'a;
  let fromResult : result 'x 'a => option 'a;
  let fromRemote : remote 'x 'a => option 'a;
  let isNone : option 'a => bool;
  let isSome : option 'a => bool;
};