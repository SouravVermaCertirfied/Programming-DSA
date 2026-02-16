#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<stdio.h>

/* Brute */
bool isMatched(char *p, char *s){
    int plen = strlen(p);
    int slen = strlen(s);

    if(p==NULL  || s==NULL || slen < plen )
        return false;
    
    bool matched = true;
    for(int i=0; i<=(slen-plen); i++){
        matched = true;
        for(int j=0; j<plen; j++){
            if(s[i+j]!=p[j]){
                matched = false;
                break;
            }
        }
        if(matched)
            return true;
    }
    return false;
}

int main(){
    char s[] = "abcdabc";
    char p[] = "abc";
    printf(" %b ", isMatched(p, s));
    getch();
}