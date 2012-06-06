#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"
#include "List.h"

void do_signals();
void sig_handler(int,siginfo_t *siginfo, void*);

void do_signals()
{
	struct sigaction act;
	 
	memset (&act, '\0', sizeof(act)); // null out act struct, easier than setting every parameter to 0
		 
	/* Use the sa_sigaction field because the handles has two additional parameters */
	act.sa_sigaction = &sig_handler;
		 
	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, &act, NULL) < 0) {
		perror ("sigaction");
	}
}

void sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	if(sig == SIGQUIT)
	{
		exit(0);
	}
}

int main(int argc, char * argv[])
{
	do_signals();
	Parser* p = new Parser(&std::cin);
	while(p->more())
	{
		List* list = new List();

		try
		{
			p->parse(list);
			list->execute();
		}
		catch(const std::string& s)
		{
			std::cerr << s << "\n" << std::flush;
		}
		catch(const char* s)
		{
			std::cerr << s << "\n" << std::flush;
		}

		delete list;
	}
	return 0;
}
