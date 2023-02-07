# C++ Basics
## Important notes
** *
### Statements and the structure of a program
** *

* A **statement** is an instruction in a computer* program* that tells the computer to perform an action.

* A **function** is a collection of statements that executes sequentially.

* There are many different kinds of statements in C++:
    * Declaration statements
    * Jump statements
    * Expression statements
    * Compound statements
    * Selection statements (conditionals)
    * Iteration statements (loops)
    * Try blocks


* Every C++ program must have a special function named **main** (all lower case letters). When the program is run, the statements inside of main are executed in sequential order.

* **Programs** are collections of instructions that manipulate data to produce a desired result.

### Introduction to objects and variables
** *

* **Data** is any information that can be moved, processed, or stored by a computer.
* A **value** is a single piece of data stored in memory.
* A **variable** is a named region of memory.
* An **identifier** is the name that a variable is accessed by.
* A **type** tells the program how to interpret a value in memory.
* In C++, the type of a variable must be known at **compile-time** (when the program is compiled), and that type can not be changed without recompiling the program or by assigning to a different variable by conversion. 
* Here’s an example of defining a variable named x: 
    ```cpp
    int x; // define a variable named x, of type int
    ```
* When the program is **run** (called runtime), the variable will be instantiated.
* **Instantiation** is a fancy word that means the object will be **created** and assigned a **memory address**. Variables must be instantiated before they can be used to store values.

### Variable assignment and initialization
** *
* **Variable assignment:** After a variable has been defined, you can give it a value (in a separate statement) using the = operator. This process is called copy assignment (or just assignment) for short.
* **Initalization**: One downside of assignment is that it requires at least two statements: one to **define the variable**, and one to **assign the value**. These two steps can be combined. When a variable is defined, you can also provide an initial value for the variable at the same time. This is called **initialization**. The value used to initialize a variable is called an **initializer**.
* There are 6 basic ways to initialize variables in C++:
    ```cpp
    int a;         // no initializer (default initialization)
    int b = 5;     // initializer after equals sign (copy initialization)
    int c( 6 );    // initializer in parenthesis (direct initialization)

    // List initialization methods (C++11)
    int d { 7 };   // initializer in braces (direct list initialization)
    int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
    int f {};      // initializer is empty braces (value initialization)
    ```
* Modern compilers will typically generate warnings if a variable is **initialized** but **not used** (since this is rarely desirable). And if “treat warnings as errors” is enabled, these warnings will be promoted to errors and cause the compilation to fail.
    * In **C++17**, the best solution is to use the `[[maybe_unused]]` attribute. This attribute tells the compiler to expect that the variable may not be used, so it will not generate unused variable warnings.
    ```cpp
    int main()
    {
        [[maybe_unused]] int x { 5 };

        // since x is [[maybe_unused]], no warning generated

        return 0;
    }
    ```
### Operators: Basics
** *
* In mathematics, an **operation** is a mathematical calculation involving zero or more input values (called **operands**) that produces a new value (called an **output** value)
* The specific operation to be performed is denoted by a symbol called an **operator**.
* The number of operands that an operator takes as input is called the operator’s **arity**.

* Operators in C++ come in **four different arities**:
    * **Unary operators** act on one operand. An example of a *unary operator* is the - operator. For example, given `-5`, `operator-` takes literal operand 5 and flips its sign to produce new output value -5.
    * **Binary operators** act on two operands (often called left and right, as the left operand appears on the left side of the operator, and the right operand appears on the right side of the operator). An example of a binary operator is the `+` operator. For example, given `3 + 4`, `operator+` takes the left operand 3 and the right operand 4 and applies mathematical addition to produce new output value 7.
    * **Ternary operators** act on three operands. There is only one of these in C++ (the conditional operator), which we’ll cover later.
    * **Nullary operators** act on zero operands. There is also only one of these in C++ (the `throw` operator), which we’ll also cover later.
* An **expression** is a combination of literals, variables, operators, and function calls that calculates a single value. The process of executing an expression is called **evaluation**, and the single value produced is called the **result of the expression**.
