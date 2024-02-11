# string.h-Implementation

The `string.h-Implementation` project is a C library developed to mimic the functionality of the standard C library's `string.h`, with additional features inspired by the C# String class. This library is aimed at providing a comprehensive suite of string manipulation functions, including memory operations, string comparisons, concatenations, and more advanced string processing functionalities. It adheres to the C11 standard using the gcc compiler and is designed following the principles of structured programming without using deprecated features.

## Features

- Implements core string and memory manipulation functions such as `memcpy`, `memset`, `strncpy`, `strncat`, and more.
- Provides advanced string functionalities like `to_upper`, `to_lower`, `insert`, and `trim`.
- Includes partial implementation of `sprintf` and `sscanf` with support for common specifiers and flags.
- Ensures compatibility with ASCII encoded one-byte character strings.
- Adheres to Google's C Style for clean and maintainable code.
- Offers extensive unit testing coverage using the Check framework, ensuring reliability and correctness.

For more details, refer to the [string header file](include/custom_string.h) and [sscanf header file](custom_sscanf.h).

## Project Structure

```tree
.
├── LICENSE
├── Makefile
├── functions
│ ├── custom_sprintf.c
│ ├── custom_sscanf.c
│ ├── custom_string.c
│ └── custom_string_from_cs.c
├── include
│ ├── custom_sscanf.h
│ └── custom_string.h
├── test.txt
└── tests
├── custom_test_sscanf.c
└── custom_test_string.c
```

## Installation and Usage

To use the `string.h-Implementation` library:

1. Clone the repository.
2. Build the library using the provided Makefile:
   ```bash
   make all
   ```
3. Include the [custom_string.h](include/custom_string.h) or [custom_sscanf.h](include/custom_sscanf.h) header files in your project.
4. Link against the custom_string.a static library when compiling your application.

## Example usage:

```c
#include "custom_string.h"

int main() {
    char str1[50] = "Hello, World!";
    char str2[50];
    
    custom_strcpy(str2, str1);
    printf("Copied string: %s\n", str2);
    
    // Other string manipulations...
    return 0;
}
```

## Building and Testing

* To compile the library and tests:
    ```bash
    make all
    ```
* To run unit tests:
    ```bash
    make tests
    ```
* To generate a coverage report:
    ```bash
    make gcov_report
    ```

Check out the [Makefile](Makefile) for build instructions.

## Contributing

Contributions to improve string.h-Implementation are welcome. Please feel free to fork the project, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for more details.