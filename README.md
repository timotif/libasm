# Libasm
*Everything is open source when you speak assembly*

## Overview
Welcome to the **Libasm** project! This project is designed to help you get familiar with assembly language by implementing various functions in x86-64 assembly. The project includes a mix of C and assembly code to demonstrate the power and efficiency of low-level programming.
### Common instructions
• You must write 64 bits ASM. Beware of the "calling convention".
• You can’t do inline ASM, you must do ’.s’ files.
• You must compile your assembly code with nasm.
• You must use the Intel syntax, not the AT&T.

## Functions
### String Operations
| Function      | Description                          | Status |
|---------------|--------------------------------------|--------|
| `ft_strlen`   | Calculate the length of a string.    | ✅     |
| `ft_strcpy`   | Copy a string to another buffer.     | ✅     |
| `ft_strcmp`   | Compare two strings.                 | ✅     |
| `ft_strdup`   | Duplicate a string.                  | ✅     |
| `ft_atoi_base`| Convert a string to an integer with a given base. | ✅     |

### I/O Operations
| Function      | Description                          | Status |
|---------------|--------------------------------------|--------|
| `ft_write`    | Write data to a file descriptor.     | ✅     |
| `ft_read`     | Read data from a file descriptor.    | ✅     |

### Linked List Operations
| Function              | Description                                              | Status |
|-----------------------|----------------------------------------------------------|--------|
| `ft_list_push_front`  | Add an element to the front of the list.                 | ✅     |
| `ft_list_size`        | Get the size of the list.                                | ✅     |
| `ft_list_sort`        | Sort the list using a comparison function.               | ✅     |
| `ft_list_remove_if`   | Remove elements from the list based on a comparison function. | ✅     |

## Getting Started
The project is tested on Ubuntu Linux 24.04 LTS.
### Prerequisites
- **nasm**: The Netwide Assembler, used to assemble the assembly code.
- **GCC**: The GNU Compiler Collection, used to compile the C code.
- **Make**: A build automation tool to compile the project.
### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/timotif/libasm.git
    cd libasm
    ```

2. Build the project:
    ```sh
    make
    ```
3. Follow the instructions on the screen to run the tests or just use the static library `libasm_bonus.a` in your project.
### Usage
Check `make help` for more options.
## Features
- **Unit test**: A test suite to verify the functionality of the implemented functions.
  - Call `./test [mandatory | bonus | <function_name>]` to run the desired test.
  - *Debug* and *Profile* mode: `make debug` to see the output of each test and `make profile` to get the function's performance compared to its libc equivalent *(implemented for some)*.
- **String generator functions**: Utility functions to generate random strings for testing purposes.
  - Long string generator
  - Random string generator
  - Random printable string generator
	This makes the tests fairer by randomizing the input data.
- **Base case string collection**: An array of strings to test the functions with common edge cases. You can find it and edit it in `test_unit\src\main.c`. You can add your own test cases to it.
  *NB: make sure to keep the aray NULL-terminated!* 
- **List utility functions**: the file `test_unit/src/test_list_helpers.c` contains utility functions to create, print, compare and free linked lists and streamline the tests.
