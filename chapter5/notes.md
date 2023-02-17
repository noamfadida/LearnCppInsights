# Operators
## Important notes
* Always use parentheses to disambiguate the precedence of operators if there is any question or opportunity for confusion.
* Why should you never do the following:
    * **a)**
        ```cpp  
        int y{ foo(++x, x) };
        ```
        Because operator++ applies a side effect to x, we should not use x again in the same expression. In this case, the parameters to function foo() can be evaluated in any order, so it’s indeterminate whether x or ++x gets evaluated first. Because ++x changes the value of x, it’s unclear what values will be passed into the function.

    * **b)**
        ```cpp  
        double x{ 0.1 + 0.1 + 0.1 }; return (x == 0.3);
        ```
        Floating point rounding errors will cause this to evaluate as false even though it looks like it should be true.

    * **c)**
        ```cpp  
        int x{ 3 / 0 };
        ```
        Division by 0 causes undefined behavior, which is likely expressed in a crash.
### Parenthesization of the conditional operator
***
* It is common convention to put the **conditional part** of the operation inside of **parentheses**, both to make it easier to read, and also to make sure the precedence is correct.
    * For example, to print the larger of values x and y to the screen, we could do this:
        ```cpp
        if (x > y)
            std::cout << x << '\n';
        else
            std::cout << y << '\n';
        ```
        Or we could use the **conditional(trenary) operator** to do this:
        ```cpp
        std::cout << ((x > y) ? x : y) << '\n';
        ```
        Let’s examine what happens if we **don’t parenthesize** the whole conditional operator in the above case. 
        <br/>Because the `<<` operator has higher precedence than the `?:` operator, the statement:
        ```cpp
        std::cout << (x > y) ? x : y << '\n';
        ```
        whould evaluate as:
        ```cpp
        (std::cout << (x > y)) ? x : y << '\n';
        ```
        That would print 1 (true) if x > y, or 0 (false) otherwise!


### Comparison of calculated floating point values can be problematic
***
* Consider the following program:
    ```cpp
    #include <iostream>

    int main()
    {
        double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
        double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

        if (d1 == d2)
            std::cout << "d1 == d2" << '\n';
        else if (d1 > d2)
            std::cout << "d1 > d2" << '\n';
        else if (d1 < d2)
            std::cout << "d1 < d2" << '\n';

        return 0;
    }
    ```
    Variables d1 and d2 should both have value 0.01. But this program prints an unexpected result:
    ```
    d1 > d2
    ```
    If you inspect the value of d1 and d2 in a debugger, you’d likely see that d1 = 0.0100000000000005116 and d2 = 0.0099999999999997868. Both numbers are close to 0.01, but d1 is greater than, and d2 is less than.

    **If a high level of precision is required, comparing floating point values using any of the relational operators can be dangerous**. This is because floating point values *are not precise*, and ***small rounding errors*** in the floating point operands may cause unexpected results.

* Avoid using `operator== `and `operator!=` to compare floating point values if there is any chance those values have been calculated.

*  **It is okay** to compare a low-precision (few significant digits) floating point literal to the same literal value of the same type.

    * For example, if a function returns such a literal (typically 0.0, or sometimes 1.0), it is safe to do a direct comparison against the same literal value of the same type:
        ```cpp
        if (someFcn() == 0.0) // okay if someFcn() returns 0.0 as a literal only
        // do something
        ```
* The most common method of doing floating point equality involves using a function that looks to see if two numbers are **almost the same**. If they are **“close enough”**, then we call them equal.

* The value used to represent **“close enough”** is traditionally called **`epsilon`**. **`Epsilon`** is generally defined as a small positive number (e.g. 0.00000001, sometimes written 1e-8). 
    ```cpp
    #include <cmath> // for std::abs()

    // epsilon is an absolute value
    bool approximatelyEqualAbs(double a, double b, double absEpsilon)
    {
        // if the distance between a and b is less than absEpsilon, then a and b are "close enough"
        return std::abs(a - b) <= absEpsilon;
    }
    ```

#### **As an aside…**

```html
If we say any number that is within 0.00001 of another number should be treated as the same number, then:

* 1 and 1.0001 would be different, but 1 and 1.00001 would be the same. That’s not unreasonable.
* 0.0000001 and 0.00001 would be the same. That doesn’t seem good, as those numbers are two orders of magnitude apart.
* 10000 and 10000.00001 would be different. That also doesn’t seem good, as those numbers are barely different given the magnitude of the number.
```
Donald Knuth, a famous computer scientist, suggested the following method in his book “The Art of Computer Programming, Volume II: Seminumerical Algorithms (Addison-Wesley, 1969)”:
```cpp
#include <algorithm> // std::max
#include <cmath> // std::abs

// return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
    return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
```
This solution is also not perfect, especially as the numbers approach to zero. The recommend solution is to combine between the both approches:
```cpp
// return true if the difference between a and b is less than absEpsilon, or within relEpsilon percent of the larger of a and b
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{ std::abs(a - b) };
    if (diff <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
```
In this algorithm, we first check if a and b are close together in **absolute terms**, which handles the case where **a and b are both close to zero**. The `absEpsilon` parameter should be set to something very small (e.g. 1e-12). If that **fails**, then we fall back to **Knuth’s algorithm**, using the `relative epsilon`.

### Short circuit evaluation
***
* In order for `logical AND` to return `true`, both operands must evaluate to `true`. If the first operand evaluates to `false`, `logical AND` knows it must return `false` **regardless of whether the second operand evaluates to true or false**. In this case, the logical AND operator will go ahead and return false **immediately without even evaluating the second operand!** This is known as **short circuit evaluation**, and it is done primarily for *optimization* purposes.
* Similarly, if the first operand for logical OR is true, then the entire OR condition has to evaluate to true, and the second operand won’t be evaluated.
* **Short circuit evaluation** may cause Logical OR and Logical AND to not evaluate one operand. **Avoid** using expressions with side effects in conjunction with these operators.

### De Morgan's law
***
* Many programmers also make the mistake of thinking that `!(x && y)` is the same thing as `!x && !y`. Unfortunately, you can not “distribute” the logical NOT in that manner.
* **De Morgan’s law** tells us how the logical NOT should be distributed in these cases:
    * `!(x && y)` is equivalent to `!x || !y`
    * `!(x || y)` is equivalent to `!x && !y`
    </br>In other words, when you distribute the logical NOT, you also need to flip logical AND to logical OR, and vice-versa!

#### Alternative operator representations
* Many operators in C++ (such as operator ||) have names that are just symbols. Historically, not all keyboards and language standards have supported all of the symbols needed to type these operators. As such, C++ supports an alternative set of keywords for the operators that use words instead of symbols. For example, instead of ||, you can use the keyword or.
    * `&&` <--> `and`
    * `||` <--> `or`
    * `!`  <--> `not`
