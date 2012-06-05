#ifndef __PARSER_H__
#define __PARSER_H__

#include "Token.h"
#include "List.h"
#include "Pipeline.h"
#include "Command.h"

#include <iostream>

class Parser {
	Token * token;
	istream * ifs;
	List* list;
	Pipeline* currentPipe;
	Command* currentCommand;

	void getToken();

	void parseList();
	void parsePipeline();
	void parseCommand();
	void parseArgument();

	public:
	Parser(istream* ifs);
	~Parser();
	void parse(List* uselist);
	bool more();
};

#endif //_PARSER_H__
