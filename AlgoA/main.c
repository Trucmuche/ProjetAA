#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud
{
    int valeur;
    char oper;
    struct noeud *gauche;
    struct noeud *droite;
} noeud ;

int conversionEntier(char car)
{
    return car-48;
}

noeud *creerArbre(char *t)
{
    noeud *s = malloc(sizeof(noeud));
    int i=0,taille=0, taille2=0;
    taille=strlen(t);

    s->valeur = conversionEntier(t[0]);
    s->oper = NULL;
    s->gauche = NULL;
    s->droite = NULL;

    do
    {
        if ((t[i] == '+') || (t[i] == '-') || (t[i] == '*')) //Si t est soit +, soit -, soit *
        {
            ajouterNoeud(s,t[i],0,1);
            ajouterNoeud(s,t[i-1],1,0);
            ajouterNoeud(s,t[i+1],0,0);
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

void ajouterNoeud(noeud **arbre, char valeur, int dir, int type)
{
    noeud *noeudfct;
    noeud *arbrefct = *arbre;

    noeud *elem = malloc(sizeof(noeud));
    if (type == 0)
    {
        elem->valeur = conversionEntier(valeur);
        elem->oper = NULL;
        elem->gauche = NULL;
        elem->droite = NULL;
    }
    else
    {
        elem->valeur = NULL;
        elem->oper = valeur;
        elem->gauche = NULL;
        elem->droite = NULL;
    }

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

void calculEquation(noeud ** arbre)
{
    noeud *noeudfct;
    noeud *arbrefct = *arbre;
    // On teste si on a bien que des nombres pour calculer
    noeudfct = arbrefct->gauche;
    if ((noeudfct->oper == '*') || (noeudfct->oper == '+') || (noeudfct->oper == '-'))
    {
        calculEquation(&noeudfct);
    }
    noeudfct = arbrefct->droite;
    if ((noeudfct->oper == '*') || (noeudfct->oper== '+') || (noeudfct->oper == '-'))
    {
        calculEquation(&noeudfct);
    }
    // Si on a bien que des nombres après chaque opérandes, on peut calculer
    if (arbrefct->oper == '*')
        arbrefct->valeur = (char)(arbrefct->gauche->valeur * arbrefct->droite->valeur);
    else if (arbrefct->oper == '+')
        arbrefct->valeur = (char)(arbrefct->gauche->valeur + arbrefct->droite->valeur);
    else if (arbrefct->oper == '-')
        arbrefct->valeur = (char)(arbrefct->gauche->valeur - arbrefct->droite->valeur);
    return 0;
}

void affichageEquation(noeud *arbre)
{
    if(arbre == NULL)
        return 0;
    else if ((arbre->oper == '+') || (arbre->oper == '-') || (arbre->oper == '*'))
    {
        affichageEquation(arbre->gauche);
        printf("%c",arbre->oper);
        affichageEquation(arbre->droite);
    }
    else
        printf("%d",arbre->valeur);
}

int main()
{
    char *s;
    noeud *arbre = NULL;

    s = "A=1+2";
    printf("%s",s);
    arbre = creerArbre(s);
    affichageEquation(s);


    printf("Fin %s\n",s);
}
