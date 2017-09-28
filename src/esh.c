/*
 * esh - the 'pluggable' shell.
 *
 * Developed by Godmar Back for CS 3214 Fall 2009
 * Virginia Tech.
 */
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

#include "esh.h"

static void
usage(char *progname)
{
    printf("Usage: %s -h\n"
        " -h            print this help\n"
        " -p  plugindir directory from which to load plug-ins\n",
        progname);

    exit(EXIT_SUCCESS);
}

/* Build a prompt by assembling fragments from loaded plugins that 
 * implement 'make_prompt.'
 *
 * This function demonstrates how to iterate over all loaded plugins.
 */
static char *
build_prompt_from_plugins(void)
{
    char *prompt = NULL;
    struct list_elem * e = list_begin(&esh_plugin_list);

    for (; e != list_end(&esh_plugin_list); e = list_next(e)) {
        struct esh_plugin *plugin = list_entry(e, struct esh_plugin, elem);

        if (plugin->make_prompt == NULL)
            continue;

        /* append prompt fragment created by plug-in */
        char * p = plugin->make_prompt();
        if (prompt == NULL) {
            prompt = p;
        } else {
            prompt = realloc(prompt, strlen(prompt) + strlen(p) + 1);
            strcat(prompt, p);
            free(p);
        }
    }

    /* default prompt */
    if (prompt == NULL)
        prompt = strdup("esh> ");

    return prompt;
}

/* The shell object plugins use.
 * Some methods are set to defaults.
 */
struct esh_shell shell =
{
    .build_prompt = build_prompt_from_plugins,
    .readline = readline,       /* GNU readline(3) */ 
    .parse_command_line = esh_parse_command_line /* Default parser */
};

int
main(int ac, char *av[])
{
    int opt;
    list_init(&esh_plugin_list);

    /* Process command-line arguments. See getopt(3) */
    while ((opt = getopt(ac, av, "hp:")) > 0) {
        switch (opt) {
        case 'h':
            usage(av[0]);
            break;

        case 'p':
            esh_plugin_load_from_directory(optarg);
            break;
        }
    }

    esh_plugin_initialize(&shell);

    /* Read/eval loop. */
    for (;;) {
        /* Do not output a prompt unless shell's stdin is a terminal */
        char * prompt = isatty(0) ? shell.build_prompt() : NULL;
        char * cmdline = shell.readline(prompt);
        free (prompt);

        if (cmdline == NULL)  /* User typed EOF */
            break;

        struct esh_command_line * cline = shell.parse_command_line(cmdline);
        free (cmdline);
        if (cline == NULL)                  /* Error in command line */
            continue;

        if (list_empty(&cline->pipes)) {    /* User hit enter */
            esh_command_line_free(cline);
            continue;
        }

        esh_command_line_execute(cline);
        esh_command_line_free(cline);
    }
    return 0;
}

void esh_command_line_execute(struck esh_command_line *cmdline) {

	struct list_elem *e = list_begin(&cmdline->pipes);

	for(; e != list_end (&cmdline->pipes); e= list_next (e)) {

		struct esh_pipeline *pipe = list_entry(e, struct esh_pipeline, elem);

		esh_pipeline_execute(pipe);
	}

}

void esh_pipeline_execute(struct esh_pipeline *pipe) {

	int i = 1;
	struct list_elem * e = list_begin (&pipe->commands);

	int pipe_ends1[2];
	if (pipe(pipe_ends1) < 0)
		perror("pipe"), exit(-1);

	int pipe_ends2[2];
	if (pipe(pipe_ends2) < 0)
		perror("pipe"), exit(-1);

	int pid = fork();
	if (pid < 0)
		perror("fork"), exit(-1);
	
	if(pid == 0) {

		printf("Starting: %s\n", list_entry(e, struct esh_command, elem);

		if (e == list_end (&pipe->commands) { //holds one command

			dup2(pipe_ends1[1], 1);
			close(pipe_ends1[1]);
			close(pipe_ends1[0]);
			close(pipe_ends2[0]);
			close(pipe_ends2[1]);
		}
		else { //holds more than one command
			dup2(pipe_ends1[1], 1);
			close(pipe_ends1[1]);
			dup2(pipe_ends2[0], 0);
			close(pipe_ends1[0]);
			close(pipe_ends2[0]);
			close(pipe_ends2[1]);
		}

		char* arry[2] = {list_entry(e, struct esh_command, elem), NULL};

		execvp(list_entry(e, struct esh_command, elem), arry);

	}
	else {
	
		for (; e != list_end (&pipe->commands); e = list_next (e)) {
	
			if(pid != 0) {
				pid = fork();
				if (pid < 0)
					perror("fork"), exit(0);
			}

			if(pid == 0) {
	
	                        printf("Starting: %s\n", argv[2]);
	
				dup2(pipe_ends1[0], 0);
				close(pipe_ends1[0]);
				dup2(pipe_ends2[1], 1);
				close(pipe_ends1[1]);
				close(pipe_ends2[0]);
				close(pipe_ends2[1]);
		
				execvp(list _entry(e, struct esh_command, elem), argv);
			}
		}
		if (pid != 0) {

			close(pipe_ends1[0]);
			close(pipe_ends1[1]);
			close(pipe_ends2[0]);
			close(pipe_ends2[1]);
			wait(NULL);
			wait(NULL);
		}

		exit(0);
	}



}
