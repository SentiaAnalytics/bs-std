let length = List.length;

let head xs => switch xs {
| [] => None
| [x, ..._] => Some x
};

let tail xs => switch xs {
| [] => []
| [_, ...xs] => xs
};

let rec nth i xs =>
  switch (i, xs) {
  | (_, []) => None
  | (0, [x, ..._]) => Some x
  | (i, [_, ...xs]) => nth (i-1) xs
  };

let reverse = List.rev;

let append = List.append;

let reverseAppend = List.rev_append;

let concat = List.concat;

let flatten = List.flatten;


/* Iterators */


let iter = List.iter;

let iteri = List.iteri;

let map = List.map;

let mapi = List.mapi;

let reverseMap = List.rev_map;

let foldLeft = List.fold_left;

let foldRight = List.fold_right;


let rec foldLeft2 f acc xs ys =>
switch (xs, ys) {
| ([], _) | (_, []) => acc
| ([x, ...xs], [y, ...ys]) => foldLeft2 f (f acc x y) xs ys
};

let rec foldRight2 f l1 l2 acc =>
switch (l1, l2) {
|  ([], _) | (_, []) => acc
| ([x, ...xs], [y, ...ys]) => f x y (foldRight2 f xs ys acc)
};


/* Iterators on two lists */

let rec iter2 f xs ys =>
  switch (xs, ys) {
  | ([], _) | (_, []) => () 
  | ([x, ...xs], [y, ...ys]) => {
    f x y;
    iter2 f xs ys;
  };
};

let rec map2 f xs ys =>
    switch (xs, ys) {
    | ([], _) | (_, []) => []
    | ([x, ...xs], [y, ...ys]) => [f x y, ...(map2 f xs ys)]
  };

let reverseMap2 f xs ys => {
  let rec map acc f xs ys =>
    switch (xs, ys) {
    | ([], _) | (_, []) => acc
    | ([x, ...xs], [y, ...ys]) => map [f x y, ...acc] f xs ys
    };
  
  map [] f xs ys;
};


/* List scanning */


let forAll = List.for_all;

let exists = List.exists;

let rec forAll2 f xs ys => 
  switch (xs, ys) {
  | ([], _) | (_, []) => true
  | ([x, ..._], [y, ..._]) when not (f x y) => false
  | ([_, ...xs], [_, ...ys]) => forAll2 f xs ys
  };

let rec exists2 f xs ys =>
  switch (xs, ys) {
  | ([], _) | (_, []) => false
  | ([x, ..._], [y, ..._]) when f x y => true
  | ([_, ...xs], [_, ...ys]) => exists2 f xs ys
  };

let contains = List.mem;


/* List searching */


let rec find f xs =>
  switch xs {
  | [] => None
  | [x, ..._] when f x => Some x 
  | [_, ...xs]  => find f xs 
  };

let filter = List.filter;


let partition = List.partition;


/* Association lists */

let rec assoc key pairs =>
  switch pairs {
  | [] => None 
  | [(k, v), ..._] when k == key => Some v
  | [_, ...pairs] => assoc key pairs
  };

let containsAssoc = List.mem_assoc;

let removeAssoc = List.remove_assoc;


/* Lists of pairs */


let split = List.split;

let rec zip xs ys => 
  switch (xs, ys) {
  | ([], _) | (_, []) =>  []
  | ([x, ...xs], [y, ...ys]) => [(x, y), ...(zip xs ys)]
  };


/* Sorting */


let sort = List.sort;

let stableSort = List.stable_sort;

let fastSort = List.fast_sort;

let sortUniq = List.sort_uniq;

let merge = List.merge;