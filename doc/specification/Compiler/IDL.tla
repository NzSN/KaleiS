----------------------------- MODULE IDL -----------------------------------
EXTENDS Interfaces
LOCAL INSTANCE Defines
LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals

CONSTANTS NULL

SentenceIDL(Is (* Interfaces *)) == InterfaceCont(SentenceCat, Is)
IsSentenceIDL(sentences) ==
    /\ sentences # NULL
    /\ TypeOfInterfaceCont(sentences) = SentenceCat
ContentOfIDLSentence(sentences) == ValueOfInterfaceCont(sentences)
============================================================================
