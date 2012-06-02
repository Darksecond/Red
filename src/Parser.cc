#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
	delete token;
}

void Parser::getToken()
{
	delete token;
	token = nextToken(*ifs);
}

bool Parser::more()
{
	getToken();
	if(token->getType() == Token::END)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Parser::parseList()
{
	if(token->getType() == Token::EOL)
	{
		//do nothing
		//TODO is deze wel nodig?
	}
	else
	{
		parsePipeline();
		
		//nextpipeline
		getToken();
		if(token->getType() == Token::SEQUENCE)
		{
			getToken();
			parseList();
		}
	}
}

void Parser::parsePipeline()
{
	parseCommand();

	//nextcommand
	getToken();
	if(token->getType() == Token::PIPE)
	{
		getToken();
		parsePipeline();
	}
}

void Parser::parseCommand()
{
	//WORD
	if(token->getType() == Token::WORD)
	{
		//do something with token
	}
	else
	{
		//throw "parse error"
	}
	//<argument>
	getToken();
	parseArgument();

	//<nextargument>
	getToken();
	if(token->getType() == Token::WORD)
	{
		getToken();
		parseArgument();
	}
}

void Parser::parseArgument()
{
	if(token->getType() == Token::WORD)
	{
		//do something with token
	}
	else if(token->getType() == Token::INPUT)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
		}
		else
		{
			//throw "parse error"
		}
	}
	else if(token->getType() == Token::OUTPUT)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
		}
		else
		{
			//throw "parse error"
		}
	}
	else if(token->getType() == Token::APPEND)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
		}
		else
		{
			//throw "parse error"
		}
	}
}
