include Js.Result;
type async('a) = ('a => unit) => unit;

type remote('a, 'x) = 
  | NotAsked
  | Pending
  | Failed('x)
  | Ready('a);
  
type result('a, 'b) = Js.Result.t('a, 'b) = | Ok('a) | Error('b);
  
type dict('k, 'v) = list(('k, 'v));
let identity = (a) => a;

let always = (a, _) => a;

let void = (_) => ();

let (>>) = (f, g, x) => g(f(x));

let flip = (f, a, b) => f(b, a);

let curry = (f, a, b) => f((a, b));

let uncurry = (f, (a, b)) => f(a, b);

let tap = (f, a) => {
  f(a);
  a
};

let decodeJSON = (decoder, json) =>
  try (Ok(json |> decoder)) {
  | Json_decode.DecodeError(err) => Error(err)
  };

let parseJSON = (jsonString) =>
  try (Ok(jsonString |> Js.Json.parseExn)) {
    | Js.Exn.Error(err) => switch (Js.Exn.message(err)) {
        | None => Error("Could not parse JSON")
        | Some(err) => Error(err)
    };
};
module Async = {
  let none = (_) => ();
  let make = (a) => ((cb) => cb(a));
  let map = (f, a) => (cb) => a(f >> cb);
  let flatten = (a) => (cb) => a((b) => b(cb));
  let flatMap = (f, a) => flatten @@ map(f, a);
};

module Option = {
  
  let some = (a) => Some(a);
  
  let none = None;
  
  let map = (f, opt) =>
    switch opt {
    | None => None
    | Some(x) => Some(f(x))
    };
  
  let map2 = (f, opt1, opt2) =>
    switch (opt1, opt2) {
    | (Some(a1), Some(a2)) => Some(f(a1, a2))
    | _ => None
    };
  
  let map3 = (f, opt1, opt2, opt3) =>
    switch (opt1, opt2, opt3) {
    | (Some(a1), Some(a2), Some(a3)) => Some(f(a1, a2, a3))
    | _ => None
    };
  
  let flatten = (opt) =>
    switch opt {
    | None => None
    | Some(a) => a
    };
  
  let flatMap = (f, opt) =>
    switch opt {
    | None => None
    | Some(x) => f(x)
    };
  
  let withDefault = (defaultValue, opt) =>
    switch opt {
    | Some(x) => x
    | None => defaultValue
    };
  
  let fromResult = (res) =>
    switch res {
    | Error(_) => None
    | Ok(v) => Some(v)
    };
  
  let fromRemote = (res) =>
    switch res {
    | Ready(a) => Some(a)
    | _ => None
    };
  
  let isNone =
    fun
    | None => true
    | _ => false;
  
  let isSome =
    fun
    | None => false
    | _ => true;
  
  let encode = (encoder) =>
    fun
    | None => Js.Json.null
    | Some(v) => encoder(v);
  
  let decode = Json.Decode.optional;
};

module List =  {

  let length = List.length;

  let reverse = (xs) => {
    let rec go = (acc, xs) =>
      switch xs {
      | [] => acc
      | [x, ...xs] => go([x, ...acc], xs)
      };
    go([], xs)
  };

  let isEmpty = (xs) =>
    switch xs {
    | [] => true
    | _ => false
    };

  /* folds */
  let rec foldLeft = (f, acc, xs) =>
    switch xs {
    | [] => acc
    | [x, ...xs] => foldLeft(f, f(x, acc), xs)
    };

  let rec foldRight = (f, acc, xs) =>
    switch xs {
    | [] => acc
    | [x, ...xs] => f(x, foldRight(f, acc, xs))
    };

  let rec foldLeft2 = (f, acc, xs, ys) =>
    switch (xs, ys) {
    | ([], _)
    | (_, []) => acc
    | ([x, ...xs], [y, ...ys]) => foldLeft2(f, f(x, y, acc), xs, ys)
    };

  let rec foldRight2 = (f, acc, xs, ys) =>
    switch (xs, ys) {
    | ([], _)
    | (_, []) => acc
    | ([x, ...xs], [y, ...ys]) => f(x, y, foldRight2(f, acc, xs, ys))
    };

  /* create */
  let repeat = (count, x) => {
    let rec go = (acc, count) =>
      if (count <= 0) {
        acc
      } else {
        go([x, ...acc], count - 1)
      };
    go([], count)
  };

  let range = (start, stop) => {
    let rec go = (acc, start) =>
      if (start >= stop) {
        acc
      } else {
        [start, ...go(acc, start + 1)]
      };
    go([], start)
  };

  /* combining lists*/
  let cons = (x, xs) => xs @ [x];

  let append = (xs, ys) => xs @ ys;

  let flatten = (xs) => foldLeft(append, [], xs);

  let rec zip = (xs, ys) =>
    switch (xs, ys) {
    | ([], _)
    | (_, []) => []
    | ([x, ...xs], [y, ...ys]) => [(x, y), ...zip(xs, ys)]
    };

  let merge = List.merge;

  /* Sub lists */
  let head = (xs) =>
    switch xs {
    | [] => None
    | [x, ..._] => Some(x)
    };

  let tail = (xs) =>
    switch xs {
    | [] => []
    | [_, ...xs] => xs
    };

  let rec nth = (i, xs) =>
    switch (i, xs) {
    | (_, []) => None
    | (i, [x, ..._]) when i <= 0 => Some(x)
    | (i, [_, ...xs]) => nth(i - 1, xs)
    };

  let rec take = (count, xs) =>
    switch (count, xs) {
    | (_, []) => []
    | (i, _) when i <= 0 => []
    | (count, [x, ...xs]) => [x, ...take(count - 1, xs)]
    };

  let rec drop = (count, xs) =>
    switch (count, xs) {
    | (_, []) => []
    | (i, _) when i <= 0 => []
    | (count, [_, ...xs]) => drop(count - 1, xs)
    };

  let takeLast = (count, xs) => drop(length(xs) - count, xs);

  let takeUntil = (f, xs) => {
    let rec go = (acc, f, xs) =>
      switch xs {
      | [] => acc
      | [x, ..._] when f(x) => acc
      | [x, ...xs] => go([x, ...acc], f, xs)
      };
    go([], f, xs)
  };

  let takeWhile = (f, xs) => takeUntil((a) => ! f(a), xs);

  let dropLast = (count, xs) => take(length(xs) - count, xs);

  let rec dropUntil = (f, xs) =>
    switch xs {
    | [] => []
    | [x, ..._] when f(x) => xs
    | [_, ...xs] => dropUntil(f, xs)
    };

  let dropWhile = (f, xs) => dropUntil((x) => f(x) |> (!), xs);

  let rec filter = (f, xs) =>
    switch xs {
    | [] => []
    | [x, ...xs] when f(x) => [x, ...filter(f, xs)]
    | [_, ...xs] => filter(f, xs)
    };

  /* map */
  let rec map = (f, xs) =>
    switch xs {
    | [] => []
    | [x, ...xs] => [f(x), ...map(f, xs)]
    };

  let mapIndexed = (f, xs) => {
    let rec go = (i, f, xs) =>
      switch xs {
      | [] => []
      | [x, ...xs] => [f(i, x), ...go(i + 1, f, xs)]
      };
    go(0, f, xs)
  };

  let rec map2 = (f, xs, ys) =>
    switch (xs, ys) {
    | (_, [])
    | ([], _) => []
    | ([x, ...xs], [y, ...ys]) => [f(x, y), ...map2(f, xs, ys)]
    };

  let rec flatMap = (f, xs) =>
    switch xs {
    | [] => []
    | [x, ...xs] => f(x) @ flatMap(f, xs)
    };

  let rec flatMap2 = (f, xs, ys) =>
    switch (xs, ys) {
    | ([], _)
    | (_, []) => []
    | ([x, ...xs], [y, ...ys]) => f(x, y) @ flatMap2(f, xs, ys)
    };

  let rec filterMap = (f, xs) =>
    switch xs {
    | [] => []
    | [x, ...xs] =>
      switch (f(x)) {
      | Some(x) => [x, ...filterMap(f, xs)]
      | None => filterMap(f, xs)
      }
    };

  /* iterate */
  let rec iter = (f, xs) =>
    switch xs {
    | [] => ()
    | [x, ...xs] =>
      f(x);
      iter(f, xs)
    };

  let rec iter2 = (f, xs, ys) =>
    switch (xs, ys) {
    | ([], _)
    | (_, []) => ()
    | ([x, ...xs], [y, ...ys]) =>
      f(x, y);
      iter2(f, xs, ys)
    };

  let iterIndexed = (f, xs) => {
    let rec go = (i, f, xs) =>
      switch xs {
      | [] => ()
      | [x, ...xs] =>
        f(i, x);
        go(i + 1, f, xs)
      };
    go(0, f, xs)
  };

  /* scan */
  let rec find = (f, xs) =>
    switch xs {
    | [] => None
    | [x, ..._] when f(x) => Some(x)
    | [_, ...xs] => find(f, xs)
    };

  let any = (f, xs) => find(f, xs) |> Option.isSome;

  let all = (f, xs) => any((x) => f(x) |> (!), xs);

  let contains = (y, xs) => any((x) => x == y, xs);

  /* misc */
  let partition = (f, xs) => {
    let rec go = ((l1, l2), f, xs) =>
      switch xs {
      | [] => (l1, l2)
      | [x, ...xs] when f(x) => go(([x, ...l1], l2), f, xs)
      | [x, ...xs] => go((l1, [x, ...l2]), f, xs)
      };
    go(([], []), f, xs)
  };

  let split = (pairs) => {
    let rec go = ((xs, ys), pairs) =>
      switch pairs {
      | [] => (xs, ys)
      | [(x, y), ...pairs] => go(([x, ...xs], [y, ...ys]), pairs)
      };
    go(([], []), pairs)
  };

  let sort = List.sort;

  let encode = Json.Encode.list;

  let decode = Json.Decode.list;

};

module Dict = {
  let empty = [];
  
  let fromList = (a) => a;
  
  let rec get = (key, dict) =>
    switch dict {
    | [] => None
    | [(k, v), ..._] when k == key => Some(v)
    | [_, ...dict] => get(key, dict)
    };
  
  let rec find = (f, dict) =>
    switch dict {
    | [] => None
    | [(_, v), ..._] when f(v) => Some(v)
    | [_, ...dict] => find(f, dict)
    };
  
  let contains = (key, dict) => get(key, dict) |> Option.isSome;
  
  let set = (key, value, dict) => [(key, value), ...List.filter(((k, _)) => k != key, dict)];
  
  let setDefault = (key, value, dict) =>
    if (contains(key, dict)) {
      dict
    } else {
      [(key, value), ...dict]
    };
  
  let keys = (dict) => List.map(((k, _)) => k, dict);
  
  let values = (dict) => List.map(((_, v)) => v, dict);
  
  let iter = (f) => List.iter(uncurry(f));
  
  let map = (f, dict) => List.map(((k, v)) => (k, f(k, v)), dict);
  
  let mapValues = (f, dict) => List.map(((k, v)) => (k, f(v)), dict);
  
  let mapKeys = (f, dict) => List.map(((k, v)) => (f(k), v), dict);
  
  let filter = (f) => List.filter(uncurry(f));
  
  let foldLeft = (f, acc, dict) => List.foldLeft(((k, v), acc) => f(k, v, acc), acc, dict);
  
  let foldRight = (f, acc, dict) => List.foldRight(((k, v), acc) => f(k, v, acc), acc, dict);
  
  let encode = (encodeKey, encodeValue, dict) =>
    dict |> mapKeys(encodeKey) |> mapValues(encodeValue) |> Json.Encode.object_;
  
  let decode = (decodeKey, decodeValue, json) =>
    json |> Json.Decode.dict(decodeValue) |> Js.Dict.entries |> Array.to_list |> mapKeys(decodeKey);
  
};

module Remote = {
  let ready = (a) => Ready(a);
  
  let error = (x) => Failed(x);
  
  let notAsked = NotAsked;
  
  let pending = Pending;
  
  let map = (f, remote) =>
    switch remote {
    | NotAsked => NotAsked
    | Pending => Pending
    | Failed(e) => Failed(e)
    | Ready(x) => Ready(f(x))
    };
  
  let map2 = (f, r1, r2) =>
    switch (r1, r2) {
    | (Ready(a1), Ready(a2)) => Ready(f(a1, a2))
    | (NotAsked, _) => NotAsked
    | (Pending, _) => Pending
    | (Failed(x), _) => Failed(x)
    | (Ready(_), NotAsked) => NotAsked
    | (Ready(_), Pending) => Pending
    | (Ready(_), Failed(x)) => Failed(x)
    };
  
  let map3 = (f, r1, r2, r3) =>
    switch (r1, r2, r3) {
    | (Ready(a1), Ready(a2), Ready(a3)) => Ready(f(a1, a2, a3))
    | (NotAsked, _, _) => NotAsked
    | (Pending, _, _) => Pending
    | (Failed(x), _, _) => Failed(x)
    | (Ready(_), NotAsked, _) => NotAsked
    | (Ready(_), Pending, _) => Pending
    | (Ready(_), Failed(x), _) => Failed(x)
    | (Ready(_), Ready(_), NotAsked) => NotAsked
    | (Ready(_), Ready(_), Pending) => Pending
    | (Ready(_), Ready(_), Failed(x)) => Failed(x)
    };
  
  let flatten = (r) =>
    switch r {
    | NotAsked => NotAsked
    | Pending => Pending
    | Failed(e) => Failed(e)
    | Ready(a) => a
    };
  
  let flatMap = (f, remote) =>
    switch remote {
    | NotAsked => NotAsked
    | Pending => Pending
    | Failed(e) => Failed(e)
    | Ready(x) => f(x)
    };
  
  let withDefault = (a, rem) =>
    switch rem {
    | Ready(a) => a
    | _ => a
    };
  
  let fromResult = (res) =>
    switch res {
    | Ok(a) => Ready(a)
    | Error(x) => Failed(x)
    };
  
  let fromOption = (opt) =>
    switch opt {
    | None => NotAsked
    | Some(a) => Ready(a)
    };
  
  let isNotAsked = (remote) =>
    switch remote {
    | NotAsked => true
    | _ => false
    };
  
  let isPending = (remote) =>
    switch remote {
    | Pending => true
    | _ => false
    };
  
  let isFailed = (remote) =>
    switch remote {
    | Failed(_) => true
    | _ => false
    };
  
  let isReady = (remote) =>
    switch remote {
    | Ready(_) => true
    | _ => false
    };
  
  let encode = (successEncoder, failEncoder, r) =>
    Json.Encode.(
      switch r {
      | Ready(r) => successEncoder(r)
      | Failed(err) => failEncoder(err)
      | NotAsked => string("NotAsked")
      | Pending => string("Pending")
      }
    );

};

module Result = {
  let map = (f, res) =>
    switch res {
    | Error(x) => Error(x)
    | Ok(a) => Ok(f(a))
    };
  
  let map2 = (f, r1, r2) =>
    switch (r1, r2) {
    | (Ok(a1), Ok(a2)) => Ok(f(a1, a2))
    | (Error(x), _) => Error(x)
    | (_, Error(x)) => Error(x)
    };
  
  let map3 = (f, r1, r2, r3) =>
    switch (r1, r2, r3) {
    | (Ok(a1), Ok(a2), Ok(a3)) => Ok(f(a1, a2, a3))
    | (Error(x), _, _) => Error(x)
    | (_, Error(x), _) => Error(x)
    | (_, _, Error(x)) => Error(x)
    };
  
  let flatten = (r) =>
    switch r {
    | Error(e) => Error(e)
    | Ok(a) => a
    };
  
  let flatMap = (f, res) =>
    switch res {
    | Error(x) => Error(x)
    | Ok(a) => f(a)
    };
  
  let withDefault = (a, res) =>
    switch res {
    | Error(_) => a
    | Ok(a) => a
    };
  
  let fromOption = (err, opt) =>
    switch opt {
    | None => Error(err)
    | Some(a) => Ok(a)
    };
  
  let isError = (res) =>
    switch res {
    | Error(_) => true
    | _ => false
    };
  
  let isOk = (res) =>
    switch res {
    | Ok(_) => true
    | _ => false
    };
  
  let encode = (encodeError, encodeOk) =>
    fun
    | Error(e) => encodeError(e)
    | Ok(v) => encodeOk(v);

};

module String = {
  
  let length = String.length;
  
  let isEmpty = (s) => s == "";
  
  let fromChar = String.make(1);
  
  let fromChars = (chars) => List.foldLeft((ch, str) => str ++ fromChar(ch), "", chars);
  
  let fromFloat = string_of_float;
  
  let fromInt = string_of_int;
  
  let get = (index, str) =>
    try (Some(str.[index])) {
    | Invalid_argument(_) => None
    };
  
  let cons = (ch, str) => String.make(1, ch) ++ str;
  
  let substring = (start, len, str) =>
    try (String.sub(str, start, min(len, length(str) - start))) {
    | Invalid_argument(_) => ""
    };
  
  let uncons = (str) =>
    switch (get(0, str)) {
    | None => None
    | Some(ch) => Some((ch, substring(1, length(str), str)))
    };
  
  let take = (i, str) => substring(0, i, str);
  
  let drop = (i, str) => substring(i, length(str), str);
  
  let takeLast = (i, str) => drop(length(str) - i, str);
  
  let dropLast = (i, str) => take(length(str) - i, str);
  
  let rec takeUntil = (f, str) =>
    switch (uncons(str)) {
    | None => ""
    | Some((ch, _)) when f(ch) => ""
    | Some((ch, str)) => fromChar(ch) ++ takeUntil(f, str)
    };
  
  let takeWhile = (f, str) => takeUntil((x) => f(x) |> (!), str);
  
  let rec dropUntil = (f, str) =>
    switch (uncons(str)) {
    | None => ""
    | Some((ch, str)) when f(ch) => str
    | Some((_, str)) => dropUntil(f, str)
    };
  
  let dropWhile = (f, str) => dropUntil((x) => f(x) |> (!), str);
  
  let rec reverse = (s) =>
    switch (uncons(s)) {
    | None => ""
    | Some((ch, s)) => reverse(s) ++ fromChar(ch)
    };
  
  let append = (x, y) => x ++ y;
  
  let join = String.concat;
  
  let iter = String.iter;
  
  let iterIndexed = String.iteri;
  
  let map = String.map;
  
  let mapIndexed = String.mapi;
  
  let trim = String.trim;
  
  let escaped = String.escaped;
  
  let indexOf = (ch, str) =>
    try (Some(String.index(str, ch))) {
    | Not_found => None
    };
  
  let lastIndexOf = (ch, str) =>
    try (Some(String.rindex(str, ch))) {
    | Not_found => None
    };
  
  let indexFrom = (i, ch, str) =>
    try (Some(String.index_from(str, i, ch))) {
    | Not_found => None
    };
  
  let lastIndexFrom = (i, ch, str) =>
    try (Some(String.rindex_from(str, i, ch))) {
    | Not_found => None
    };
  
  /* String.rindex_from s i c returns the index of the last occurrence of character c in string s before position i+1. String.rindex s c is equivalent to String.rindex_from s (String.length s - 1) c. */
  let contains = (c, s) => String.contains(s, c);
  
  /* String.contains s c tests if character c appears in the string s. */
  let uppercase = String.uppercase;
  
  let lowercase = String.lowercase;
  
  let capitalize = String.capitalize;
  
  let uncapitalize = String.uncapitalize;
  
  let rec pad = (i, padding, str) =>
    if (i <= 0) {
      str
    } else {
      pad(i - 1, padding ++ (str ++ padding), str)
    };
  
  let rec leftPad = (i, padding, str) =>
    if (i <= 0) {
      str
    } else {
      leftPad(i - 1, padding ++ str, str)
    };
  
  let rec rightPad = (i, padding, str) =>
    if (i <= 0) {
      str
    } else {
      rightPad(i - 1, str ++ padding, str)
    };
  
  let split = (separator, str) => {
    let len = length(separator);
    let rec go = (i, str) => {
      let sub = substring(i, len, str);
      switch () {
      | () when sub == separator => [take(i, str), ...go(0, drop(i + len, str))]
      | () when i == length(str) => [str]
      | () => go(i + 1, str)
      }
    };
    go(0, str)
  };
  
  let lines = split("\n");
  
  let words = split(" ");
  
  let encode = Json.Encode.string;
  
  let decode = Json.Decode.string;

};