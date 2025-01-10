--------------------- MODULE InnerRepresent ----------------------
LOCAL INSTANCE Sequences
LOCAL INSTANCE Naturals
LOCAL INSTANCE Defines
LOCAL INSTANCE Property

CONSTANTS NULL

Interface[n \in 0..CARDINALITY_LIMIT] == [ interface |-> <<InnerCat,n>>, prop |-> NULL]
Interfaces == { Interface[n] : n \in 0..CARDINALITY_LIMIT }

GetInterfaceDef(i) == i.interface[2]
=============================================================
