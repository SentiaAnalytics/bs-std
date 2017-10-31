open Types;
let length = List.length;

let reverse xs => {
  let rec go acc xs =>
    switch xs {
    | [] => acc
    | [x, ...xs] => go [x, ...acc] xs
    };
    go [] xs;
};


let isEmpty xs => 
  switch xs {
  | [] => true
  | _ => false
  };


  /* folds */

let rec foldLeft f acc xs => 
  switch xs {
    | [] => acc
    | [x, ...xs] => foldLeft f (f x acc) xs
  };

let rec foldRight f acc xs => 
  switch xs {
    | [] => acc
    | [x, ...xs] => f x (foldRight f acc xs)
  };

let rec foldLeft2 f acc xs ys =>
  switch (xs, ys) {
    | ([], _) | (_, []) => acc
    | ([x, ...xs], [y, ...ys]) => foldLeft2 f (f x y acc) xs ys
  };

let rec foldRight2 f acc xs ys =>
  switch (xs, ys) {
  | ([], _) | (_, []) => acc
  | ([x, ...xs], [y, ...ys]) => f x y (foldRight2 f acc xs ys)
  };


/* create */

let repeat count x => {
  let rec go acc count => 
    if (count <= 0) acc else go [x, ...acc] (count -1);
  go [] count;
};

let range start stop => {
  let rec go acc start =>
    if (start >= stop)
        acc 
    else 
      [start, ...(go acc (start + 1))];
  go [] start;
};


/* combining lists*/

let cons x xs => xs @ [x];

let append xs ys => xs @ ys; 

let flatten xs => foldLeft append [] xs;

let rec zip xs ys => 
  switch (xs, ys) {
  | ([], _) | (_, []) =>  []
  | ([x, ...xs], [y, ...ys]) => [(x, y), ...(zip xs ys)]
  };

let merge = List.merge;

/* Sub lists */

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
  | (i, [x, ..._])  when i <= 0 => Some x
  | (i, [_, ...xs]) => nth (i-1) xs
  };

let rec take count xs =>
  switch (count, xs) {
  | (_ , []) =>  []
  | (i , _) when i <= 0 =>  []
  | (count, [x, ...xs]) => [x, ...(take (count - 1) xs)]
  };

let rec drop count xs =>
  switch (count, xs) {
  | (_, []) => []
  | (i, _) when i <= 0 => []
  | (count, [_, ...xs]) => drop (count - 1) xs
  };

let takeLast count xs =>
  drop ((length xs) - count) xs;


let takeUntil f xs => {
  let rec go acc f xs =>
    switch xs {
    | [] => acc
    | [x, ..._] when (f x) => acc
    | [x, ...xs] => go [x, ...acc] f xs
    };
    go [] f xs;
};
let takeWhile f xs =>
  takeUntil (fun a => not (f a)) xs;

let dropLast count xs => 
  take ((length xs) - count) xs;

let rec dropUntil f xs =>
  switch xs {
  | [] => []
  | [x, ..._] when f x => xs
  | [_, ...xs] => dropUntil f xs
  };

let dropWhile f xs =>
  dropUntil (fun x => f x |> not) xs;

let rec filter f xs =>
  switch xs {
  | [] => [] 
  | [x, ...xs] when f x => [x, ...(filter f xs)] 
  | [_, ...xs] => filter f xs
  };

/* map */

let rec map f xs => 
  switch xs {
  | [] => []
  | [x, ...xs] => [f x, ...(map f xs)]
  };

let mapIndexed f xs => {
  let rec go i f xs =>
    switch xs {
    | [] => []
    | [x, ...xs] => [f i x, ...(go (i + 1) f xs)]
    };
    go 0 f xs;
};

let rec map2 f xs ys =>
  switch (xs, ys) {
  | (_, []) | ([], _) => []
  | ([x, ...xs],[y, ...ys]) => [f x y, ...(map2 f xs ys)]
  };

let rec flatMap f xs =>
  switch xs {
  | [] => []
  | [x, ...xs] => f x @ flatMap f xs
  };

let rec flatMap2 f xs ys =>
  switch (xs, ys) {
  | ([], _) | (_, []) => []
  | ([x, ...xs], [y, ...ys]) => f x y @ flatMap2 f xs ys
  };

let rec filterMap f xs => 
  switch xs {
    | [] => []
    | [x, ...xs] => switch (f x) {
      | Some x => [x , ...filterMap f xs] 
      | None => filterMap f xs
    }
  };

/* iterate */

let rec iter f xs =>
  switch xs {
  | [] => ()
  | [x, ...xs] => {
    f x;
    iter f xs;
  };
};

let rec iter2 f xs ys => 
  switch (xs, ys) {
  | ([], _) | (_, []) => ()
  | ([x, ...xs], [y, ...ys]) => {
    f x y;
    iter2 f xs ys
  }; 
};

let iterIndexed f xs => {
  let rec go i f xs => 
    switch xs {
      | [] => ()
      | [x, ...xs] => {
        f i x;
        go (i + 1) f xs;
      }
    };
    go 0 f xs;
};


/* scan */

let rec find f xs =>
  switch xs {
  | [] => None
  | [x, ..._] when f x => Some x
  | [_, ...xs] => find f xs
  };

let any f xs =>
  find f xs |> Option.isSome;

let all f xs => 
  any (fun x => f x |> not) xs;


let contains y xs => 
  any (fun x => x == y) xs;

/* misc */

let partition  f xs => {
  let rec go (l1, l2) f xs =>
    switch xs {
    | [] => (l1, l2)
    | [x, ...xs] when f x => go ([x, ...l1], l2) f xs
    | [x, ...xs] => go (l1, [x, ...l2]) f xs
    };
    go ([], []) f xs;
};


let split pairs =>  {
  let rec go (xs, ys) pairs =>
    switch pairs {
    | [] => (xs, ys)
    | [(x, y), ...pairs] => go ([x, ...xs], [y, ...ys]) pairs
    };
    go ([], []) pairs;
}; 

let sort = List.sort;

let encode = Json.Encode.list;
let decode = Json.Decode.list;
