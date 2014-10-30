#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int testEquation(char *t)
{
    int taille, i=0,f=0,f2=0,taille2=0;
    taille=strlen(t);
    //Test du signe egal
    do
    {
        i++;
        if(t[i] == '=')
        {
            f = 1;
        }
    }while ((i<= taille) && (f == 0));

    if (f == 0)
    {
        return 1;
    }
    f=0;
    //Test si avant le egal, on a lettre et apr�s, on a nombre
    i=0;
    do
    {
        i++;
        taille2++;
    }while ((i<= taille) && (t[i] != '=')); // compte le nombre de caractere avant le =

    i=0;
    do
    {
        if (toupper(t[i]) < 65 || toupper(t[i]) > 90)
        {
            f = 1;
        }
        i++;
    }while ((i< taille2) && (t[i] != '='));

    if (f == 1)
        return 2;

    f=0;

    //Test si apr�s le egal, on a soit des caract�res de calculs, soit des nombres
    i=taille2+1;
    printf("%d\n",taille2);

    do
    {
        printf("%d\n",i);
        printf("caractere : %c\n",t[i]);

        if ((toupper(t[i]) <= 48 || toupper(t[i]) >= 57) || ((toupper(t[i]) <= 39 || (toupper(t[i]) == 45)) || (toupper(t[i]) != 44))) //Si t n'est ni un nombre, ni une parenth�se, ni un *, ni un +, ni un -
        {
            printf("ERREUR : Caract�re non autoris� trouv� apr�s le signe =. Veuillez r��ssayer.\n");
            return 3;
        }
        i++;
    }while (i< taille);


    return 0;
}

int conversionEntier(char car)
{
    return car-48;
}

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
    int t,taille ;
    char *d , tmp[100];
    chaine(tmp);//A
    while ((t=testEquation(tmp)) != 0)
    {
        if (t == 1)
            printf("Erreur : pas de signe �gal ==> Pas une �quation. Veuillez r�essayer.\n");
        if (t == 2)
            printf("ERREUR : Caract�re non accept� trouv� devant = : Veuillez n'utilisez que des lettres de l'alphabet (a..z) pour caract�riser votre �quation.\n");
        chaine(tmp);
    }
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
