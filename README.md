Red Shell
=========

School assignment to create a unix-like shell. 

Compiling
---------

By default the Makefile is configured to use clang++ as it's compiler and linker. If you don't have LLVM installed, you can change it to use g++ as it's compiler and linker.

Running
-------

The resulting binary is located in the top-level directory of the project folder. You can execute the binary by prefixing it with './'.

Features
--------

The Red Shell supports multiple features, many of which are reminiscent of more commonly used shells like bash or zsh.

Some of it's features are:
 * Support for pipes (|)
 * Support for multiple command sequences on a single line (;)
 * Support for input redirection (<)
 * Support for output redirection (>)
 * Support for output redirection in append mode (>>)
