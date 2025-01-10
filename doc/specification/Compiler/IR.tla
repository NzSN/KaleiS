------------------------ MODULE IR ------------------------
\* IR is responsible to generate runtime datastructure that
\* represent interfaces correspond to input AST.
EXTENDS Naturals, Defines, Sequences, TLC, Interfaces
CONSTANTS NULL, ASTSamples
VARIABLES ir

IDL            == INSTANCE IDL WITH NULL <- NULL
AST            == INSTANCE AST WITH NULL <- NULL
InnerRepresent == INSTANCE InnerRepresent WITH NULL <- NULL

(* Implementations *)
InvalidInterface__(ir_, i) ==
  \* If an interface is not defined within realm of IDL
  \* then implementation from external must be provided
  \* otherwise generated interfaces result in ill-formed.
  \/ (~IsImplemented(i) /\ ~HasProp(i, EXTERNAL))
  \* Interface can be annoated with at most one of {SYNCHRONOUS, ASYNCHRONOUS},
  \* Must not presented together at the same time.
  \/ (IsAsyncInterface(i) /\ IsSyncInterface(i))
  \* Uniqueness of Interface

RECURSIVE SpawnDoStep__(_,_)
SpawnDoStep__(ir_, Is) ==
  \* Generate inner representation for current interface in ast.
  LET current_proc_interface == Head(Is)
      proc(ir__, i) ==
        IF InvalidInterface__(ir__, current_proc_interface)
          THEN [ir__ EXCEPT !.error = Append(@, i)]
          ELSE [ir__ EXCEPT !.innerRep = Append(@, i)]
  IN IF Len(Is) > 0
      THEN SpawnDoStep__(proc(ir_, current_proc_interface), Tail(Is))
      ELSE ir_

SpawnStep__(ir_, a) == SpawnDoStep__(ir_, AST!GetAllInterfaces(a))

(* Interfaces *)
IR == [ innerRep |-> <<>>, error |-> <<>> ]
IsIR(ir_) ==
  /\ \A k \in 1..Len(ir_.innerRep): IsInterface(ir_.innerRep[k])
  /\ \A k \in 1..Len(ir_.error):    IsInterface(ir_.error[k])
SpawnInnerRep(ir_, a) ==
  /\ ir_.innerRep = <<>>
  /\ ir_.error = <<>>
  /\ ir_' = SpawnStep__(ir_, a)
GetInnerRep(ir_) ==
  InnerRepresent!InnerRep(ir_.innerRep)
AllInterfaces(ir_) == CODOMAIN(ir_.innerRep) \union CODOMAIN(ir_.error)

(* Specification *)
ConflictCheck(ir_) ==
  \A li \in AllInterfaces(ir_):
  \A ri \in (AllInterfaces(ir_) \ {li}):
    ~IsSameInterface(li, ri)
POSTCOND_CHECK(ir_) ==
  /\ ConflictCheck(ir_)

TypeInvariant == ir = IR

Init == TypeInvariant

Spawning(A (* AST *)) ==
  /\ AST!IsAST(A)
  /\ ir.innerRep = <<>>
  /\ ir.error = <<>>
  /\ SpawnInnerRep(ir, A)

Spawned ==
  /\ POSTCOND_CHECK(ir)
  /\ ir.innerRep # <<>>
  /\ ir.error = <<>>
  /\ UNCHANGED <<ir>>

Ill_Formed ==
  /\ (~POSTCOND_CHECK(ir) \/ ir.error # <<>>)
  /\ UNCHANGED <<ir>>

Next == \A a \in ASTSamples: Spawning(a) \/ Spawned \/ Ill_Formed
Spec == Init /\ [][Next]_<<ir>>
===========================================================
