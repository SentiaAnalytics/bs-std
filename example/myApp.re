open App;

type action =
 | Inc
 | NoOp
 ;

let delayedInc = 
  Task.delay 3000
    |> Task.map (Func.always Inc)
    |> Cmd.fromTask;

let update action state => 
  switch action {
  | Inc => (state + 1, delayedInc)
  | _ => (state, Cmd.none)
  };

App.make
  init:: 0
  ::update
  onAction:: (fun _ => Js.log "ACTION")
  onLoad::(fun _ dispatch => dispatch Inc)
  render::(fun state _  => {
    Js.log state
  })
  ();


