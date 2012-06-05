#include "Parser.h"
#include "List.h"

//TODO replace all perror calls with throws.

Parser::Parser(istream * istream)
{
	ifs = istream;
}

Parser::~Parser()
{
	delete token;
}

void Parser::parse(List* use_list)
{
	list = use_list;
	parseList();
}

void Parser::getToken()
{
	delete token;
	token = nextToken(*ifs);
}

bool Parser::more()
{
	std::cout << "#" << std::flush;

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
	//list is already created
	currentPipe = list->addPipeline();
	currentCommand = NULL;
	parsePipeline();

	//nextpipeline
	if(token->getType() == Token::SEQUENCE)
	{
		getToken();
		parseList();
	}
}

void Parser::parsePipeline()
{
	parseCommand();

	//nextcommand
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
		currentCommand = currentPipe->addCommand(token->getText());
		getToken();
	}
	else
	{
		perror("parse error on command");
	}
	//<argument>
	parseArgument();

}

void Parser::parseArgument()
{
	if(token->getType() == Token::WORD)
	{
		//do something with token
		currentCommand->addArg(token->getText());
		getToken();
	}
	else if(token->getType() == Token::INPUT)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
			currentCommand->addInput(token->getText());
			getToken();
		}
		else
		{
			perror("parse error on input");
		}
	}
	else if(token->getType() == Token::OUTPUT)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
			currentCommand->addOutput(token->getText());
			getToken();
		}
		else
		{
			perror("parse error on output");
		}
	}
	else if(token->getType() == Token::APPEND)
	{
		getToken();
		if(token->getType() == Token::WORD)
		{
			//do something with token
			currentCommand->addAppend(token->getText());
			getToken();
		}
		else
		{
			perror("parse error on append");
		}
	}

	//<nextargument>
	if(token->getType() == Token::WORD 
			|| token->getType() == Token::INPUT 
			|| token->getType() == Token::OUTPUT 
			|| token->getType() == Token::APPEND)
	{
		parseArgument();
	}
}
