open Prelude;
let length: list('a) => int;
let isEmpty: list('a) => bool;
let reverse: list('a) => list('a);
let merge: (('a, 'a) => int, list('a), list('a)) => list('a);
/* create */
let repeat: (int, 'a) => list('a);
let range: (int, int) => list(int);
/* combining lists*/
let cons: ('a, list('a)) => list('a);
let append: (list('a), list('a)) => list('a);
let flatten: list(list('a)) => list('a);
let zip: (list('a), list('b)) => list(('a, 'b));
/* Sub lists */
let head: list('a) => option('a);
let tail: list('a) => list('a);
let nth: (int, list('a)) => option('a);
let take: (int, list('a)) => list('a);
let takeLast: (int, list('a)) => list('a);
let takeWhile: ('a => bool, list('a)) => list('a);
let takeUntil: ('a => bool, list('a)) => list('a);
let drop: (int, list('a)) => list('a);
let dropLast: (int, list('a)) => list('a);
let dropWhile: ('a => bool, list('a)) => list('a);
let dropUntil: ('a => bool, list('a)) => list('a);
let filter: ('a => bool, list('a)) => list('a);
/* map */
let map: ('a => 'b, list('a)) => list('b);
let mapIndexed: ((int, 'a) => 'b, list('a)) => list('b);
let map2: (('a, 'b) => 'c, list('a), list('b)) => list('c);
let flatMap: ('a => list('b), list('a)) => list('b);
let flatMap2: (('a, 'b) => list('c), list('a), list('b)) => list('c);
let filterMap: ('a => option('b), list('a)) => list('b);
/* iterate */
let iter: ('a => unit, list('a)) => unit;
let iter2: (('a, 'b) => unit, list('a), list('b)) => unit;
let iterIndexed: ((int, 'a) => unit, list('a)) => unit;
/* fold */
let foldLeft: (('a, 'b) => 'b, 'b, list('a)) => 'b;
let foldRight: (('a, 'b) => 'b, 'b, list('a)) => 'b;
let foldLeft2: (('a, 'b, 'c) => 'c, 'c, list('a), list('b)) => 'c;
let foldRight2: (('a, 'b, 'c) => 'c, 'c, list('a), list('b)) => 'c;
/* scan */
let find: ('a => bool, list('a)) => option('a);
let all: ('a => bool, list('a)) => bool;
let any: ('a => bool, list('a)) => bool;
let contains: ('a, list('a)) => bool;
/* misc */
let partition: ('a => bool, list('a)) => (list('a), list('a));
let split: list(('a, 'b)) => (list('a), list('b));
let sort: (('a, 'a) => int, list('a)) => list('a);
let encode: ('a => Js.Json.t, list('a)) => Js.Json.t;
let decode: (Js.Json.t => 'a, Js.Json.t) => list('a);