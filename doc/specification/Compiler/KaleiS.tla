----------------- MODULE KaleiS --------------------------
EXTENDS TLC, Defines, Interfaces

CONSTANTS NULL
VARIABLES ast, ir, generator

InterfaceDomain == <<
  SetToImplemented(Interface(0)),
  SetToImplemented(Interface(1)),
  SetToImplemented(Interface(2)),
  SetToImplemented(Interface(3)) >>

AST == INSTANCE AST WITH
  NULL <- NULL

IDL == INSTANCE IDL WITH
  NULL <- NULL

SourceIDLs == { IDL!SentenceIDL(InterfaceDomain) }
Parser == INSTANCE Parser WITH
  NULL <- NULL,
  ParsableIDLSentences <- SourceIDLs
IR == INSTANCE IR WITH
  NULL <- NULL,
  ASTSamples <- { AST!AST(InterfaceDomain) },
  ir <- ir

Gen == INSTANCE Generator WITH
  generator <- generator

TypeInvariant ==
  /\ Gen!TypeInvariant
  /\ IR!TypeInvariant

(* States *)
Init == /\ TypeInvariant
        /\ ast = NULL

Parse(sentence) ==
  /\ ast  = NULL
  /\ ast' = Parser!Parse[sentence]
  /\ UNCHANGED <<ir, generator>>

GenIr ==
  /\ AST!IsAST(ast)
  /\ IR!Spawning(ast)
  /\ UNCHANGED <<ast, generator>>

GenTarget ==
  /\ AST!IsAST(ast)
  /\ IR!Spawned
  /\ Gen!Generating(IR!GetInnerRep(ir))
  /\ UNCHANGED <<ast, ir>>

Done ==
  /\ AST!IsAST(ast)
  /\ IR!Spawned
  /\ Gen!Generated
  /\ UNCHANGED <<ast, ir, generator>>

Next ==
  \A s \in SourceIDLs:
    \/ Parse(s)
    \/ GenIr
    \/ GenTarget
    \/ Done

Spec == Init /\ [][Next]_<<ast, ir, ast>>
==========================================================
