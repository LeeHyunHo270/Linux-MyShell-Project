#include <stdio.h>
#include "common.h"

typedef enum {NEUTRAL, INQUOTE, INWORD} STATUS;

////////////////////////////////////////////////////////////////////////
//  문자열을 분석하며 심볼을 찾는 함수
////////////////////////////////////////////////////////////////////////
SYMBOL getsymbol(char *word)
{
	STATUS state;
	int c;
	char *w;
	
	state = NEUTRAL;
	w = word;

	//EOF=CTRZ 이거 누르면 꺼짐
	while ((c = getchar()) != EOF) 
	{
	
		switch (state) 
		{

			case NEUTRAL :
				switch (c) 
				{
					//엔터키로 명령어를 입력할 때
					case '\n':
						return S_NL;

					//띄어쓰기나 탭키를 사용할 때
					case ' ' :
					case '\t':
						continue;


					case '"' :  //알리아스 할때 "" 문자열로 받아야함 
						state = INQUOTE;
						continue;


					default  : 
						state = INWORD;
						*w++ = c;
						continue;
				}


			case INQUOTE:
				switch (c) 
				{
					case '\\' : 
						*w++ = getchar();
						continue;

					case '"'  : 
						*w = '\0';
						return S_WORD;

					default   : 
						*w++ = c;
						continue;
				}

			case INWORD:
				switch (c ) 
				{
					case ';' :
					case '&' :
					case '|' :
					case '<' :
					case '>' :
					case '\n':
					case ' ' :
					case '\t': 
						ungetc(c, stdin);
						*w = '\0';
						return S_WORD;

					default  : 
						*w++ = c;
						continue;
				}
		}
	}

   return S_EOF;
}

