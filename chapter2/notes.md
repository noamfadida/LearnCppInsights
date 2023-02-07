# C++ Basics: Functions and Files
## Important notes
** *

### Why functions?
***
*  Functions provide a number of benefits that make them extremely useful in programs of non-trivial length or complexity:
    * **Organization** - reduce a complicated program into smaller, more manageable chunks, which reduces the overall complexity of our program.
    * **Reusability** - Once a function is written, it can be called multiple times from within the program. This avoids duplicated code (“Don’t Repeat Yourself”) and minimizes the probability of copy/paste errors.
    * **Testing** - Functions are self-contained, once we’ve tested a function to ensure it works, we don’t need to test it again unless we change it.
    * **Extensiblity** -  When we need to extend our program to handle a case it didn’t handle before, functions allow us to make the change in one place and have that change take effect every time the function is called.
    * **Abstraction**- In order to use a function, you only need to know its name, inputs, outputs, and where it lives. You don’t need to know how it works, or what other code it’s dependent upon to use it.
### Functins return values
** *
* The C++ standard only defines the meaning of 3 **status codes**: `0, EXIT_SUCCESS, and EXIT_FAILURE`. 
    * `0` and `EXIT_SUCCESS` both mean the program executed successfully. 
    * `EXIT_FAILURE` means the program did not execute successfully.
* `EXIT_SUCCESS` and `EXIT_FAILURE` are **preprocessor macros** defined in the `<cstdlib>` header:
    ```cpp
    #include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
    int main()
    {
        return EXIT_SUCCESS;
    }
    ```

* C++ **disallows** calling the main function explicitly.

### Function parameters and arguments
** *
* A **function parameter** is a variable used in the header of a function. 
* **Function parameters** work almost identically to variables defined inside the function, but with one difference: they are initialized with a value provided by the caller of the function.

* **Pass-by-value** is a process that copies the given argument of the function call to a newly created variables (i.e to the appropriate function parameters).

### Local Scope
***
* Function parameters, as well as variables defined inside the function body, are called **local variables**
* **Function parameters** are created and initialized when the function is **entered**, and **variables** within the function body are created and initialized at the **point of definition**.
    * For example:
        ```cpp
        int add(int x, int y) // x and y created and initialized here
        {
            int z{ x + y }; // z created and initialized here

            return z;
        }
        ```

* **Local variables are destroyed** in the **opposite** order of creation at the end of the set of curly braces in which it is defined (or for a function parameter, at the end of the function).
    * In the previous example, z, y and x are destroyed at the end of the function.

* An **object’s lifetime** is defined to be the time between its creation and destruction.

* An **identifier’s scope** determines where the identifier can be accessed within the source code.
* When an identifier can be accessed, we say it is **in scope**.
*  When an identifier can not be accessed, we say it is **out of scope**. 
* **Scope** is a **compile-time** property, and trying to use an identifier when it is not in scope will result in a **compile error**.

* Names used for function parameters or variables declared in a function body are only visible within the function that declares them.

### Forward declarations and definitions
* The compiler compiles the contents of code files **sequentially**.
* An example for that:
    ```cpp
    #include <iostream>

    int main()
    {
        std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
        return 0;
    }

    int add(int x, int y)
    {
        return x + y;
    }
    ```
    When the compiler reaches the function call to add on line 5 of main, it doesn’t know what add is, because we haven’t defined add until line 9! That produces the error, identifier not found.

* A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually defining the identifier.
    * In the case of functions, this allows us to tell the compiler about the existence of a function before we define the function’s body

* Here's a **function declaration** for the ***add*** function:
    ```cpp
    int add(int x, int y); // function declaration includes return type, name, parameters, and semicolon.  No function body!
    ```
    * You also can forward declartion function without specify the names of the function parameters. (But it preferable to keep the names).
        ```cpp
        int add(int, int);
        ```

* **Definitions vs. Declarations**: 
    * A **definition** actually implements (for functions or types) or instantiates (for variables) the identifier. A **definition** is needed to satisfy the **linker**. If you use an identifier without providing a definition, the linker will error. Examples:
        ```cpp
        int add(int x, int y) // implements function add()
        {
            int z{ x + y }; // instantiates variable z

            return z;
        }
        ```
    * A **declaration** is a statement that tells the **compiler** about the existence of an identifier and its type information. A **declaration** is all that is needed to **satisfy the compiler**. This is why we can use a **forward declaration** to tell the compiler about an identifier that isn’t actually defined until later.
    Here are some examples of declarations:
        ```cpp
        int add(int x, int y); // tells the compiler about a function named "add" that takes two int parameters and returns an int.  No body!
        int x; // tells the compiler about an integer variable named x
        ```
    * In C++, all definitions also serve as declarations. This is why int x appears in our examples for both definitions and declarations. Since int x is a definition, it’s a declaration too. In most cases, a definition serves our purposes, as it satisfies both the compiler and linker. We only need to provide an explicit declaration when we want to use an identifier before it has been defined.
    * While it is true that all definitions are declarations, the converse is not true: not all declarations are definitions. An example of this is the function declaration -- it satisfies the compiler, but not the linker.

| Term	| Definition | Examples |
| :----: | :---: | :-------: |
| Definition | Implements a function or instantiates a variable. Definitions are also declarations.| void foo() { } // function definition<br/> int x; // variable definition |
| Declaration | Tells compiler about an identifier. Does not create the object or function. | void foo(); // function declaration<br/> int x; // variable declaration |
| Pure declaration | A declaration that isn’t a definition. | void foo(); |
| Initializer | Provides an initial value for a defined object. | int x { 2 }; // 2 is the initializer |
