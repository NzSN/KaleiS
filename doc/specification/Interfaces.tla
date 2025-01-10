--------------------- MODULE Interfaces ----------------------
LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Defines
LOCAL INSTANCE Property

CONSTANTS NULL

Interface[n \in 0..CADINALITY_LIMIT] == [ interface |-> <<InterfaceCat,n>>, prop |-> NULL]
Interfaces == { Interface[n] : n \in 0..CADINALITY_LIMIT }
=============================================================
