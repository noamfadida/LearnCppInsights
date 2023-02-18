# Bit Manipulation
## Important notes
On modern computer architectures, the smallest addressable unit of memory is a byte. Since all objects need to have unique memory addresses, this means objects must be at least one byte in size. For most variable types, this is fine. However, for Boolean values, this is a bit wasteful (pun intended). Boolean types only have two states: true (1), or false (0). This set of states only requires one bit to store. However, if a variable must be at least a byte, and a byte is 8 bits, that means a Boolean is using 1 bit and leaving the other 7 unused.
### Bit flags
***
* To define a set of bit flags, we’ll typically use an unsigned integer of the appropriate size (8 bits, 16 bits, 32 bits, etc… depending on how many flags we have), or std::bitset.

    ```cpp
    #include <bitset> // for std::bitset

    std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
    ```
### Bit numbering and bit positions
***
* Given a sequence of bits, we typically number the bits from right to left, starting with 0 (not 1). Each number denotes a bit position.
    ```cpp
    76543210  Bit position
    00000101  Bit sequence
    ```
    Given the bit sequence 0000 0101, the bits that are in position 0 and 2 have value 1, and the other bits have value 0.

### std::bitset
***
* `std::bitset` provides 4 key functions that are useful for doing **bit manipulation**:
    * `test()` allows us to query whether a bit is a 0 or 1
    * `set()` allows us to turn a bit on (this will do nothing if the bit is already on)
    * `reset()` allows us to turn a bit off (this will do nothing if the bit is already off)
    * `flip()` allows us to flip a bit value from a 0 to a 1 or vice versa
    <br>Each of these functions takes the position of the bit we want to operate on as their only argument.<br/>

* An example:
    ```cpp
    #include <bitset>
    #include <iostream>

    int main()
    {
        std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
        bits.set(3); // set bit position 3 to 1 (now we have 0000 1101)
        bits.flip(4); // flip bit 4 (now we have 0001 1101)
        bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

        std::cout << "All the bits: " << bits << '\n';
        std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
        std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

        return 0;
    }
    ```
    This prints:
    ```cpp
    All the bits: 00001101
    Bit 3 has value: 1
    Bit 4 has value: 0
    ```

* **The size of `std::bitset`**: One potential surprise is that std::bitset is optimized for speed, not memory savings. The size of a std::bitset is typically the number of bytes needed to hold the bits, rounded up to the nearest sizeof(size_t), which is 4 bytes on 32-bit machines, and 8-bytes on 64-bit machines.

    Thus, a std::bitset<8> will typically use either 4 or 8 bytes of memory, even though it technically only needs 1 byte to store 8 bits. Thus, std::bitset is most useful when we desire convenience, not memory savings.

### Bitwise operators

* The **bitwise left shift (`<<`) operator** shifts bits to the left. The **left operand** is the **expression to shift** the bits of, and the **right operand** is an integer **number of bits to shift left by**.
    * So when we say x << 1, we are saying “shift the bits in the variable x left by 1 place”. New bits shifted in from the right side receive the value 0.
    ```cpp
    0011 << 1 is 0110
    0011 << 2 is 1100
    0011 << 3 is 1000
    ```
* The **bitwise right shift (`>>`) operator** shifts bits to the right.
    ```cpp
    1100 >> 1 is 0110
    1100 >> 2 is 0011
    1100 >> 3 is 0001
    ```
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> x { 0b1100 };

    std::cout << x << '\n';
    std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
    std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000

    return 0;
}
```
* The **bitwise NOT operator (`~`)** is perhaps the easiest to understand of all the bitwise operators. It simply flips each bit from a 0 to a 1, or vice versa. Note that the result of a bitwise NOT is dependent on what size your data type is.

* The **Bitwise OR (`|`)** works much like its logical OR counterpart. However, instead of applying the OR to the operands to produce a single result, bitwise OR applies to each bit! 

* The **Bitwise AND (`&`)** works similarly to the above. Logical AND evaluates to true if both the left and right operand evaluate to true. Bitwise AND evaluates to true (1) if both bits in the column are 1.

* The last operator is the **bitwise XOR (`^`)**, also known as exclusive or. When evaluating two operands, XOR evaluates to true (1) if one and only one of its operands is true (1). If neither or both are true, it evaluates to 0. 

