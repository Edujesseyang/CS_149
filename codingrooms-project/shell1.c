#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 // max len of each command
#define MAXARGS 256	 // max args
int main()
{
	char buf[MAXLINE]; /* from apue.h */

	printf("%% "); /* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		size_t size = strlen(buf);
		if (size && buf[size - 1] == '\n')
		{
			buf[size - 1] = '\0'; /* replace newline with null */
		}

		char *argv[MAXARGS];			// a ptr array to store each argu ptr
		int argc = 0;					// counting argus
		char *tok = strtok(buf, " \t"); // ptr of the first letter of command
		while (tok && argc < MAXARGS - 1)
		{ // save all ptr of first char of each arg
			argv[argc++] = tok;
			tok = strtok(NULL, " \t");
		}

		argv[argc] = NULL; // set last element

		if (argc == 0)
		{ // if no arg, continue
			printf("%% ");
			continue;
		}

		if (strcmp(argv[0], "./countnames") == 0 && argc >= 2)
		{ // check if it is countnames
			int children = 0;
			for (int i = 1; i < argc; i++)
			{ // fork each argu
				pid_t pid = fork(); // dup proc
				if (pid < 0)
				{ // fork error
					perror("fork error");
					exit(1);
				}

				if (pid == 0)
				{ // child
					char *args[] = {"./countnames", argv[i], NULL};
					execvp(args[0], args);
					perror("execvp");
					_exit(127);
				}
				children++;
			}

			while (children-- > 0) 
			{ // wait() each child
				if (wait(NULL) < 0)
				{ // is wait error
					perror("Wait error");
					break;
				}
			}
		}
		else
		{ // other command
			pid_t pid = fork();
			if (pid < 0)
			{
				perror("fork error");
				exit(1);
			}

			if (pid == 0)
			{
				execvp(argv[0], argv);
				perror("exec error");
				_exit(127);
			}
			waitpid(pid, NULL, 0);
		}
		printf("%% ");
	}

	return 0;
}
