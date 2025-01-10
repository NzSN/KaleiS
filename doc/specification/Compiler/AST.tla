------------------- MODULE AST -----------------------
EXTENDS Sequences, Interfaces
CONSTANTS NULL
LOCAL INSTANCE Defines
LOCAL INSTANCE IDL WITH NULL <- NULL

AST(Is) == InterfaceCont(ASTCat, Is)

IsAST(ast) == ast # NULL /\ TypeOfInterfaceCont(ast) = ASTCat
NumOfInterfaceInAST(ast) == Len(ValueOfInterfaceCont(ast))
GetInterfaceInAST(ast, idx) == ValueOfInterfaceCont(ast)[idx]

GetFirstInterface(ast) == HeadOfIC(ValueOfInterfaceCont(ast))
RemoveFirstInterface(ast) == RemoveFromHead(ValueOfInterfaceCont(ast))
GetAllInterfaces(ast) == ValueOfInterfaceCont(ast)
======================================================
