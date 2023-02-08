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

### Name Collisions and Namespaces
***
* A **namespace** is a ***region*** that allows you to declare names inside of it for the purpose of ***disambiguation***. The namespace provides a scope region (called **namespace scope**) to the names declared inside of it
* In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of an implicitly defined namespace called the **global namespace** (sometimes also called the *global scope*).
    * Only **declarations** and **definition statements** can appear in the **global namespace**.
    * Other types of statements (such as expression statements) cannot be placed in the **global namespace** (initializers for global variables being an exception) 
    ```cpp
    #include <iostream> // handled by preprocessor

    // All of the following statements are part of the global namespace
    void foo();    // okay: function forward declaration in the global namespace
    int x;         // compiles but strongly discouraged: uninitialized variable definition in the global namespace
    int y { 5 };   // compiles but discouraged: variable definition with initializer in the global namespace
    x = 5;         // compile error: executable statements are not allowed in the global namespace

    int main()     // okay: function definition in the global namespace
    {
        return 0;
    }

    void goo();    // okay: another function forward declaration in the global namespace
    ```
* The `::` symbol is an operator called the **scope resolution** operator. 
    * The identifier to the *left* of the `::` symbol identifies the *namespace* that the name to the *right* of the `::` symbol is contained within.

* A `using` directive allows us to access the names in a namespace without using a namespace prefix.
    * Avoid using-directives (such as using namespace std;) at the top of your program or in header files. They violate the reason why namespaces were added in the first place.

### Intro to Preprocessor
***
* **Prior** to compilation, each code (.cpp) file goes through a **preprocessing phase**. 
    * When the preprocessor runs, it scans through the code file (from top to bottom), looking for **preprocessor directives**
    
* **Preprocessor directives** (often just called directives) are instructions that start with a `#` symbol and end with a `newline` **(NOT a semicolon)**. These directives tell the preprocessor to perform certain text manipulation tasks. .

* **`#include` directive**: When you #include a file, the preprocessor replaces the #include directive with the contents of the included file. The included contents are then preprocessed (along with the rest of the file), and then compiled.
    ```cpp
    #include <iostream>
    ```
* **`#define` directive**: The #define directive can be used to create a macro. In C++, a macro is a rule that defines how input text is converted into replacement output text. There are two basic types of macros:
    * **Object-like macros**: can be defined in one of the two ways - 
        ```cpp
        #define identifier
        #define identifier substitution_text
        ```
        The top definition has no substitution text, whereas the bottom one does. Because these are preprocessor directives (not statements), note that neither form ends with a semicolon.
    * **Function-like macros**(Not safety): act like functions, and serve a similar purpose. 
        ```cpp
        // Macro to calculate area of a rectangle.
        #define AREA(l, b) (l * b)
        ```

* **Conditional compilation directives**: these directives allow you to specify under what conditions something will or won’t compile. 
    * **`#ifdef` directive**: allows the preprocessor to check whether an identifier has been previously `#defined`. **If so**, the code between the #ifdef and matching `#endif` is **compiled**. **If not**, the code is **ignored**.
        * Can be seen as `#if defined(condition)`.
        ```cpp
        #include <iostream>

        #define PRINT_JOE

        int main()
        {
        #ifdef PRINT_JOE
            std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
        #endif

        #ifdef PRINT_BOB
            std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
        #endif

            return 0;
        }
        ```
    * **`#ifndef` directive**: the **opposite** of `#ifdef`, in that it allows you to check whether an identifier has ***NOT*** been `#defined` yet.
        * Can be seen as `#if !defined(condition)`.
        ```cpp
        #include <iostream>

        int main()
        {
        #ifndef PRINT_BOB
            std::cout << "Bob\n";
        #endif

            return 0;
        }
        ```
    * **`#if 0` directive**: exclude a block of code from being compiled (as if it were inside a comment block):
        ```cpp
        #include <iostream>

        int main()
        {
            std::cout << "Joe\n";

        #if 0 // Don't compile anything starting here
            std::cout << "Bob\n";
            std::cout << "Steve\n";
        #endif // until this point

            return 0;
        }
        ```
    * **`#endif` directive**: end of if condition block.

