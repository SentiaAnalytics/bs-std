open Prelude;

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

let encode = (failEncoder, successEncoder, r) =>
  Json.Encode.(
    switch r {
    | Ready(r) => successEncoder(r)
    | Failed(err) => failEncoder(err)
    | NotAsked => string("NotAsked")
    | Pending => string("Pending")
    }
  );
