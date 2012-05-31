This is the BNF the parser will be based upon.


```BNF
<list> ::= <pipeline> <nextpipeline>
<nextpipeline> ::= e | SEQUENCE <list>
<pipeline> ::= <simplecommand> <nextcommand>
<nextcommand> ::= e | PIPE <pipeline>
<simplecommand> ::= WORD <argument> <nextargument>
<nextargument> ::= e | <argument>
<argument> ::= WORD | <io>
<io> = INPUT WORD | OUTPUT WORD | APPEND WORD
```
