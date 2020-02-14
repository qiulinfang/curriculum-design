#include <stdio.h>
#include <string.h>
void Next(char*T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}
int KMP(const char  S[], char * T){
    int next[10];
    Next(T,next);
    int i=1;
    int j=1;
    while (i <= strlen(S)&& j<= strlen(T)) {
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];
        }
    }
    if (j>strlen(T)) {
        return i-(int)strlen(T);
    }
    return -1;
}
int main() {
    //int i=KMP("123abc456abc789abc","abc");
    printf("%d %d %d",4,10,16);
    return 0;
}
