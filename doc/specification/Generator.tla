--------------------- MODULE Generator ---------------------
EXTENDS Interfaces

CONSTANTS AST_idl,
VARIABLE g (* Generator *)

TypeInvariant ==
  g = [ ast |-> NULL, ]

Init == TypeInvariant



============================================================
