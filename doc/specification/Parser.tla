-------------------- MODULE Parser ----------------------
EXTENDS Sequences, Naturals
CONSTANTS NULL
VARIABLES parser

LOCAL INSTANCE Defines
LOCAL INSTANCE IDL WITH NULL <- NULL
LOCAL INSTANCE AST WITH NULL <- NULL

TypeInvariant == parser = [ ast |-> NULL, sentence |-> NULL ]

Init == TypeInvariant

Parsing(sentence) ==
  /\ sentence \in Sentences
  /\ parser.ast = NULL
  /\ parser.sentence = NULL
  /\ parser' = [parser EXCEPT !.sentence = sentence]

Parsed ==
  /\ parser.sentence /= NULL
  /\ parser.ast = NULL
  /\ parser' = [parser EXCEPT !.ast = AST[parser.sentence]]

Clean ==
  /\ parser.sentence # NULL
  /\ parser.ast # NULL
  /\ parser' = [parser EXCEPT !.sentence = NULL, !.ast = NULL]

Next == \E s \in { <<InterfaceIDL[n]>> : n \in 0..CARDINALITY_LIMIT }: Parsing(s) \/ Parsed \/ Clean

Spec == Init /\ [][Next]_<<parser>>
=========================================================
