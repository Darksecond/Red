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
 * Support for ^D to quickly exit.
 * Support for exit and logout commands to exit.

Examples
--------

Here are some examples listed to get you started using the Red Shell.

```sh
echo Hello, World!
```
This example will print out 'Hello, World!' by running the 'echo' command.

```sh
cat < README.md | grep exit | less
```
In this example the 'cat' program will be called with the 'README.md' file as it's input redirector. The output will be piped to 'grep' with 'exit' as it's argument. Next the output of grep will be piped to 'less' which will display it on the screen.
The output should be as following:
```
 * Support for ^D to quickly exit.
 * Support for exit and logout commands to exit.
```

More Documentation
-------------

You can find more documentation in the 'doc' directory. Amongst the files found there is the BNF used to develop the parser used.
