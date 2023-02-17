# Fundamental Data Types
## Important notes
** *
* Prefer **`int`** when the *size* of the integer **doesn’t matter*** (e.g. the number will always fit within the range of a 2-byte signed integer). For example, if you’re asking the user to enter their age, or counting from 1 to 10, it doesn’t matter whether int is 16 or 32 bits (the numbers will fit either way). This will cover the vast majority of the cases you’re likely to run across.
* Prefer **`std::int#_t`** when storing a **quantity** that needs a guaranteed range.
* Prefer **`std::uint#_t`** when doing **bit manipulation** or where well-defined wrap-around behavior is required.
* **Avoid** the following when possible:
    * Unsigned types for holding quantities
    * The 8-bit fixed-width integer types
    * The fast and least fixed-width types
    * Any compiler-specific fixed-width integers -- for example, Visual Studio defines `__int8`, `__int16`, etc…

* **`std::size_t`** is defined as an unsigned integral type, and it is typically used to represent the size or length of objects.
    * `size_t` is defined to be big enough to hold the size of the largest object creatable on your system (in bytes)

### Floating Point
***
* Floating point numbers are useful for storing very large or very small numbers, including those with fractional components.
* Floating point numbers often have small rounding errors, even when the number has fewer significant digits than the precision. Many times these go unnoticed because they are so small, and because the numbers are truncated for output. However, comparisons of floating point numbers may not give the expected results. Performing mathematical operations on these values will cause the rounding errors to grow larger.
* The **precision** of a number defines how many significant digits it can represent without information loss. 
* A **rounding error** can occur when too many significant digits are stored in a floating point number that can’t hold that much precision. Rounding errors happen all the time, even with simple numbers such as 0.1. Because of this, you *shouldn’t compare floating point numbers directly*.


### Sizeof operator
***
* The **`sizeof` operator** can be used to return the size of a type in bytes.


### Constant, Constexpr 
***
* A **constant** is a value that may not be changed. C++ supports two types of constants: **const variables, and literals**. A variables whose value can not be changed is called a constant variable. The `const` keyword is used to make a variable constant.
* **Const** variables must be initialized when you define them, and then that value can not be changed via assignment:
    ```cpp
    int main()
    {
        const double gravity; // error: const variables must be initialized
        gravity = 9.9;        // error: const variables can not be changed

        return 0;
    }
    ```

* A **symbolic constant** is a name given to a constant value. Constant variables are one type of symbolic constant, as are object-like macros with substitution text.
    ```cpp
    #include <iostream>
    #define MAX_STUDENTS_PER_CLASS 30

    int main()
    {
        std::cout << "The class has " << MAX_STUDENTS_PER_CLASS << " students.\n";

        return 0;
    }
    ```
* A **constant expression** is an expression that can be evaluated at compile-time.

* A **compile-time constant** is a constant whose value is known at compile-time. 

* A **runtime constant** is a constant whose initialization value isn’t known until runtime. 

```cpp
    #include <iostream>

    int getNumber()
    {
        std::cout << "Enter a number: ";
        int y{};
        std::cin >> y;

        return y;
    }

    int main()
    {
        const int x{ 3 };           // x is a compile time constant

        const int y{ getNumber() }; // y is a runtime constant

        const int z{ x + y };       // x + y is a runtime expression
        std::cout << z << '\n';     // this is also a runtime expression

        return 0;
    }
```

* A **constexpr variable** must be a compile-time constant. If the initialization value of a constexpr variable is not a constant expression, the compiler will error.

### Strings
***
* **`std::string`** offers an easy and safe way to deal with text strings. std::string lives in the <string> header. std::string is expensive to initialize and copy.

* **`std::string_view`** provides read-only access to an existing string (a C-style string literal, a std::string, or a char array) without making a copy.
