open Types;
let empty = [];
let fromList a => a;
let rec get key dict => switch dict {
| [] => None
| [(k, v), ..._] when k == key => Some v 
| [_, ...dict] => get key dict
};

let rec find f dict => switch dict {
| [] => None
| [(_, v), ..._] when f v => Some v 
| [_, ...dict] => find f dict
};

let contains key dict => get key dict |> Option.isSome;
let set key value dict => [(key, value), ...(List.filter (fun (k, _) => k != key) dict)];
let setDefault key value dict => if (contains key dict) {
    dict
  } else {
    [(key, value), ...dict]
  };

let keys dict => List.map (fun (k, _) => k) dict;
let values dict => List.map (fun (_, v) => v) dict;
let iter f => List.iter (uncurry f);

let map f dict => List.map (fun (k, v) => (k, f k v)) dict;
let mapValues f dict => List.map (fun (k, v) => (k, f v)) dict;
let mapKeys f dict => List.map (fun (k, v) => (f k, v)) dict;

let filter f => List.filter (uncurry f);

let foldLeft f acc dict => List.foldLeft (fun (k, v) acc => f k v acc) acc dict;
let foldRight f acc dict => List.foldRight (fun (k, v) acc => f k v acc) acc dict;

let encode encodeKey encodeValue dict => dict |> mapKeys encodeKey |> mapValues encodeValue |> Json.Encode.object_;
let decode decodeKey decodeValue json => 
  json |> Json.Decode.dict decodeValue
    |> Js.Dict.entries
    |> Array.to_list
    |> mapKeys decodeKey;