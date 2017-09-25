module Cmd : {
  type t 'action;
  let none : t 'action;

  let batch : list (t 'action) => t 'action;
  
  let fromTask : Task.t unit 'action => t 'action;
};

let make : 
  init:: 'state => 
  update::('action => 'state => ('state, Cmd.t 'action )) => 
  render::('state => ('action => unit) => unit) => 
  onAction:: ('action => unit)? =>
  onUpdate:: ('state => unit)? =>
  onLoad:: ('state => ('action => unit) => unit)? =>
  unit => 
    unit;