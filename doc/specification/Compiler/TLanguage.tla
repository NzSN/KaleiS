------------------------ MODULE TLanguage -------------------------
EXTENDS Defines, Sequences, Interfaces
CONSTANTS NULL

SentenceTarget(Is (* Interfaces *)) == InterfaceCont(TSentenceCat, Is)
===================================================================
