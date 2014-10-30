#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud
{
    char valeur;
    struct noeud *gauche;
    struct noeud *droite;
} noeud ;

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
    //Test si avant le egal, on a lettre
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

    //Test si après le egal, on a soit des caractères de calculs, soit des nombres
    i=taille2+1;
    printf("%d\n",taille2);

    do
    {
        printf("%d\n",i);
        printf("caractere : %c\n",t[i]);

        if ((t[i] != '+') || (t[i] != '-') || (t[i] != '*') || (t[i] != '(') || (t[i] != ')') || (t[i] <= 47) || (t[i] >= 58)) //Si t n'est ni un nombre, ni une parenthèse, ni un *, ni un +, ni un -
        {
            printf("ERREUR : Caractère non autorisé trouvé après le signe =. Veuillez rééssayer.\n");
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
            printf("Erreur : pas de signe égal ==> Pas une équation. Veuillez réessayer.\n");
        if (t == 2)
            printf("ERREUR : Caractère non accepté trouvé devant = : Veuillez n'utilisez que des lettres de l'alphabet (a..z) pour caractériser votre équation.\n");
        chaine(tmp);
    }
    taille=strlen(tmp)+1;//B
    d=(char*)malloc(taille*sizeof(char));
    strcpy(d,tmp);
    return d;
}

noeud *creerArbre(char *t)
{
    noeud *s = malloc(sizeof(noeud));
    int i=0,taille=0, taille2=0;
    taille=strlen(t);

    s->valeur = t[0];
    s->gauche = NULL;
    s->droite = NULL;

    do
    {
       // printf("caractere : %c\n",t[i]);
       printf("Yolo\n");

        if ((t[i] == '+') || (t[i] == '-') || (t[i] == '*')) //Si t n'est ni un nombre, ni une parenthèse, ni un *, ni un +, ni un -
        {
            ajouterNoeud(s,t[i],0);
            ajouterNoeud(s,t[i-1],1);
            ajouterNoeud(s,t[i+1],0);
        }
        i++;
    }while (i< taille);


    i=0;
    do
    {
        i++;
        taille2++;
    }while (i<= taille); // compte le nombre de caractere avant le =

    return s;
}

void ajouterNoeud(noeud **arbre, char valeur, int dir)
{
    noeud *noeudfct;
    noeud *arbrefct = *arbre;

    noeud *elem = malloc(sizeof(noeud));
    elem->valeur = valeur;
    elem->gauche = NULL;
    elem->droite = NULL;
    printf("Valeur de l'element ajouté %d\n", elem->valeur);

    if (dir == 0)
    {
        if(arbrefct)
        do
        {
            noeudfct = arbrefct;
            arbrefct = arbrefct->droite;
            if(!arbrefct)
            {
                noeudfct->droite = elem;
            }
        }while(arbrefct);
    }
    else if (dir == 1)
    {
        if(arbrefct)
        do
        {
            noeudfct = arbrefct;
            arbrefct = arbrefct->droite;
            if(!arbrefct)
            {
                noeudfct->gauche = elem;
            }
        }while(arbrefct);
    }
}

void affichageEquation(noeud *arbre)
{
    printf("Wow\n");
    if(arbre == NULL)
        exit(1);
    else if ((arbre->valeur == '+') || (arbre->valeur == '-') || (arbre->valeur == '*'))
    {
        affichageEquation(arbre->gauche);
        printf("%c",arbre->valeur);
        affichageEquation(arbre->droite);
    }
    else
        printf("%c",arbre->valeur);
}

int main()
{
    char *s;
    noeud *arbre = NULL;

    s = "A=1+2";
    arbre = creerArbre(s);
    affichageEquation(s);


    printf("Fin %s\n",s);
}
