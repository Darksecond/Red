#include <string>
#include <fcntl.h>
#include <iostream>

#include "Command.h"

Command::Command(std::string word)
{
	name = word;
	fd[0] = -1; //input
	fd[1] = -1; //output
}

Command::~Command()
{
}

bool Command::isExit()
{
	return name == "exit" || name == "logout";
}

void Command::print()
{
	std::string arg_string = "";
	for( std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		arg_string += *it;
	}
	std::cout << name << " arguments: " << arg_string 
		<< " output: " << output 
		<< " input: " << input
		<< "\n" << std::flush;
}

void Command::execute()
{
	//determine not-yet-set fd's
	prepareFd();
	dup2(fd[0], 0); //input
	dup2(fd[1], 1); //output
	
	char **argv = new char*[args.size() + 2];
	argv[0] = const_cast<char *>(name.c_str()); //first argument is the command itself
	argv[args.size() + 1] = NULL; //null terminated array
	for(unsigned int i = 1; i <= args.size(); i++)
		argv[i] = (char*)args[i-1].c_str(); //add argument to argv array

	execvp(argv[0], argv);

	perror("could not execute command");
}

void Command::setInputFd(int input)
{
	fd[0] = input;
}

void Command::setOutputFd(int output)
{
	fd[1] = output;
}

void Command::addArg(std::string word)
{
	args.push_back(word);
}

void Command::addInput(std::string word)
{
	input = word;
}

void Command::addOutput(std::string word) 
{
	output = word;
}

void Command::addAppend(std::string word)
{
	append = word;
}

void Command::prepareFd()
{
	if(fd[0] == -1)
	{
		if(!input.empty())
		{
			//input
			fd[0] = open(input.c_str(), O_RDONLY);
		} 
	}
	if(fd[1] == -1)
	{
		if(!append.empty())
		{
			//append
			fd[1] = open(append.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		}
		else if(!output.empty())
		{
			//output
			fd[1] = open(output.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		}
	}
}
