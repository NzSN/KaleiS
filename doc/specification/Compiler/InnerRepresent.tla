--------------------- MODULE InnerRepresent ----------------------
EXTENDS Sequences, Naturals, Defines, Property, Interfaces
CONSTANTS NULL

InnerRep(Is (* Interface *)) == InterfaceCont(InnerCat, Is)
IsInnerRep(i) == TypeOfInterfaceCont(i) = InnerCat
ContentOfInnerRep(i) == ValueOfInterfaceCont(i)
=============================================================
