#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>

#include "Pipeline.h"

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
	for( std::vector<Command*>::const_iterator it = commands.begin(); it != commands.end(); ++it)
	{
		delete *it;
	}
}

Command* Pipeline::addCommand(std::string word)
{
	Command * cmd = new Command(word);
	commands.push_back(cmd);
	return cmd;
}

void Pipeline::execute()
{
	
	if(commands.size() == 0)
	{
		return;
	}

	//the command is 'exit' or 'logout' so exit
	//POSSIBLETODO: abstract this to a seperate 'ExitCommand' or something, this would allow for arguments
	if(commands.front()->isExit())
	{
		exit(0);
	}

	int pid = fork();
	if(pid == 0)
	{
		//child (C)
		int input[2] = {-1, -1};
		int output[2] = {-1, -1};
		for( std::vector<Command*>::reverse_iterator it = commands.rbegin(); it != commands.rend(); ++it)
		{
			//prepare pipes
			if(*it != commands.front())
			{
				pipe(input);
			}

			int child_pid = -1;
			if(*it != commands.front())
			{
				child_pid = fork();
			}

			if(child_pid == 0)
			{
				//child (B)
				//'swap' pipes
				output[0] = input[0];
				output[1] = input[1];
				input[0] = -1;
			}
			else
			{
				if(input[0] != -1)
				{
					(*it)->setInputFd(input[0]);
					close(input[1]);
				}
				if(output[0] != -1)
				{
					(*it)->setOutputFd(output[1]);
					close(output[0]);
				}
				(*it)->execute();
				//we only reach here if the command is bad
				throw "command is bad";
				exit(-1);
			}
		}
		exit(0);
	}
	else
	{
		//parent (shell)
		int status;
		waitpid(pid, &status, 0);
	}
}
