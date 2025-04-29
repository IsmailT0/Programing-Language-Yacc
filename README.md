# EON Programming Language
  

**Group Members**: İsmail Temüroğlu, Can Dündar, Emre Topcu, Ömer Lütfi Duran
  

## Language Overview

EON is a statically-typed programming language with a clean syntax that emphasizes readability and explicit type declarations. It features unique control flow keywords, specialized operators, and a distinctive statement termination approach using colons.


## Syntax & Features

### Variable Declaration and Types

Variables must be declared with explicit types using the `::` operator:

variableName :: type = value:

*Supported primitive types:*

- `int`: Integer values

- `float`: Floating-point numbers

- `string`: Text strings enclosed in single quotes

- `ch`: Single character values enclosed in double quotes

- `bool`: Boolean values (`True` or `False`)

  

*Examples:*

- count :: int = 42:

- pi :: float = 3.14159:

- name :: string = 'John Doe':

- grade :: ch = "A":

- isValid :: bool = True:

  
  

### Constants

Constants are declared using the `CON` keyword:

- CON NAME :: type = value:

Example:

CON PI :: float = 3.14159: CON MAX_SIZE :: int = 100:

  
  
  

### Comments

- Single-line comments: Begin with `---`

--- This is a single line comment

- Multi-line comments: Enclosed between `-*` and `*-`

-* This is a multi-line comment *-

  
  
  

### Control Structures

#### Conditional Statements

- `when` / `otherwise`: Similar to if/else: 

	- when (condition) { // code } otherwise { // code }

- `unless`: Opposite of `when`, executes if condition is false:

	- unless (condition) { // code }


#### Loops 

- `ctloop` (count loop): Similar to a for loop

	- ctloop (initialization: condition: update) { // code }

- `cnloop` (continue loop): Similar to a while loop

	- cnloop (condition) { // code }


### Functions

Functions are declared using the `method` keyword:

method name(param :: type, param2 :: type) -> returnType { // function body return value: }


### Arrays

Arrays are declared with square brackets:

arrayName :: type[size] = [value1, value2, ...]:

Example:

numbers :: int[5] = [1, 2, 3, 4, 5]:
  

### Operators
- Arithmetic: `+`, `-`, `*`, `/`, `++`, `--`

- Assignment: `=`, `+=`, `-=`, `*=`, `/=`

- Comparison: `>`, `<`, `>=`, `<=`, `==`

- Logical: `&&` (AND), `||` (OR), `^^` (XOR)

- Bitwise: `&` (AND), `|` (OR), `^` (XOR)

  

### Input/Output
- Output: `write(expression)`

- Input: `input()`


### Statement Termination
All statements end with a colon `:` rather than a semicolon.


## Sample Code

```eon
method calculateArea(radius :: float) -> float {
    return PI * radius * radius:
}
```

  

```eon
method main() -> int {

    num :: int = 42:
    
    when (num > 0) {
        write('Positive number'):
    } otherwise {
        write('Non-positive number'):
    }

    ctloop (i :: int = 0: i < 10: i++) {
        write(i):
    }

    return 0:
}
```

  
## BNF Grammer
`<program>` ::= `<statement>`*

`<statement>` ::= `<variable-declaration>` 
                    | `<constant-declaration>` 
                    | `<function-declaration>` 
                    | `<control-structure>`
                    | `<expression-statement>`
                    | `<return-statement>` 
                    | `<io-statement>`
                    | `<comment>`

`<variable-declaration>` ::= `<identifier>` "::" `<type>` "=" `<expression>` ":"

`<constant-declaration>` ::= "CON" `<identifier>` "::" `<type>` "=" `<expression>` ":"

`<type>` ::= "int" | "float" | "string" | "ch" | "bool" | `<array-type>`

`<array-type>` ::= `<type>` "[" `<expression>` "]"

`<expression-statement>` ::= `<expression>` ":"

`<return-statement>` ::= "return" `<expression>` ":"

`<function-declaration>` ::= "method" `<identifier>` 
                                "(" `<parameter-list>` ")" 
                                    "->" `<type>` "{" `<statement>`* "}"

`<parameter-list>` ::= `<parameter>` ("," `<parameter>`)* | ε  
`<parameter>` ::= `<identifier>` "::" `<type>`

`<control-structure>` ::= `<when-statement>` 
                            | `<unless-statement>`
                            | `<ctloop>`
                            | `<cnloop>`

`<when-statement>` ::= "when" "(" `<expression>` ")" "{" `<statement>`* "}" 
                       ["otherwise" "{" `<statement>`* "}"]

`<unless-statement>` ::= "unless" "(" `<expression>` ")" "{" `<statement>`* "}"

`<ctloop>` ::= "ctloop" "(" `<initialization>` ":" `<condition>` ":" `<update>` ")" 
               "{" `<statement>`* "}"

`<initialization>` ::= `<variable-declaration-without-colon>` 
                            | `<expression>`

`<variable-declaration-without-colon>` ::= `<identifier>` "::" `<type>` "=" `<expression>`

`<condition>` ::= `<expression>`

`<update>` ::= `<expression>`

`<cnloop>` ::= "cnloop" "(" `<expression>` ")" "{" `<statement>`* "}"

`<expression>` ::= `<literal>` 
                            | `<identifier>` 
                            | `<array-literal>` 
                            | `<binary-expression>` 
                            |`<unary-expression>` 
                            | `<function-call>` 
                            | "(" `<expression>` ")"

`<literal>` ::= `<integer-literal>` 
                    | `<float-literal>` 
                    | `<string-literal>` 
                    | `<char-literal>` 
                    | `<bool-literal>`

`<integer-literal>` ::= [0-9]+

`<float-literal>` ::= [0-9]+ "." [0-9]*

`<string-literal>` ::= "'" [^']* "'"

`<char-literal>` ::= "\"" [^"] "\""

`<bool-literal>` ::= "True" | "False"

`<array-literal>` ::= "[" `<expression>` ("," `<expression>`)* "]"

`<binary-expression>` ::= `<expression>` `<binary-operator>` `<expression>`

`<binary-operator>` ::= "+" | "-" | "*" | "/" | "+=" | "-=" | "*=" | "/=" | 
                        ">" | "<" | ">=" | "<=" | "==" | "&&" | "||" | "^^" | "&" | "|" | "^"

`<unary-expression>` ::= `<unary-operator>` `<expression>`
                            | `<expression>` `<post-unary-operator>`

`<unary-operator>` ::= "+" | "-" | "!"

`<post-unary-operator>` ::= "++" | "--"

`<function-call>` ::= `<identifier>` "(" `<argument-list>` ")"

`<argument-list>` ::= `<expression>` ("," `<expression>`)* | ε

`<io-statement>` ::= "write" "(" `<expression>` ")" ":" | `<identifier>` "=" "input" "(" ")" ":"

`<comment>` ::= `<single-line-comment>` | `<multi-line-comment>`

`<single-line-comment>` ::= "---" [^\n]*

`<multi-line-comment>` ::= "-*" .* "*-"

`<identifier>` ::= [a-zA-Z_][a-zA-Z0-9_]*


## Program Execution
To execute your program:
1. Create a file with the `.eon` extension

2. Use the provided Makefile to compile the program

3. Run your program with:

``` bash

   make

   ./myprog < example.eon
```