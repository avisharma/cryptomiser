#include <stdio.h>
int main()
{
    int i,j,n,m;
    char c;
    for(m=0;m=1;m++){
        for (i=8;i<=15;i++) {
            char s[16]="";
            for(j=1;j<=i;j++) {
                n = rand() % 26;
                c = (char)(n+97);
                s[j-1]=c;
            }
            printf("%s\n",s);
        }
    }
    return 0;
}
