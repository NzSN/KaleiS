----------------------------- MODULE Property -----------------------------
\* This module define property for individual interface.
EXTENDS Naturals

LOCAL INSTANCE Defines

\* Binding Property
WASM_BINDING == 0
NODE_NATIVE_BINDING == 1

\* Synchronous Property
SYNCHRONOUS == 2
ASYNCHRONOUS == 3

\* External implies that this interface is implemented by
\* external language.
EXTERNAL == 4

Property(n) == [ type |-> PropertyCat, prop |-> n ]
Properties == { Property(n) : n \in 0..CARDINALITY_LIMIT }

PropVal(p) == p.prop
===========================================================================
