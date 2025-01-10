# KaleiS

Motivation of this project is to provide a convenient, flexible ways to specify
JavaScript/TypeScript interfaces that implemented by WASM or Native.

# How to specify Interfaces

```
interface NatPair {
  fst :: Nat,
  snd :: Nat,
}

[NativeBind]
Plus(n :: Nat) :: Nat {
  return n + 1;
}

[NativeBind, External]
Ping :: Nat;
```

this lead to following javascript 

```
interface NatPair {
   fst: number,
   snd: number,
}

function Plus(n: number): number {
  ...
}

function Ping(): number {
  ...
}
```

and C++ source file that can be used to build wasm or node native modules.
