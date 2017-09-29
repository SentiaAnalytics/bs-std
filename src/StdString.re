let length = String.length;

let get index str =>
  try (Some (String.get str index)) {
  | Invalid_argument _ => None
  };

let make = String.make;

let init = String.init;

let sub start len str => 
  try (String.sub str start len) {
    | Invalid_argument _ => ""
  };


let concat x y => x ^ y;

let join = String.concat;


let iter = String.iter;

let iteri = String.iteri;

let map = String.map;

let mapi = String.mapi;

let trim = String.trim;

let escaped = String.escaped;

let indexOf ch str =>
  try (Some (String.index str ch)) {
  | Not_found => None 
  };

let lastIndexOf ch str =>
  try (Some (String.rindex str ch)) {
  | Not_found => None 
  };

let indexFrom i ch str =>
  try (Some (String.index_from str i ch)) {
  | Not_found => None 
  };

let lastIndexFrom i ch str =>
  try (Some (String.rindex_from str i ch)) {
  | Not_found => None 
  };
/* String.rindex_from s i c returns the index of the last occurrence of character c in string s before position i+1. String.rindex s c is equivalent to String.rindex_from s (String.length s - 1) c. */

let contains c s => String.contains s c;
/* String.contains s c tests if character c appears in the string s. */

let containsFrom i c s =>
  try (String.contains_from s i c) {
  | Invalid_argument _ => false
  };

let containsUntil i c s =>
  try (String.rcontains_from s i c) {
  | Invalid_argument _ => false
  };

let uppercase = String.uppercase;

let lowercase = String.lowercase;

let capitalize = String.capitalize;

let uncapitalize = String.uncapitalize;

type t = string;

let compare = String.compare;