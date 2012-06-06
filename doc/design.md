Design
======

Of course there was some design involved in creating the shell. 

Main code flow
--------------

1. Parser parses input stream.
2. Resulting data structure is executed.
3. Goto 1 while we have not received any signals to stop.

Class Design
------------

This classes were designed to be fairly standalone and were all based on the BNF and parser. The following classes are implemented:

* Command
* List
* Pipeline
* Parser

List, Pipeline and Command implement the bulk of the program.
