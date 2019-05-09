#include<stdio.h>

int main(void)
{
    char buf[256];
    int i;
    int nc = 0, lc = 0, bc = 0, ec = 0;
 
    printf("insert: ");
    gets(buf);
 
    for (i = 0; buf[i]; i++)//buf[i]가 참인 문자면 반복
    {
        if ((buf[i] >= '0') && (buf[i] <= '9'))//숫자일 때
        {
            nc++;
        }
        else if ((buf[i] >= 'a') && (buf[i] <= 'z'))//소문자일 때
        {
            lc++;
        }
        else if ((buf[i] >= 'A') && (buf[i] <= 'Z'))//대문자일 때
        {
            bc++;
        }
        else//다른 문자일 때
        {
            ec++;
        }
    }
    printf("number: %dea s: %dea L: %dea etc: %dea\n", nc, lc, bc, ec);
    return 0;
}

