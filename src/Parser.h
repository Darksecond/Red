#ifndef __PARSER_H__
#define __PARSER_H__

#include "Token.h"

#include <iostream>

class Parser {
	Token * token;
	istream * ifs;
	void getToken();

	public:
	Parser();
	~Parser();
	//vector<Pipe*> parse(istream & ifs);
};

#endif //_PARSER_H__
