Tests
=====

Of course a project would not be complete without some testing. 
These tests were performed on version 2faa0ece1ccd670161f96826aa7d699e71c92a22

Simple commands
---------------

```sh
echo Hello, World!
```
Expected output: 'Hello, World!'
Received output: 'Hello, world!'
Test passed.

 * * * 

```sh
ls
```
Expected output: 'Makefile README.md doc red src'
Received output: 'Makefile README.md doc red src'
Output may vary on your system.
Test passed.

Piped commands
--------------

```sh
cat README.md | grep logout
```
Expected output:
```
 * Support for exit and logout commands.
 * The 'exit' or 'logout' command can only be used as the first command in a pipe.
 * Support for exit and logout commands to exit.
```
Received output:
```
 * Support for exit and logout commands.
 * The 'exit' or 'logout' command can only be used as the first command in a pipe.
 * Support for exit and logout commands to exit.
```
Test passed.

Redirectors
-----------

```sh
head -n 5 < README.md
```
Expected output:
```
Red Shell
=========

School assignment to create a unix-like shell. 

```
Received output:
```
Red Shell
=========

School assignment to create a unix-like shell. 

```
Test passed.

 * * *

```sh
cat Makefile > tempfile
```
Expected result: a new file exists with the contents of 'Makefile', a second run of this command should provide the same contents.
Received result: a new file exists with the contents of 'Makefile', a second run of this command provides the same contents.
Test passed.

 * * *

```sh
cat Makefile >> tepmfile
```
Expected result: the file 'tempfile' will contain the contents of 'Makefile', and it will not overwrite any existing data.
Received result: the file 'tempfile' will contain the contents of 'Makefile', and it will not overwrite any existing data.
Test passeed.

Special commands
----------------

```sh
exit
```
Expected result: shell quits
Received result: shell quits
Test passed.

 * * *

```sh
logout
```
Expected result: shell quits
Received result: shell quits
Test passed.

Sequences
---------

...
