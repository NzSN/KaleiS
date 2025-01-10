--------------------------- MODULE Defines ----------------------------
EXTENDS Naturals

\* Category Definitions

\* Runtime structure that can be manipulate directly by
\* Programming Language.
InnerCat == 0

\* Property that can be attach to Interfaces.
PropertyCat  == 1

\* Sentence of IDL language
SentenceCat  == 2

\* Sentence of target language, target language is the language
\* that used to implement interfaces that declared by 'SentenceCat'.
TSentenceCat == 3

\* Abstract Syntax Tree that be got by parsed of sentence of 'SentenceCat'
ASTCat       == 4

\* For the purposes of reduce the scale of states
\* this specification use this definition to control
\* size of interface set.
CARDINALITY_LIMIT == 3

CODOMAIN(F) == { F[x] : x \in DOMAIN F  }
=======================================================================
