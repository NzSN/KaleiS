----------------- MODULE KaleiS --------------------------
EXTENDS TLC

\* KaleiS is a program tht
CONSTANTS NULL
VARIABLES parser, ir, generator

LOCAL INSTANCE Defines
LOCAL INSTANCE IDL WITH NULL <- NULL

Parser == INSTANCE Parser WITH
  NULL   <- NULL,
  parser <- parser

IR == INSTANCE IR WITH
  NULL <- NULL,
  ir   <- ir

Generator == INSTANCE Generator WITH
  NULL <- NULL,
  generator <- generator

(* States *)
Init ==
  /\ Parser!Init
  /\ IR!Init
  /\ Generator!Init

Prepare(sentence) ==
  /\ Parser!Prepare(sentence)
  /\ UNCHANGED <<ir, generator>>

Parsing ==
  /\ Parser!Parsing
  /\ UNCHANGED <<ir, generator>>

PrepareIr ==
  /\ Parser!Parsed
  /\ IR!Prepare(Parser!GetAST(parser))
  /\ UNCHANGED <<parser, generator>>

GenerateIr ==
  /\ Parser!Parsed
  /\ IR!Transforming
  /\ UNCHANGED <<parser, generator>>

PrepareTr ==
  /\ Parser!Parsed
  /\ IR!Transformed
  /\ Generator!Prepare(ir.interfaces)
  /\ UNCHANGED <<parser, ir>>

Transforming ==
  /\ Parser!Parsed
  /\ IR!Transformed
  /\ Generator!Generate
  /\ UNCHANGED <<parser, ir>>

Transformed ==
  /\ Parser!Parsed
  /\ IR!Transformed
  /\ Generator!Generated
  /\ UNCHANGED <<parser, ir, generator>>

Next ==
  \E s \in { <<InterfaceIDL[n]>> : n \in 0..CARDINALITY_LIMIT }:
    \/ Prepare(s)
    \/ Parsing
    \/ PrepareIr
    \/ GenerateIr
    \/ PrepareTr
    \/ Transforming
    \/ Transformed

Spec == Init /\ [][Next]_<<parser, ir>>
==========================================================
