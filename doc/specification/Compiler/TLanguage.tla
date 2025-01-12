------------------------ MODULE TLanguage -------------------------
EXTENDS Defines, Sequences
CONSTANTS NULL

InterfaceT[n \in 0..CARDINALITY_LIMIT] ==
    [ tsentence |-> <<TSentenceCat,n>>, prop |-> NULL ]
InterfaceTs == { InterfaceT[n] : n \in 0..CARDINALITY_LIMIT }
TSentences == Seq(InterfaceTs)

GetInterfaceDef(i) == i.tsentence[2]
===================================================================
