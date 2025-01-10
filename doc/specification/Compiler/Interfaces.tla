-------------------------- MODULE Interfaces ----------------------------
EXTENDS Naturals, Property, Sequences

(* Interface Definition *)
Interface(i) ==
    [ id |-> i, defined |-> FALSE, prop |-> <<>> ]
InterfaceWithProperties(I, Ps) ==
    [id |-> I, defined |-> FALSE, prop |-> Ps]
IsInterface(i) ==
    /\ i.id \in Nat
    /\ i.prop \in Properties
HasProp(I, kP) ==
    \E k \in DOMAIN I.prop: I.prop[k] = kP
IsAsyncInterface(i) == HasProp(i, ASYNCHRONOUS)
IsSyncInterface(i) == ~IsAsyncInterface(i)
IsWasmInterface(i) == HasProp(i, WASM_BINDING)
IsNodeInterface(i) == HasProp(i, NODE_NATIVE_BINDING)
SetToImplemented(i) ==
    [i EXCEPT !.defined = TRUE]
SetToUnimplemented(i) ==
    [i EXCEPT !.defined = FALSE]
IsSameInterface(li, ri) == li.id = ri.id

(* Interface Container *)
InterfaceCont(ContType, Is (* Sequence of Interfaces *)) ==
    [ type |-> ContType, value |-> Is ]
IsInterfaceCont(ic) ==
    /\ ic.type \in Nat
    /\ \A k \in 1..Len(ic): IsInterface(ic.value[k])
TypeOfInterfaceCont(IC) == IC.type
ValueOfInterfaceCont(IC) == IC.value
AppendToInterfaceCont(IC, I) ==
    IC' = [IC EXCEPT !.value = Append(@, I)]
HeadOfIC(IC) == Head(ValueOfInterfaceCont(IC))
RemoveFromHead(IC) ==
    IC' = [IC EXCEPT !.value = Tail(@)]
IsImplemented(IC) == IC.defined = TRUE

========================================================================
