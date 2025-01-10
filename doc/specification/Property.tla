----------------------------- MODULE Property -----------------------------
\* This module define property for individual interface.
EXTENDS Naturals

\* Binding Property
WASM_BINDING == 0
NODE_NATIVE_BINDING == 1

\* Synchronous Property
SYNCHRONOUS == 2
ASYNCHRONOUS == 3

Properties == { <<PropertyCat,n>> : n \in 0..CADINALITY_LIMIT }
Property[n \in 0..CADINALITY_LIMIT] == <<PropertyCat,n>>
===========================================================================
