open Prelude;
let ready: 'a => remote('a, 'x);
let error: 'x => remote('a, 'x);
let pending: remote('a, 'x);
let notAsked: remote('a, 'x);
let map: ('a => 'b, remote('a, 'x)) => remote('b, 'x);
let map2: (('a, 'b) => 'c, remote('a, 'x), remote('b, 'x)) => remote('c, 'x);
let map3: (('a, 'b, 'c) => 'd, remote('a, 'x), remote('b, 'x), remote('c, 'x)) => remote('d, 'x);
let flatten: remote(remote('a, 'x), 'x) => remote('a, 'x);
let flatMap: ('a => remote('b, 'x), remote('a, 'x)) => remote('b, 'x);
let withDefault: ('a, remote('a, 'x)) => 'a;
let fromResult: result('a, 'x) => remote('a, 'x);
let fromOption: option('a) => remote('a, 'x);
let isNotAsked: remote('a, 'x) => bool;
let isPending: remote('a, 'x) => bool;
let isFailed: remote('a, 'x) => bool;
let isReady: remote('a, 'x) => bool;
let encode: ('a => Js.Json.t, 'x => Js.Json.t, remote('a, 'x)) => Js.Json.t;