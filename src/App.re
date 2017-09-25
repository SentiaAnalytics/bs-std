module Cmd = {
  type t 'action = option (Task.t unit (('action => unit) => unit));
  let none = None;

  let perform dispatch cmd => 
    switch cmd {
    | None => ()
    | Some t => t |> Task.fork (fun _ => ()) (fun f => f dispatch);
    };

  let batch cmds => Some (Task.succeed (fun dispatch => List.iter (perform dispatch) cmds));

  let fromTask task => 
    Some (task |> Task.map (fun action  => (fun dispatch => dispatch action)));

};


let make 
  ::init 
  ::update 
  ::render 
  ::onAction=(fun _ => ())
  ::onUpdate=(fun _ => ())
  ::onLoad=(fun _ _ => ())
  _ => {
  let state = ref init;
  let rec dispatch a => {
    onAction a;
    let (nextState, cmd) = update a !state;
    state := nextState;
    onUpdate !state;
    render !state dispatch;
    Cmd.perform dispatch cmd;
  };
  render !state dispatch;
  onLoad !state dispatch;
};

