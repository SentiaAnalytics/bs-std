open Prelude;

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