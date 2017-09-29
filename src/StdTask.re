external _resolvePromise : Js.Promise.t 'a => ('a => unit) => ('err => unit) => unit =
"then" [@@bs.send];

external _setTimeout : (unit => unit) => int => unit = "setTimeout" [@@bs.val]; 

type t 'err 'ok = ('err => unit) => ('ok => unit) => unit;

let make create fail success => create fail success;

let succeed a => make (fun _ success => success a);

let fail x => make (fun fail _ => fail x);

let fork fail success task => task fail success;

let map f task => make (fun fail success => task fail (fun x => f x |> success));

let map2 f t1 t2 => 
  make (fun fail success => {
    t1 fail (fun a1 => {
      t2 fail (fun a2 => f a1 a2 |> success);
    });
  });
let map3 f t1 t2 t3 => 
  make (fun fail success => {
    t1 fail (fun a1 => {
      t2 fail (fun a2 => {
        t3 fail (fun a3 => f a1 a2 a3 |> success);
      });
    });
  });
let chain f task => make (fun fail success => task fail (fun x => (f x) fail success));

let biMap mapFail mapSuccess task =>
make (
  fun fail success => task (fun err => mapFail err |> fail) (fun ok => mapSuccess ok |> success)
);

let fold mapFail mapSuccess task =>
make (
  fun _ success => task (fun err => mapFail err |> success) (fun ok => mapSuccess ok |> success)
);

let fromLazyPromise f => make (fun fail success => _resolvePromise (f ()) success fail);

let fromOption err opt =>
switch opt {
| None => fail err
| Some x => succeed x
};

let fromResult res =>
switch res {
| StdResult.Error err => fail err
| StdResult.Ok v => succeed v
};

let delay ms => make (fun _ resolve => _setTimeout resolve ms);