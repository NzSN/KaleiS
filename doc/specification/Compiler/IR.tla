------------------------ MODULE IR ------------------------
\* IR is responsible to generate runtime datastructure that
\* represent interfaces correspond to input AST.
EXTENDS Naturals, Defines, Sequences

CONSTANTS NULL
VARIABLES ir

IDL            == INSTANCE IDL WITH NULL <- NULL
AST            == INSTANCE AST WITH NULL <- NULL
InnerRepresent == INSTANCE InnerRepresent WITH NULL <- NULL

TypeInvariant == ir = [ ast |-> NULL, interfaces |-> NULL ]

Init == TypeInvariant

Prepare(ast) ==
  /\ AST!IsAST(ast)
  /\ ir.ast = NULL
  /\ ir.interfaces = NULL
  /\ ir' = [ir EXCEPT !.ast = ast]

Transforming ==
  /\ ir.ast # NULL
  /\ ir.interfaces = NULL
  /\ ir' = [ir EXCEPT
            !.interfaces =
              [ i \in 1..AST!NumOfInterfaceInAST(ir.ast) |->
                  InnerRepresent!Interface[IDL!GetInterfaceDef(AST!GetInterfaceInAST(ir.ast, i))]
                ]
            ]

Transformed ==
  /\ ir.ast # NULL
  /\ ir.interfaces # NULL
  /\ UNCHANGED <<ir>>

Next ==
  \E a \in { AST!AST[<<IDL!InterfaceIDL[n]>>] : n \in 0..CARDINALITY_LIMIT }:
    Prepare(a) \/ Transforming \/ Transformed

Spec == Init /\ [][Next]_<<ir>>
===========================================================
