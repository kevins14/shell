#include "BuiltIn.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

static void jobs_execution(struct esh_pipeline *pipe);

void esh_built_in_commands(struct esh_pipeline *pipe) {

	struct list_elem * e = list_begin (&pipe->commands);

	for (; e != list_end (&pipe->commands); e = list_next (e)) {

		struct esh_command *cmd = list_entry(e, struct esh_command, elem);
		char **p = cmd->argv;

		if(strcmp(p[0], "exit") == 0) 
			exit(EXIT_SUCCESS);
		else if(strcmp(p[0], "jobs") == 0)
			jobs_execution(pipe);

		//implement needed
		esh_signal_block(SIGCHLD);

		if(strcmp(p[0], "fg") == 0) {

		}
		if(strcmp(p[0], "bg") == 0) {
	
		}
		if(strcmp(p[0], "kill") == 0) {
	
		}
		if(strcmp(p[0], "stop") == 0) {
	
		}
	
	}

}

static void jobs_execution(struct esh_pipeline *pipe) {

	struct list_elem * e = list_begin (jobslist);

	for (; e != list_end (jobslist); e = list_next (e)) {

		jobslist->

	}
	printf("[%d]	", pipe->jid);
		
	if(pipe->status == BACKGROUND)
		printf("%s			", "Running");
	else if(pipe->status == NEEDSTERMINAL)
		printf("%s			", "Stopped");
	int i = 0;
	for (; e != list_end (&pipe->commands); e = list_next (e)) {

		struct esh_command *cmd = list_entry(e, struct esh_command, elem);
		char **p = cmd->argv;
	
		printf("%s", p[i]);
		i++;
	}
	printf("\n");
}
