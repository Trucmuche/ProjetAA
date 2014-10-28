#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chaine(char *t)
{
    int i ;
    char car;
    i=0;
    do
        {
        car=getchar(); //getchar , code asci de ce qui est prit au clavier
        t[i]=car; //peut placer directement t[i]=getchar ....
        i++;
        }
    while(car!='\n'); //.... remplacer car par t[i-1]
    t[i-1]='\0'; // Pour degager le \n
}

//Partie a 2eme point , on met dans un tableau ajuster
char *saisie()
{
    int taille ;
    char *d , tmp[100];
    chaine(tmp);//A
    taille=strlen(tmp)+1;//B
    d=(char*)malloc(taille*sizeof(char));
    strcpy(d,tmp);
    return d;
}

int main()
{
    char *s;
    s = saisie();
    printf("%s",s);
}
