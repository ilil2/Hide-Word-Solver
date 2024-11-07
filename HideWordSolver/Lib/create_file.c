#include "lib.h"
#include <unistd.h>
#include <err.h>
#include <wait.h>

char create_file(char* path)
{
	int pid = fork();
	if (pid)
	{
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
	else
	{
		char* filepath[] = {"touch", path, NULL};
		return execvp("touch", filepath);
		err(1, "execvp()");
	}
}
