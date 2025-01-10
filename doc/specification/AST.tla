------------------- MODULE AST -----------------------
EXTENDS Sequences
CONSTANTS NULL
LOCAL INSTANCE Defines
LOCAL INSTANCE IDL WITH NULL <- NULL

AST[s \in Sentences] == <<ASTCat, s>>

IsAST(ast) ==
    /\ ast[1] = ASTCat
    /\ ast[2] \in Sentences
NumOfInterfaceInAST(ast) == Len(ast[2])
GetInterfaceInAST(ast, idx) == ast[2][idx]

======================================================
