open Prelude;

let length = String.length;

let isEmpty = (s) => s == "";

let fromChar = String.make(1);

let fromChars = (chars) => StdList.foldLeft((ch, str) => str ++ fromChar(ch), "", chars);

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
