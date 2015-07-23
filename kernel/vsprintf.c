
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                              vsprintf.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "string.h"

/*
 *  为更好地理解此函数的原理，可参考 printf 的注释部分。
 */

/*======================================================================*
                                vsprintf
 *======================================================================*/
int vsprintf(char *buf, const char *fmt, va_list args)
{
	char*	p;
	char	tmp[256];
	va_list	p_next_arg = args;

	for (p=buf;*fmt;fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;
			continue;
		}

		fmt++;

		switch (*fmt)
		{
		case 's':
			{
				strcpy(p, *(char **)(p_next_arg));
				int iStrLen = strlen(*(char **)(p_next_arg));
				p[iStrLen]=0;
				p += iStrLen;
				p_next_arg += 4;
				break;
			}
		case 'c':
			*p++ = *p_next_arg;
			p_next_arg += 4;
			break;

		default:
			if (*fmt>='0'&&*fmt<='9')
			{
				//先把显示多少个探清楚。
				int itotal=0;
				int itempnum;
				int i;
				int iStrLen;
				for (i=0;*fmt>='0'&&*fmt<='9';i++,fmt++)
				{
					//_atoi(&(*fmt),itempnum);
					itempnum=*fmt-48;
					itotal=itotal*10+itempnum;
				}
				itotal=itotal%20;
				
				if (*fmt=='c')
				{
					for (i=0;i<itotal-1;i++)
					{
						*p=' ';
						p++;
					}
					*p++ = *p_next_arg;
					p_next_arg += 4;
				}
				else if (*fmt =='s')
				{
					strcpy(p, *(char **)(p_next_arg));
					iStrLen = strlen(*(char **)(p_next_arg));
					if (iStrLen<itotal)
					{
						for (i=0;i<itotal-iStrLen;i++)
						{
							*p=' ';
							p++;
						}
					}
					p[iStrLen]=0;
					p += iStrLen;
					p_next_arg += 4;
				}
			}
			break;
		}
	}
	return (p - buf);
}

