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

Properties == { <<PropertyCat,n>> : n \in 0..CARDINALITY_LIMIT }
Property[n \in 0..CARDINALITY_LIMIT] == <<PropertyCat,n>>
===========================================================================
