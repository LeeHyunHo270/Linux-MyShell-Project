#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

////////////////////////////////////////////////////////////////////////
//  명령어를 파싱한다.
////////////////////////////////////////////////////////////////////////
SYMBOL parse(int *waitpid)
{
	//심볼은 헤더파일에서 정의되어 있고 symbol로 symbol.c 자세하게 분석해서 term 리턴 심볼 정리 해야됨!!!!
	SYMBOL symbol, term;
	int argc, sourcefd, destfd;
	int pid;
	char *argv[MAXARG+1], sourcefile[MAXFNAME];
	char destfile[MAXFNAME];
	//단어로 입력 받음 심볼에서
	char word[MAXWORD];
	BOOLEAN append;

	argc = 0;			
	sourcefd = 0;		
	destfd = 1;			

	
	while (TRUE) 
	{
		// 하나의 단어씩을 분석한다.
		switch (symbol = getsymbol(word))		
		{
			// 일반 문자일 경우
			case S_WORD :	
				//인자 갯수 헤더에 정의되어 있으니 많이 쓰지마라
				if(argc == MAXARG) 
				{
					//오류문
					fprintf(stderr, "Too many args.\n");
					break;
				}

				// 입력받은 값으로 메모리를 동적 할당함
				// 새로운 인자 배열을 메모리 할당 한다.
				argv[argc] = (char *) malloc(strlen(word)+1);
				
				// 패스
				if(argv[argc] == NULL) 
				{
					fprintf(stderr, "Out of arg memory.\n");
					break;
				}


				// 명령어 복사
				// word로 한 단어씩 저장된 값을 배열에 저장
				strcpy(argv[argc], word);
				

				// arg 카운터 증가
				argc++;
				continue;

			// &, ;, 줄바꿈 문자일 경우 - 하나의 명령어 단위
			case S_AMP  :
			case S_SEMI :
			case S_NL   :
			
				//명령어나 파일이름이 아니므로 넣지 않는다 - 엔터는 명령어에 필요치 않기 떄문에
				argv[argc] = NULL;
				// 입력받은 symbol을 term으로 넘겨서 그 term을 excute로 넘겨서 명령어를 실행
				term = symbol;
				
				
				// 명령을 수행한다.
				pid = execute(argc, argv, sourcefd, sourcefile,
								destfd, destfile,append, term == S_AMP);
				

				
				//*waitpid = pid;
			
				// 인자값을 없을 경우
				if (argc == 0 && (symbol != S_NL || sourcefd > 1))

				{
					fprintf(stderr, "Missing command.\n");
				}

				// 인자로 입력된 값들의 메모리 해제
				while (--argc >= 0)
				{
					free(argv[argc]);
				}

				return term;

			// 명령이 잘못되었을 경우 종료
			//case S_EOF : 
				//exit(0);
		} 
	}    
}

