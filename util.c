#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

////////////////////////////////////////////////////////////////////////
//  치명적인 오류 처리
////////////////////////////////////////////////////////////////////////
void fatal(char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(1);
}

////////////////////////////////////////////////////////////////////////
//  일반 에러 처리
////////////////////////////////////////////////////////////////////////
void syserr(char *message)
{
	fprintf(stderr, "Error: %s (%d", message, errno);
	exit(1);
}

////////////////////////////////////////////////////////////////////////
//  부모가 자식의 실행이 끝나길 기다리는 함수
////////////////////////////////////////////////////////////////////////
void waitfor(int pid)
{
	int wpid, status;
	// minish에서 받은 pid가 wait상태가 아니고 , error 상태가 아닐 때
	// wait를 이용하여 프로세스를 기다린다.

	while ((wpid = wait(&status)) != pid && wpid != ERROR);
}

////////////////////////////////////////////////////////////////////////
//  프롬프트를 출력한다.
////////////////////////////////////////////////////////////////////////
void print_prompt()
{

		printf(">> ");
}

////////////////////////////////////////////////////////////////////////
//  사용자 정의 명령을 처리하는 함수
////////////////////////////////////////////////////////////////////////
BOOLEAN shellcmd(int ac, char *av[])
{
	char *path;

	// cd
	if(!strcmp(av[0], "cd"))
	{
		cmd_cd(ac, av);
	}
	// ls
	else if(!strcmp(av[0], "ls"))
	{
		cmd_ls(ac, av);
	}
	// cp
	else if(!strcmp(av[0], "cp"))
	{
		cmd_cp(ac, av);
	}
	// rm
	else if(!strcmp(av[0], "rm"))
	{
		cmd_rm(ac, av);
	}
	// mkdir
	else if(!strcmp(av[0], "mkdir"))
	{
		cmd_mkdir(ac, av);
	}

	// cat
	else if(!strcmp(av[0], "cat"))
	{
		cmd_cat(ac, av);
	}
	// exit
	else if(!strcmp(av[0], "exit"))
	{
		cmd_exit();
	}
	// chmod
	else if (!strcmp(av[0], "chmod"))
	{
		cmd_chmod(ac, av);
	}
	// ln
	else if (!strcmp(av[0], "ln"))
	{
		cmd_ln(ac, av);
	}

	// pwd
	else if (!strcmp(av[0], "pwd"))
	{
		cmd_pwd(ac, av);
	}
	// stat
	else if (!strcmp(av[0], "stat"))
	{
	
		cmd_stat(ac, av);
	}
	else
	{
		return FALSE;
	}


	return TRUE;
}

