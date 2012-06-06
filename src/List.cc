#include "List.h"
#include "Pipeline.h"

#include <iostream>

List::List()
{
}

List::~List()
{
	for( std::vector<Pipeline*>::const_iterator it = pipes.begin(); it != pipes.end(); ++it)
	{
		delete *it;
	}
}

Pipeline* List::addPipeline()
{
	Pipeline * pipe = new Pipeline();
	pipes.push_back(pipe);
	return pipe;
}

void List::execute()
{
	for( std::vector<Pipeline*>::const_iterator it = pipes.begin(); it != pipes.end(); ++it)
	{
		(*it)->execute();
		delete *it;
	}
	pipes.clear();
}
