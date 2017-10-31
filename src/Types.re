type remote 'x 'a = 
  | NotAsked
  | Pending
  | Failed 'x
  | Ready 'a;
  
type result 'x 'a =
  | Error 'x
  | Ok 'a;
  
type task 'err 'ok = ('err => unit) => ('ok => unit) => unit;

type dict 'k 'v = list ('k, 'v);