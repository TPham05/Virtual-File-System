# 📁 Virtual File System (VFS) – Custom Shell in C

This project is a fully functional **Virtual File System** written in C, simulating basic file system operations like creating directories, managing files, and navigating through a custom-built directory tree. It provides a command-line interface similar to a UNIX shell and is designed to help you learn about memory structures, shell logic, and recursive design.

---

## 🧠 Features

- 📂 **Directory & File Management**  
  Create (`mkdir`, `touch`), delete (`rm`, `rmdir`), rename, and organize files and directories.

- 🧑‍💻 **Custom Shell Interface**  
  Simple and intuitive shell loop that accepts VFS commands and provides immediate feedback.

- 🌳 **Recursive Tree Structure**  
  Internally stores the file system as a recursive tree to support nested directories and file lookup.

- 💾 **Save & Load System State**  
  Use `save` and `load` to persist the virtual file system between sessions.

- 📄 **File Reading & Writing**  
  Supports basic file content operations like `write` and `cat` to read text.

---

## ⚙️ Technologies Used

- **C (C11)** – Core programming language  
- **Standard Libraries** – `stdio.h`, `stdlib.h`, `string.h`  
- **Custom Header** – `vfs.h` for declarations and type definitions

---

## 📟 Supported Commands

| Command               | Description                                      |
|------------------------|--------------------------------------------------|
| `mkdir <dir>`          | Create a new directory                          |
| `touch <file>`         | Create a new empty file                         |
| `ls`                   | List contents of the current directory          |
| `cd <dir>`             | Change the current directory                    |
| `pwd`                  | Show the full path of the current directory     |
| `cat <file>`           | Display contents of a file                      |
| `write <file> <text>`  | Overwrite a file with new content               |
| `rm <file>`            | Delete a file                                   |
| `rmdir <dir>`          | Delete an empty directory                       |
| `rename <old> <new>`   | Rename a file or directory                      |
| `tree`                 | Display the full directory structure visually   |
| `cp <src> <dest>`      | Copy a file or directory                        |
| `mv <src> <dest>`      | Move or rename a file/directory to a new path   |
| `save <file>`          | Save the entire VFS state to disk               |
| `load <file>`          | Load a saved VFS state from disk                |
| `exit`                 | Exit the VFS shell                              |

