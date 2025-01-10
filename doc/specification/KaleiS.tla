----------------- MODULE KaleiS --------------------------
\* KaleiS is a program tht
CONSTANTS NULL
VARIABLES kaleis, parser, transformer

Parser == INSTANCE Parser WITH
  NULL         <- NULL,
  Sentence_idl <- {1,2,3},
  AST_idl      <- {1,2,3},
  parser       <- parser

TypeInvariant ==
  /\ Parser!TypeInvariant
  /\ kaleis = []

Init ==
  /\ TypeInvariant
  /\ Parser!Init

Parse(sentence) ==
  /\ Parser!Parsing(sentence)



==========================================================
