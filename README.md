# Minishell  

---
## Collaboration

👉🏻 This project was created together with [DitaBisko](https://github.com/DitaBisko). 

---
**Minishell** is a simple, functional shell implementation inspired by Bash.

Minishell is a lightweight shell program that provides an interactive interface for executing commands, managing environment variables, handling some signals, and implementing shell features such as redirections and pipes.

![](https://github.com/owrmille/minishell/blob/main/demo/example.gif)

---

## Overview  
Minishell supports the following features:    

1. **Command Execution**  
   - Searches and executes commands based on the `PATH` variable, or using relative or absolute paths.  

3. **Command History**  
   - Maintains a working history of entered commands.  

4. **Redirections**  
   - `<` redirects input from a file.  
   - `>` redirects output to a file.  
   - `<<` reads input until a given delimiter is encountered (here-document).  
   - `>>` appends output to a file.  

5. **Pipes**  
   - Implements pipelines where the output of one command is passed as input to the next using the `|` operator.
   - Handles pipes in the end of the command line (e.g. `ls |`).

6. **Environment Variables**  
   - Supports expansion of environment variables using `$` syntax.  
   - Expands `$?` to the exit status of the most recently executed foreground command.  

7. **Shell Variables**
   - Supports expansion of shell variables using `$` syntax.  

9. **Signal Handling**  
   - Handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` like Bash:  
     - `Ctrl-C`: Displays a new prompt on a new line.  
     - `Ctrl-D`: Exits the shell.  
     - `Ctrl-\`: Does nothing in interactive mode.  

10. **Built-in Commands**  
   - `echo`: Includes support for the `-n` option.  
   - `cd`: Changes the current directory (supports relative and absolute paths).  
   - `pwd`: Prints the current working directory.  
   - `export`: Sets environment variables.  
   - `unset`: Unsets environment variables.  
   - `env`: Prints the environment variables.  
   - `exit`: Exits the shell.  

11. **Quoting**  
   - Handles single quotes (`'`) to disable interpretation of meta-characters.  
   - Handles double quotes (`"`) to partially disable interpretation of meta-characters, except for `$`.
   - Handles unclosed quotes of both types.

--------------
## Getting Started

### Build the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/owrmille/minishell.git
   ```
2. Compile the program using `make`:
   ```bash
   make
   ```

### Run the Program

Run the program:
```bash
./minishell
```

### Command Syntax  
- Commands can be entered with standard syntax, including support for pipes (`|`) and redirections (`>`, `<`, `>>`, `<<`).  
- Environment and shell variables can be referenced using `$`.  

### Examples  
- Simple command execution:  
  ```bash  
  ls -l  
  ```  
- Using pipes:  
  ```bash  
  ls | grep minishell  
  ```  
- Using redirections:  
  ```bash  
  echo "Hello, world!" > output.txt  
  cat < output.txt  
  ```  
---

## Notes  
- Memory leaks caused by the `readline` library are expected and not required to be fixed.
