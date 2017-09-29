
type t 'err 'ok =
  | NotAsked
  | Pending
  | Error 'err
  | Ready 'ok
  ;

let ready a => Ready a;
let error x => Error x;
let notAsked = NotAsked;

let pending = Pending;
let map f remote => 
  switch remote {
  | NotAsked => NotAsked
  | Pending => Pending
  | Error e => Error e
  | Ready x => Ready (f x)
  };

let map2 f r1 r2 => 
  switch (r1, r2) {
  | (Ready a1, Ready a2) => Ready (f a1 a2)
  | (NotAsked, _) => NotAsked
  | (Pending, _) => Pending
  | (Error x, _) => Error x
  | (Ready _, NotAsked) => NotAsked
  | (Ready _, Pending) => Pending
  | (Ready _, Error x) => Error x
  };

let map3 f r1 r2 r3 => 
  switch (r1, r2, r3) {
  | (Ready a1, Ready a2, Ready a3) => Ready (f a1 a2 a3)
  | (NotAsked, _, _) => NotAsked
  | (Pending, _, _) => Pending
  | (Error x, _, _) => Error x
  | (Ready _, NotAsked, _) => NotAsked
  | (Ready _, Pending, _) => Pending
  | (Ready _, Error x, _) => Error x
  | (Ready _, Ready _, NotAsked) => NotAsked
  | (Ready _, Ready _, Pending) => Pending
  | (Ready _, Ready _, Error x) => Error x
  };

let flatMap f remote => 
  switch remote {
  | NotAsked => NotAsked
  | Pending => Pending
  | Error e => Error e
  | Ready x => f x
  };

let withDefault a rem => switch rem {
| Ready a => a
| _ => a
};

let fromResult res => switch res {
| StdResult.Ok a => Ready a
| StdResult.Error x => Error x
};


let fromOption opt => switch opt {
| None => NotAsked
| Some a => Ready a
};


let isNotAsked remote => switch (remote) {
| NotAsked => true
| _ => false
};

let isPending remote => switch (remote) {
| Pending => true
| _ => false
};

let isError remote => switch (remote) {
| Error _ => true
| _ => false
};

let isReady remote => switch (remote) {
| Ready _ => true
| _ => false
};
