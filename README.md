# get_next_line

## Overview
`get_next_line` is a C program that reads a line from a file descriptor, typically used for reading input line-by-line from files or standard input. The project consists of three main files: `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h`. This project provides a robust implementation of reading lines until the end of the file is reached, using dynamic memory allocation and efficient buffer management.

---

## Repository
GitHub: [ft_get_next_line](https://github.com/Raainshe/ft_get_next_line.git)

---

## Files
- **`get_next_line.c`**: The main logic of reading lines from a file descriptor.
- **`get_next_line_utils.c`**: Contains utility functions used by the main `get_next_line` logic.
- **`get_next_line.h`**: Header file containing the function prototypes and necessary includes.

---

## Compilation
To compile the project, use the provided `Makefile`.

Run the following command to compile the code:
```bash
make
```

This will generate the `get_next_line.o` and `get_next_line_utils.o` object files and link them into a final executable.
To clean up the compiled files, you can use:
```bash
make clean
```

## Example Usage
```c
int main(void) {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

## Authors
Developed by Ryan Makoni

## License
This project is licensed under the MIT License. Feel free to use and modify it.
