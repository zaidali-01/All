# LLVM IR Generator

This project demonstrates how to use the LLVM API in C++ to generate LLVM Intermediate Representation (IR). The program defines a function that performs the modulus (`%`) operation and generates the corresponding LLVM IR dynamically. It also includes a `main` function that prints `"Hello, World!"` and calls the modulus function.

---

## How the Program Works
The program utilizes the LLVM API to:
1. Create an LLVM Module: This serves as a container for all functions and global variables.
2. Define a Modulus Function:  
   `int mod(int x, int y)` performs `x % y` and returns the result.
3. Define the `main` Function:  
   Calls `printf` to print `"Hello, World!"`.
   Calls `mod(10, 3)` and stores the result.
4. Generate LLVM IR Code: The program prints the generated IR to `stdout`, which can be saved in a `.ll` file.


### Prerequisites
Ensure LLVM is installed. Check with:
```sh
llvm-config --version