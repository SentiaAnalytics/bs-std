open Types;
let map f res => switch res {
  | Error x => Error x
  | Ok a => Ok (f a)
};

let map2 f r1 r2 => switch (r1, r2) {
  | (Ok a1, Ok a2) => Ok (f a1 a2)
  | (Error x, _) => Error x
  | (_, Error x) => Error x
};

let map3 f r1 r2 r3 => switch (r1, r2, r3) {
  | (Ok a1, Ok a2, Ok a3) => Ok (f a1 a2 a3)
  | (Error x, _, _) => Error x
  | (_, Error x, _) => Error x
  | (_, _, Error x) => Error x
};

let flatten r => {
  switch r {
  | Error e => Error e
  | Ok a => a
  };
};

let flatMap f res => switch res {
| Error x => Error x
| Ok a => f a
};


let withDefault a res => switch res {
| Error _ => a
| Ok a => a
};

let fromOption err opt => switch opt {
| None => Error err
| Some a => Ok a
};

let isError res => switch res {
| Error _ => true
| _ => false
};

let isOk res => switch res {
| Ok _ => true
| _ => false
};

let encode encodeError encodeOk => fun
| Error e => encodeError e
| Ok v => encodeOk v;

  