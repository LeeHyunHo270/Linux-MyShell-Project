#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include "common.h"

////////////////////////////////////////////////////////////////////////
//  디렉토리를 변경하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_cd(int ac, char *av[])
{
	char *path;

	// 인자가 있을 경우 path를 설정
	if(ac > 1)
	{
		path = av[1];

	}
	
	// 인자가 없을 경우 HOME디렉토리를 설정
	//디렉토리 이름 불러올떄 기본설정이 home이므로 getenv를 사용하여 path에 "HOME" 디렉토리로 설정
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		// 환경 변수가 없을 경우 현재 디렉토리로 설정
		path = ".";
	}
	
	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "%s: bad directory.\n", path);
	}

}

////////////////////////////////////////////////////////////////////////
//  프로그램을 종료
////////////////////////////////////////////////////////////////////////
void cmd_exit()
{
	exit(1);
}

////////////////////////////////////////////////////////////////////////
//  파일 권한 변경
////////////////////////////////////////////////////////////////////////
void cmd_chmod(int ac, char **av)
{
	if (ac != 3)
	{
		fprintf(stderr, "usage: %s [file name]\n", av[0]);
		return 1;
	}
	if (access(av[1], F_OK) != 0)
	{
		printf("%s is not existed\n", av[1]);
		return 1;
	}
	if (chmod(av[1], atoi(av[2])) != 0)
	{
		printf("fail change mode\n");
	}
	else
	{
		printf("success change mode\n");
	}

}

////////////////////////////////////////////////////////////////////////
//  디렉토리 리스트를 출력하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_ls(int ac, char *av[])
{

	DIR *dp;//구조체 변수 포인터
	struct dirent *entry; //구조체 포인터
	char *path='.'; // 자기자신
	int count;

	// 인자가 없을 경우 자기 자신의 디렉토리로 설정한다.
	if(ac < 2)
	{
		path = ".";
	}
	
	// 디렉토리를 연다.(자기자신)
	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "Can't open directory: %s", av[1]);
		return;
	}


	count = 0;


	while((entry = readdir(dp)) != NULL)
	{
		if(entry->d_name[0] == '.')
		{
			continue;
		}

		
		// 출력
		printf("%s\t", entry->d_name);

		// 한줄에 3개씩 출력한다.
	
			if(count > 3)
			{
				printf("\n");
				count = 0;
			}
			else
			{
				count++;
			}

	}

	// 디렉토리를 닫는다.
	closedir(dp);
	printf("\n");
}

////////////////////////////////////////////////////////////////////////
//  파일을 복사하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_cp(int ac, char *av[])
{
	FILE *src;
	FILE *dst;
	char ch;

	// 인자가 2개 이하일 경우 에러
	if(ac < 3)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	// 복사할 소스 파일을 연다.
	if((src = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[1]);
		return;
	}

	// 쓰기를 할 파일을 연다.
	if((dst = fopen(av[2], "w")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[2]);
		return;
	}

	// 복사
	while(!feof(src))
	{
		ch = (char) fgetc(src);

		if(ch != EOF)
		{
			fputc((int)ch, dst);
		}
	}

	fclose(src);
	fclose(dst);
}

////////////////////////////////////////////////////////////////////////
//  파일 삭제 명령 함수
////////////////////////////////////////////////////////////////////////
void cmd_rm(int ac, char *av[])
{
	// 인자가 없을 경우 에러
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	// 파일 삭제
	unlink(av[1]);

}

////////////////////////////////////////////////////////////////////////
//  디렉토리를 생성하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_mkdir(int ac, char *av[])
{
	// 인자가 없을 경우 에러
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	// 디렉토리를 생성한다.
	if(mkdir(av[1], 0755))
	{
		fprintf(stderr, "Make directory failed.\n");
	}
}


////////////////////////////////////////////////////////////////////////
//  cat 명령어 함수
////////////////////////////////////////////////////////////////////////
void cmd_cat(int ac, char *av[])
{
	int ch;
	FILE *fp;


	// 인자가 없을 경우 에러처리
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments");
		return;
	}

	// 일기전용으로 파일을 연다.
	if((fp = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "No such file on directory.\n");
		return;
	}

	// 내용 출력
	// 파일 스트림을 인자로 받는 getc를 이용하여 한 문자씩 파일이 끝날 때 까지 ch에 저장 
	while((ch = getc(fp)) != EOF)
	{
		putchar(ch);
	}

	fclose(fp);
}

void cmd_ln(int ac, char* av[]) {
	
	
	if ((link(av[1], av[2])) < 0) {
		printf("%s", av[0]);
		perror("error creating hard link");
		exit(1);
	}
	
	printf("hard link created\n");
}

////////////////////////////////////////////////////////////////////////
//  pwd 버퍼 멜로케이션으로 해볼 것 g혹시 안되면 cd 뒷부분 살릴것
////////////////////////////////////////////////////////////////////////
void cmd_pwd(int ac, char* av[])
{
	char buff[1024];
	getcwd(buff, 1024);
	printf("%s\n", buff);
}


void cmd_stat(int argc, char *argv[])

{ 
	struct stat sb;

	
	if (argc !=2){
		fprintf(stderr, "Usage : %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(lstat(argv[1], &sb)==-1){
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	printf("ID of containing device: [%lx, %lx])\n",(long) major(sb.st_dev),(long) minor(sb.st_dev));

	printf("File type:");
	
	switch (sb.st_mode & S_IFMT){
	case S_IFBLK: printf("block device\n");	break;
	case S_IFCHR: printf("character device\n");	break;
	case S_IFDIR: printf("directory\n");	break;
	case S_IFIFO: printf("FIFO/PIPE\n");	break;
	case S_IFLNK: printf("symlink\n");	break;
	case S_IFREG: printf("socket\n");	break;
	case S_IFSOCK: printf("socket\n");	break;
	default:	printf("unknown?\n");	break;
	}
	
	printf("I-node number:	%ld\n", (long) sb.st_ino);	
	
	printf("Mode:%lo(octal)\n", (unsigned long) sb.st_mode);
	printf("Link count:%ld\n", (long) sb.st_nlink);
	printf("Ownership:	UID=%ld	GID=%ld\n", (long) sb.st_uid, (long)sb.st_gid);
	printf("Preferred I/O block size:%ld byte\n", (long) sb.st_blksize);
	printf("File size:%lld bytes\n", (long long) sb.st_size);
	printf("Blocks alllocated:%lld\n", (long long) sb.st_blocks);
	
	printf("Last status change:	%s", ctime(&sb.st_ctime));
	printf("Last file access:	%s", ctime(&sb.st_atime));
	printf("Last file modification:	%s", ctime(&sb.st_mtime));
	
	
}
