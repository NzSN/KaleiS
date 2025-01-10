------------------- MODULE IRMain -------------------------
EXTENDS AST, Interfaces, Property
VARIABLES ir

Samples == {
             AST(<<Interface(0),
                    InterfaceWithProperties(2, <<EXTERNAL>>),
                    InterfaceWithProperties(3, <<EXTERNAL>>)>>)
            }
IR == INSTANCE IR WITH NULL <- NULL, ASTSamples <- Samples, ir <- ir

Spec == IR!Spec
===========================================================
