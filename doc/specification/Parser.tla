-------------------- MODULE Parser ----------------------
EXTENDS Sequences, Naturals
CONSTANTS NULL
VARIABLES parser

LOCAL INSTANCE Defines
LOCAL INSTANCE IDL WITH NULL <- NULL
LOCAL INSTANCE AST WITH NULL <- NULL

TypeInvariant == parser = [ ast |-> NULL, sentence |-> NULL ]

GetSentence(p) == p.sentence
GetAST(p) == p.ast

Init == TypeInvariant

Prepare(sentence) ==
  /\ sentence \in Sentences
  /\ parser.ast = NULL
  /\ parser.sentence = NULL
  /\ parser' = [parser EXCEPT !.sentence = sentence]

Parsing ==
  /\ parser.sentence /= NULL
  /\ parser.ast = NULL
  /\ parser' = [parser EXCEPT !.ast = AST[parser.sentence]]

Parsed ==
  /\ parser.sentence # NULL
  /\ parser.ast # NULL
  /\ UNCHANGED <<parser>>

\* Due to Sentence unable to enumerated so only specify
\* step on Sentence with only one interface declared,
\* and it's enough to guranteed behavior of Parser.
Next ==
  \E s \in { <<InterfaceIDL[n]>> : n \in 0..CARDINALITY_LIMIT }:
    Prepare(s) \/ Parsing \/ Parsed

Spec == Init /\ [][Next]_<<parser>>
=========================================================
