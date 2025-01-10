--------------------- MODULE Generator ---------------------
\* Generator will generating sentence of target language that implement
\* declared interfaces that represent by datastructures that represent
\* Interfaces.
EXTENDS Sequences, Naturals, Defines, TLanguage

VARIABLE generator
CONSTANTS NULL


LOCAL INSTANCE TLanguage WITH NULL <- NULL
LOCAL INSTANCE InnerRepresent WITH NULL <- NULL

IRDomain == { InnerRep(<<Interface(0), Interface(1)>>)  }

(* Interfaces *)
Generator == [ t_sentence |-> <<>> ]
IsGenerator(g) == IsInterfaceCont(g.t_sentence)
Generate(G (* Generator *), innerRep) ==
  LET all_interfaces == ContentOfInnerRep(innerRep)
  IN [G EXCEPT !.t_sentence = SentenceTarget(all_interfaces)]

(* Specification *)
TypeInvariant == generator = Generator

Init == TypeInvariant

Generating(IR (* InnerRepresent *)) ==
     \* Assume that Generation is non-trivial
  /\ Len(ContentOfInnerRep(IR)) > 0
  /\ generator.t_sentence = <<>>
  /\ generator' = Generate(generator, IR)

Generated ==
  /\ generator.t_sentence # <<>>
  /\ UNCHANGED <<generator>>

IllFormed ==
  /\ generator.t_sentence = <<>>
  /\ UNCHANGED <<generator>>

Next ==
  \A ir \in IRDomain:
    \/ Generating(ir)
    \/ Generated
    \/ IllFormed

Spec == Init /\ [][Next]_<<generator>>
============================================================