* **`#defines` scope**: Directives are resolved before compilation, from top to bottom on a file-by-file basis. 
    * Remember! The preprocessor does't understand C++ at all. Example for that:
        ```cpp
        #include <iostream>

        void foo()
        {
        #define MY_NAME "Alex"
        }

        int main()
        {
            std::cout << "My name is: " << MY_NAME << '\n';

            return 0;
        }
        ```
        **Output** will be: `"My name is: Alex"`
    * Directives are only valid from the point of definition to the **end of the file** in which they are defined. Directives defined in *one code file do not have impact on other code files* in the same project.
        ```cpp
        //function.cpp
        #include <iostream>

        void doSomething()
        {
        #ifdef PRINT
            std::cout << "Printing!\n";
        #endif
        #ifndef PRINT
            std::cout << "Not printing!\n";
        #endif
        }
        ```
        ```cpp
        //main.cpp
        void doSomething(); // forward declaration for function doSomething()

        #define PRINT

        int main()
        {
            doSomething();

            return 0;
        }
        ```
        **Output** will be: `Not printing!"`

### Header files
***
* **Header files** usually have a `.h` extension, but you will occasionally see them with a `.hpp` extension or no extension at all. 
* The primary purpose of a header file is to **propagate declarations** to code files.
* When you `#include` a file, the **content** of the included file is inserted at the point of inclusion. This provides a useful way to pull in declarations from another file.
* **Header files** should generally ***NOT*** contain function and variable *definitions*, so as not to violate the one definition rule. An exception is made for symbolic constants 
* **Including header files from other directories**:
    * One (bad) way to do this is to include a relative path to the header file you want to include as part of the `#include` line. For example:
        ```cpp
        #include "headers/myHeader.h"
        #include "../moreHeaders/myOtherHeader.h"
        ```
        The downside of this approach is that it requires you to reflect your directory structure in your code. If you ever update your directory structure, your code won’t work anymore.
    * A better method is to tell your compiler or IDE that you have a bunch of header files in some other location, so that it will look there when it can’t find them in the current directory.
    <br/>**VSCode:** In your tasks.json configuration file, add a new line in the “Args” section:
        ```json
        "-I/source/includes",
        ``` 
* **Best practive:** Each file should explicitly #include all of the header files it needs to compile. Do not rely on headers included transitively from other headers.

* To maximize the chance that missing includes will be flagged by compiler, order your #includes as follows:
    * The paired header file
    * Other headers from your project
    * 3rd party library headers
    * Standard library headers

    The headers for each grouping should be sorted alphabetically.

#### Header Guards
***
Consider the following academic example:
> square.h
```cpp
// We generally shouldn't be defining functions in header files
// But for the sake of this example, we will
int getSquareSides()
{
    return 4;
}
```
> geomtry.h
```cpp
#include "square.h"
```
> main.cpp
```cpp
#include "square.h"
#include "geometry.h"

int main()
{
    return 0;
}
```
**What's happening here?**
First, **main.cpp** `#includes square.h`, which copies the definition for function `getSquareSides` into **main.cpp**. Then **main.cpp** `#includes geometry.h`, which `#includes square.h` itself. This copies contents of **square.h** (including the definition for function getSquareSides) into **geometry.h**, which then gets copied into main.cpp.
> After preprocessing
```cpp
int getSquareSides() // from square.h 
{
    return 4;
}

int getSquareSides() // from geometry.h (via square.h)
{
    return 4;
}

int main()
{
    return 0;
}
```
>*>*> **Result**: Duplicate definitions and a compile error

* **Header guards** are conditional compilation directives that take the following form:
    ```cpp
    #ifndef SOME_UNIQUE_NAME_HERE
    #define SOME_UNIQUE_NAME_HERE

    // your declarations (and certain types of definitions) here

    #endif
    ```
* When this header is #included, the preprocessor checks whether SOME_UNIQUE_NAME_HERE has been previously defined. If this is the first time we’re including the header, SOME_UNIQUE_NAME_HERE will not have been defined. Consequently, it #defines SOME_UNIQUE_NAME_HERE and includes the contents of the file. If the header is included again into the same file, SOME_UNIQUE_NAME_HERE will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored (thanks to the #ifndef).

#### #pragma once
***
Modern compilers support a simpler, alternate form of header guards using the `#pragma` directive:
```cpp
#pragma once

// your code here
```
* `#pragma once` serves the same purpose as `header guards`: to avoid a header file from being included multiple times. 
* With traditional `**header guards**`, the developer uses **preprocessor directives** to guard the header. With `**#pragma once**`, we’re asking the **compiler** to guard the header