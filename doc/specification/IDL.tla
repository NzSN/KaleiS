----------------------------- MODULE IDL -----------------------------------
LOCAL INSTANCE Defines
LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals

CONSTANTS NULL

InterfaceIDL[n \in 0..CARDINALITY_LIMIT] == [ sentence |-> <<SentenceCat,n>>, prop |-> NULL]
InterfaceIDLs == { InterfaceIDL[n] : n \in 0..CARDINALITY_LIMIT }
Sentences == Seq(InterfaceIDLs)
============================================================================
