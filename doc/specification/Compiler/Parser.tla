-------------------- MODULE Parser ----------------------
EXTENDS Sequences, Naturals, TLC, Interfaces
CONSTANTS NULL, ParsableIDLSentences

LOCAL INSTANCE IDL WITH NULL <- NULL
LOCAL INSTANCE AST WITH NULL <- NULL

(* Interface *)
Parse[x \in ParsableIDLSentences] == AST(ContentOfIDLSentence(x))
=========================================================
