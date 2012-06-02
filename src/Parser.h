#ifndef __PARSER_H__
#define __PARSER_H__

#include "Token.h"

#include <iostream>

class Parser {
	Token * token;
	istream * ifs;
	void getToken();
	bool more();

	void parseList();
	void parsePipeline();
	void parseCommand();
	void parseArgument();

	public:
	Parser();
	~Parser();
	//vector<Pipe*> parse(istream & ifs);
};

#endif //_PARSER_H__
