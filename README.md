# EON Programming Language

**Group Members**: İsmail Temüroğlu, Can Dündar, Emre Topcu, Ömer Lütfi Duran

## Language Overview

EON is a statically-typed programming language with a clean syntax that emphasizes readability and explicit type declarations. It features unique control flow keywords, specialized operators, and a distinctive statement termination approach using colons.

## Syntax & Features

### Variable Declaration and Types

Variables must be declared with explicit types using the `::` operator:

variableName :: value:

_Supported primitive types:_

- `int`: Integer values

- `float`: Floating-point numbers

- `string`: Text strings enclosed in single quotes

- `ch`: Single character values enclosed in double quotes

- `bool`: Boolean values (`True` or `False`)

Bare in mind that naming of a variable may only have 1 character.

_Examples:_

- c :: 42:

- d :: 3.14159:

- n :: 'John Doe':

- g :: "A":

- i :: True:

### Comments

- Single-line comments: Begin with `---`

--- This is a single line comment

- Multi-line comments: Enclosed between `-*` and `*-`

-_ This is a multi-line comment _-

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
when (k > 4) {
    write(5):
    write(6):
    write(7):
    write(8):
    write(9):
    write(10):

} otherwise {
    write(1):
    write(2):
    write(3):
}
```

## BNF Grammer

`<program>` ::= `<function>`

`<function>` ::= `<function>` `<stmt>` | ε

`<stmt>` ::=
COLON
| `<expr>` COLON
| PRINT `<expr>` COLON
| IDENTIFIER ASSIGN `<expr>` COLON
| WHILE LEFT_PARENTHESIS `<expr>` RIGHT_PARENTHESIS `<stmt>`
| IF LEFT_PARENTHESIS `<expr>` RIGHT_PARENTHESIS `<stmt>`
| IF LEFT_PARENTHESIS `<expr>` RIGHT_PARENTHESIS `<stmt>` ELSE `<stmt>`
| LEFT_BRACE `<stmt_list>` RIGHT_BRACE
| `<comment>` `<stmt_list>`
| `<try_catch_stmt>`
| `<throw_stmt>`

`<try_catch_stmt>` ::=
TRY `<stmt>` `<catch_clauses>`
| TRY `<stmt>` `<catch_clauses>` `<finally_clause>`

`<catch_clauses>` ::=
`<catch_clause>`
| `<catch_clauses>` `<catch_clause>`

`<catch_clause>` ::=
CATCH LEFT_PARENTHESIS INTEGER RIGHT_PARENTHESIS `<stmt>`
| CATCH LEFT_PARENTHESIS RIGHT_PARENTHESIS `<stmt>`

`<finally_clause>` ::= FINALLY `<stmt>`

`<throw_stmt>` ::= THROW `<expr>` COLON

`<stmt_list>` ::=
`<stmt>`
| `<stmt_list>` `<stmt>`

`<comment>` ::= COMMENTLINE | OPENCOMMENT

`<expr>` ::=
INTEGER
| IDENTIFIER
| MINUS `<expr>`
| `<expr>` PLUS `<expr>`
| `<expr>` MINUS `<expr>`
| `<expr>` MULTIPLE `<expr>`
| `<expr>` DIVIDE `<expr>`
| `<expr>` LESSTHAN `<expr>`
| `<expr>` GREATERTHAN `<expr>`
| `<expr>` EQUALORGREAT `<expr>`
| `<expr>` EQUALORLESS `<expr>`
| `<expr>` ISNOTEQUAL `<expr>`
| `<expr>` EQUAL `<expr>`
| LEFT_PARENTHESIS `<expr>` RIGHT_PARENTHESIS

## Program Execution

To execute your program:

1. Create a file with the `.eon` extension

2. Use the provided Makefile to compile the program

3. Run your program with:

```bash

   make

   ./myprog < example.eon
```
