# 🐚 Mini Shell (Linux Internals Project)

## 📌 Overview

Mini Shell is a simplified Linux command-line interpreter implemented in
C as part of a Linux Internals project.\
This project demonstrates core operating system concepts including
process creation, system calls, signal handling, inter-process
communication (IPC), and shell behavior.

The implementation is inspired by Linux shell fundamentals and follows
the project requirements specified by Emertxe Linux Internals
curriculum.

------------------------------------------------------------------------

## 🎯 Project Objectives

-   Implement a functional mini shell using **system calls**
-   Execute external commands using **fork() and exec()**
-   Handle **signals** such as SIGINT and SIGTSTP
-   Support **built-in commands**
-   Implement **special shell variables**
-   Provide **N-pipe IPC support**
-   Understand process lifecycle and foreground/background execution

------------------------------------------------------------------------

## 🛠 Technologies Used

-   C Programming Language
-   Linux System Calls
-   Process Management APIs
-   Signal Handling
-   File Handling
-   IPC (Pipes)

------------------------------------------------------------------------

## 🖥 Features

### 1️⃣ Customizable Prompt

Default prompt:

    minishell$

Change prompt using:

    PS1=NEW_PROMPT

⚠ Whitespace around '=' is not allowed:

    PS1 = NEW_PROMPT   → Treated as normal command (command not found)

------------------------------------------------------------------------

### 2️⃣ External Command Execution

-   Creates child process using `fork()`
-   Executes using `execvp()`
-   Parent waits using `wait()`
-   Displays prompt only after child finishes

Supported commands: - ls - pwd - mkdir - rmdir - sleep - date - Any
executable file

------------------------------------------------------------------------

### 3️⃣ Built-in Commands

These commands are handled internally (without fork):

-   `exit` → Terminates minishell
-   `cd` → Change directory
-   `pwd` → Print working directory

------------------------------------------------------------------------

### 4️⃣ Special Variables

  Variable   Description
  ---------- --------------------------------------
  `$?`       Exit status of last executed command
  `$$`       PID of minishell
  `$SHELL`   Full path of minishell executable

Examples:

    echo $$
    echo $?
    echo $SHELL

------------------------------------------------------------------------

### 5️⃣ Signal Handling

#### Ctrl+C (SIGINT)

-   If foreground process running → Send SIGINT to child
-   If no foreground process → Redisplay prompt

#### Ctrl+Z (SIGTSTP)

-   Stops foreground process
-   Displays child PID
-   Enables job control

------------------------------------------------------------------------

### 6️⃣ Job Control

-   `jobs` → List stopped jobs
-   `fg` → Resume job in foreground
-   `bg` → Resume job in background

------------------------------------------------------------------------

### 7️⃣ IPC -- N Pipes

Supports multiple pipe commands:

    ls | wc
    ls | grep txt | wc

Implemented using: - `pipe()` - `dup2()` - Multiple `fork()` calls

------------------------------------------------------------------------

## 🧠 Concepts Demonstrated

-   Process creation and hierarchy
-   Foreground and background execution
-   Exit status management
-   Signal propagation
-   File descriptor manipulation
-   Inter-process communication
-   Environment variable handling

------------------------------------------------------------------------

## 📂 Project Structure

    Minishell/
    │
    ├── main.c
    ├── scan_input.c
    ├── commands.c
    ├── handler.c
    ├── extr_external_cmds.c
    ├── header.h
    ├── ext_cmds.txt
    └── check_cd_cmd/

------------------------------------------------------------------------

## 🔄 Execution Flow

1.  Display prompt
2.  Read user input
3.  Parse command
4.  Check built-in or external
5.  Execute accordingly
6.  Handle signals
7.  Update exit status
8.  Redisplay prompt

------------------------------------------------------------------------

## 🚀 How to Compile

    gcc *.c -o minishell

## ▶ How to Run

    ./minishell

------------------------------------------------------------------------

## 📚 Learning Outcomes

This project strengthens understanding of:

-   How Linux shells work internally
-   Interaction between user space and kernel
-   Process control mechanisms
-   Signal-driven programming
-   IPC implementation

------------------------------------------------------------------------

## 🏁 Conclusion

Mini Shell is a foundational systems programming project that
demonstrates practical knowledge of Linux internals and operating system
concepts. It simulates real shell behavior while providing deep insights
into process management and signal handling.

------------------------------------------------------------------------

## 👨‍💻 Author

Siddharth Gaikwad
B.Tech – Electronics & Communication Engineering
Aspiring Embedded Software Engineer

Linux Internals Project
📌 Strong focus on C, Operating system, and System-level programming

------------------------------------------------------------------------

## 📚 References
Emertxe – Linux Internals Mini Shell Project Specification
Official project requirement document and slides provided as part of the Linux Internals curriculum.
