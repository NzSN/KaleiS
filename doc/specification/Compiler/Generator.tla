--------------------- MODULE Generator ---------------------
\* Generator will generating sentence of target language that implement
\* declared interfaces that represent by datastructures that represent
\* Interfaces.
EXTENDS Sequences, Naturals, Defines

VARIABLE generator
CONSTANTS NULL

InnerRepresent == INSTANCE InnerRepresent WITH NULL <- NULL
TLang == INSTANCE TLanguage WITH NULL <- NULL

TypeInvariant == generator = [ structure |-> NULL, tsentences |-> NULL ]

Init == TypeInvariant

Prepare(i_seq (* Sequence of Interface datastructure *)) ==
  /\ i_seq \in Seq(InnerRepresent!Interfaces)
  /\ generator.structure = NULL
  /\ generator.tsentences = NULL
  /\ generator' = [generator EXCEPT !.structure = i_seq]

Generate ==
  /\ generator.structure # NULL
  /\ generator.tsentences = NULL
  /\ generator' = [generator EXCEPT
                  !.tsentences =
                    [ i \in 1..Len(generator.structure) |->
                        TLang!InterfaceT[InnerRepresent!GetInterfaceDef(generator.structure[i])]]
                  ]

Generated ==
  /\ generator.structure \in Seq(InnerRepresent!Interfaces)
  /\ generator.tsentences \in TLang!TSentences
  /\ UNCHANGED <<generator>>

Next ==
  \E i_seq \in { <<InnerRepresent!Interface[n]>> : n \in 0..CARDINALITY_LIMIT } :
    Prepare(i_seq) \/ Generate \/ Generated

Spec == Init /\ [][Next]_<<generator>>
============================================================
