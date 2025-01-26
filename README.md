# minishell

# Minishell

Minishell is a project that aims to create a simplified version of a Unix shell. This project provides hands-on experience with system programming concepts and shell functionality.

## Key Features

- Command execution based on PATH or absolute paths
- Built-in commands: echo, cd, pwd, export, unset, env, and exit
- Input/output redirections (<, >, <<, >>)
- Pipes (|) for command chaining
- Environment variable expansion
- Signal handling (ctrl-C, ctrl-D, ctrl-$$
- Command history

## Technical Aspects

- Lexical analysis and parsing of user input
- Process creation and management
- File descriptor manipulation
- Signal handling
- Environment variable management
- String manipulation and memory management in C

## Usage

Compile the project and run the executable:

```bash
make
./minishell
```

Once inside the shell, you can use it like a standard Unix shell, executing commands and utilizing built-in functionalities.

## Skills Developed

- Advanced C programming
- Unix system calls and library functions
- Process management and inter-process communication
- Shell scripting and command interpretation
- Error handling and signal management

Minishell provides a deep dive into the inner workings of shell programs, enhancing understanding of Unix-like operating systems and system-level programming.
