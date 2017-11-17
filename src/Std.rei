
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
module Async : {
    let none : async('a);
    let make : 'a => async('a);
    let map : ('a => 'b) => async('a) => async('b);
    let flatten: async(async('a)) => async('a);
    let flatMap : ('a => async('b)) => async('a) => async('b);
    let fromPromise : (unit => Js.Promise.t('a)) => async(result('a, 'x));
};
module Option : {
    let some: 'a => option('a);
    
      /*** returns an optional with the value 'a */
    let none: option('a);
    let map: ('a => 'b, option('a)) => option('b);
    let map2: (('a, 'b) => 'c, option('a), option('b)) => option('c);
    let map3: (('a, 'b, 'c) => 'd, option('a), option('b), option('c)) => option('d);
    let flatten: option(option('a)) => option('a);
    let flatMap: ('a => option('b), option('a)) => option('b);
    let withDefault: ('a, option('a)) => 'a;
    let fromResult: result('a, 'x) => option('a);
    let fromRemote: remote('a, 'x) => option('a);
    let isNone: option('a) => bool;
    let isSome: option('a) => bool;
    let encode: ('a => Js.Json.t, option('a)) => Js.Json.t;
    let decode: (Js.Json.t => 'a, Js.Json.t) => option('a);
};

module List : {
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
};

module Dict : {
    let empty: dict('key, 'value);
    let fromList: list(('key, 'value)) => dict('key, 'value);
    let get: ('key, dict('key, 'value)) => option('value);
    let find: ('value => bool, dict('key, 'value)) => option('value);
    let contains: ('key, dict('key, 'value)) => bool;
    let set: ('key, 'value, dict('key, 'value)) => dict('key, 'value);
    let setDefault: ('key, 'value, dict('key, 'value)) => dict('key, 'value);
    let keys: dict('key, 'value) => list('key);
    let values: dict('key, 'value) => list('value);
    let iter: (('key, 'value) => unit, dict('key, 'value)) => unit;
    let map: (('key, 'a) => 'b, dict('key, 'a)) => dict('key, 'b);
    let mapValues: ('a => 'b, dict('key, 'a)) => dict('key, 'b);
    let mapKeys: ('k1 => 'k2, dict('k1, 'value)) => dict('k2, 'value);
    let filter: (('key, 'value) => bool, dict('key, 'value)) => dict('key, 'value);
    let foldLeft: (('key, 'value, 'acc) => 'acc, 'acc, dict('key, 'value)) => 'acc;
    let foldRight: (('key, 'value, 'acc) => 'acc, 'acc, dict('key, 'value)) => 'acc;
    let encode: ('key => Js.Dict.key, 'value => Js.Json.t, dict('key, 'value)) => Js.Json.t;
    let decode: (Js.Dict.key => 'key, Js.Json.t => 'value, Js.Json.t) => dict('key, 'value);
};

module Remote : {
    let ready: 'a => remote('a, 'x);
    let error: 'x => remote('a, 'x);
    let pending: remote('a, 'x);
    let notAsked: remote('a, 'x);
    let map: ('a => 'b, remote('a, 'x)) => remote('b, 'x);
    let map2: (('a, 'b) => 'c, remote('a, 'x), remote('b, 'x)) => remote('c, 'x);
    let map3: (('a, 'b, 'c) => 'd, remote('a, 'x), remote('b, 'x), remote('c, 'x)) => remote('d, 'x);
    let flatten: remote(remote('a, 'x), 'x) => remote('a, 'x);
    let flatMap: ('a => remote('b, 'x), remote('a, 'x)) => remote('b, 'x);
    let withDefault: ('a, remote('a, 'x)) => 'a;
    let fromResult: result('a, 'x) => remote('a, 'x);
    let fromOption: option('a) => remote('a, 'x);
    let isNotAsked: remote('a, 'x) => bool;
    let isPending: remote('a, 'x) => bool;
    let isFailed: remote('a, 'x) => bool;
    let isReady: remote('a, 'x) => bool;
    let encode: ('a => Js.Json.t, 'x => Js.Json.t, remote('a, 'x)) => Js.Json.t;
};

module Result : {
    let map: ('a => 'b, result('a, 'x)) => result('b, 'x);
    let map2: (('a, 'b) => 'c, result('a, 'x), result('b, 'x)) => result('c, 'x);
    let map3: (('a, 'b, 'c) => 'd, result('a, 'x), result('b, 'x), result('c, 'x)) => result('d, 'x);
    let flatten: result(result('a, 'x), 'x) => result('a, 'x);
    let flatMap: ('a => result('b, 'x), result('a, 'x)) => result('b, 'x);
    let withDefault: ('a, result('a, 'x)) => 'a;
    let fromOption: ('x, option('a)) => result('a, 'x);
    let isError: result('a, 'x) => bool;
    let isOk: result('a, 'x) => bool;
    let encode: ('x => Js.Json.t, 'a => Js.Json.t, result('a, 'x)) => Js.Json.t;
};

module String : {
    
    let length: string => int;
    /* Return the length (number of characters) of the given string. */
    let isEmpty: string => bool;
    let fromChar: char => string;
    let fromInt: int => string;
    let fromFloat: float => string;
    let fromChars: list(char) => string;
    let escaped: string => string;
    let reverse: string => string;
    let uppercase: string => string;
    let lowercase: string => string;
    let capitalize: string => string;
    let uncapitalize: string => string;
    /* substrings */
    let get: (int, string) => option(char);
    let substring: (int, int, string) => string;
    let trim: string => string;
    let take: (int, string) => string;
    let drop: (int, string) => string;
    let takeLast: (int, string) => string;
    let dropLast: (int, string) => string;
    let takeUntil: (char => bool, string) => string;
    let takeWhile: (char => bool, string) => string;
    let dropUntil: (char => bool, string) => string;
    let dropWhile: (char => bool, string) => string;
    /* splitting strings */
    let split: (string, string) => list(string);
    let words: string => list(string);
    let lines: string => list(string);
    /* combining strings */
    let cons: (char, string) => string;
    let uncons: string => option((char, string));
    let append: (string, string) => string;
    let join: (string, list(string)) => string;
    let pad: (int, string, string) => string;
    let leftPad: (int, string, string) => string;
    let rightPad: (int, string, string) => string;
    /* iterate */
    let iter: (char => unit, string) => unit;
    let iterIndexed: ((int, char) => unit, string) => unit;
    let map: (char => char, string) => string;
    let mapIndexed: ((int, char) => char, string) => string;
    /* find ind string */
    let indexOf: (char, string) => option(int);
    let lastIndexOf: (char, string) => option(int);
    let indexFrom: (int, char, string) => option(int);
    let lastIndexFrom: (int, char, string) => option(int);
    let contains: (char, string) => bool;
    let encode: string => Js.Json.t;
    let decode: Js.Json.t => string;
};