# AST Generator
A program that transform TreeSitter NodeTypes into Strongly-typed AST in C++.

# Transform Example

For example, there is a leaf node in json format.

``` json
{
  "type": "this", 
  "named": true,
}
```

Then correspond CPP code is generated as

``` c++
class This : public Leaf {
    
};
```
