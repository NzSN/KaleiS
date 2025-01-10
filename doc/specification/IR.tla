------------------------ MODULE IR ------------------------
\* IR is responsible to generate runtime datastructure that
\* present interfaces correspond to input AST.
EXTENDS Interfaces

CONSTANTS NULL, AST_idl
VARIABLES ir


TypeInvariant == ir = [ ast |-> NULL, interfaces |-> NULL ]

Init == TypeInvariant

Transform(ast) ==
  /\ ir.ast = NULL
  /\ ir.interfaces = NULL
  /\ ir' = [ir EXCEPT !.ast = ast]

Transformed ==
  /\ ir.ast # NULL
  /\ ir.interfaces = NULL
  /\ ir' = [ir EXCEPT !.interfaces = Interface[ir.ast]]

Clean ==
  /\ ir.ast # NULL
  /\ ir.interfaces # NULL
  /\ ir' = [ir EXCEPT !.ast = NULL, !.interfaces = NULL]

Next == \E a \in AST_idl: Transform(a) \/ Transformed \/ CLean

Spec == Init /\ [][Next]_<<ir>>
===========================================================
