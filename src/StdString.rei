let length: string => int;
/* Return the length (number of characters) of the given string. */

let get: int => string => option char;
/* String.get s n returns the character at index n in string s. You can also write s.[n] instead of String.get s n. */

let make: int => char => string;
/* String.make n c returns a fresh string of length n, filled with the character c.
Raise Invalid_argument if n < 0 or n > Sys.max_string_length. */

let init: int => (int => char) => string;
/* String.init n f returns a string of length n, with character i initialized to the result of f i (called in increasing index order).
Raise Invalid_argument if n < 0 or n > Sys.max_string_length. */

let sub: int => int => string => string;
/* String.sub s start len returns a fresh string of length len, containing the substring of s that starts at position start and has length len.
Raise Invalid_argument if start and len do not designate a valid substring of s. */


let concat : string => string => string;
/* String.concat s s concatenates the two strings */

let join: string => list string => string;
/* String.join sep sl concatenates the list of strings sl, inserting the separator string sep between each. */

let iter: (char => unit) => string => unit;
/* String.iter f s applies function f in turn to all the characters of s. It is equivalent to f s.[0]; f s.[1]; ...; f s.[String.length s - 1]; (). */

let iteri: (int => char => unit) => string => unit;
/* Same as String.iter, but the function is applied to the index of the element as first argument (counting from 0), and the character itself as second argument. */

let map: (char => char) => string => string;
/* String.map f s applies function f in turn to all the characters of s (in increasing index order) and stores the results in a new string that is returned. */

let mapi: (int => char => char) => string => string;
/* String.mapi f s calls f with each character of s and its index (in increasing index order) and stores the results in a new string that is returned. */

let trim: string => string;
/* Return a copy of the argument, without leading and trailing whitespace. The characters regarded as whitespace are: ' ', '\012', '\n', '\r', and '\t'. If there is neither leading nor trailing whitespace character in the argument, return the original string itself, not a copy. */

let escaped: string => string;
/* Return a copy of the argument, with special characters represented by escape sequences, following the lexical conventions of OCaml. If there is no special character in the argument, return the original string itself, not a copy. Its inverse function is Scanf.unescaped. */
/* Raise Invalid_argument if the result is longer than Sys.max_string_length bytes. */

let indexOf: char => string => option int;
/* String.indexOf c s returns the index of the first occurrence of character c in string s. */

let lastIndexOf: char => string => option int;
/* String.rindex s c returns the index of the last occurrence of character c in string s.*/

let indexFrom: int => char => string => option int;
/* String.index_from i c s returns the index of the first occurrence of character c in string s after position i. String.indexOf c s is equivalent to String.indexFrom 0 c s. */

let lastIndexFrom: int => char => string => option int;
/* String.rindex_from i c s returns the index of the last occurrence of character c in string s before position i+1. String.lastIndex c s is equivalent to String.lastIndexFrom (String.length s - 1) c s. */

let contains: char => string => bool;
/* String.contains s c tests if character c appears in the string s. */

let containsFrom: int => char => string => bool; 
/* String.containsFrom start c s tests if character c appears in s after position start. String.contains s c is equivalent to String.contains_from s 0 c. */

let containsUntil: int => char => string => bool; 
/* String.containsBefore stop c s tests if character c appears in s before position stop+1. */

let uppercase: string => string;
/* Return a copy of the argument, with all lowercase letters translated to uppercase, including accented letters of the ISO Latin-1 (8859-1) character set. */

let lowercase: string => string;
/* Return a copy of the argument, with all uppercase letters translated to lowercase, including accented letters of the ISO Latin-1 (8859-1) character set. */

let capitalize: string => string;
/* Return a copy of the argument, with the first character set to uppercase. */

let uncapitalize: string => string;
/* Return a copy of the argument, with the first character set to lowercase. */

type t = string;
/* An alias for the type of strings. */

let compare: t => t => int;
/* The comparison function for strings, with the same specification as Pervasives.compare. Along with the type t, this function compare allows the module String to be passed as argument to the functors Set.Make and Map.Make. */