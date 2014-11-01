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

int nombre(int a, int b)
{
    return (a*10)+b;
}

int estTuUnChiffre(char car)
{
    if ((car == '+') || (car == '-') || (car == '*') || (car == '(') || (car == ')'))
        return 0;
    else
        return 1;
}

int estTuUnOperande(char car)
{
    if ((car == '+') || (car == '-') || (car == '*'))
        return 1;
    else
        return 0;
}

noeud *creerArbre(char *t)
{
    noeud *s = malloc(sizeof(noeud));
    int i=2,taille=0; // i initialisé à 2 pour sauté le =
    taille=strlen(t);

    s->valeur = t[0]; // implicitement, le caractère est transformé en Code ASCII
    s->oper = "=";  // permet de dire que nous sommes bien dans le premier élement pour la fonction d'affichage
    s->gauche = NULL;
    s->droite = NULL;

    do
    {
        if ((t[i] == '+') || (t[i] == '-') || (t[i] == '*'))  //Si t est soit +, soit -, soit *, soit
        {
            printf("dafuk?\n");
            ajouterNoeud(s,t[i],0,1);
            printf("dafuk?\n");
            //Ne pas oublier de faire une conversion en nombre à 2 digits si on le doit
            if (estTuUnChiffre(t[i-2]))
                ajouterNoeud(s,nombre(t[i-2],t[i-1]),1,0);
            else
                ajouterNoeud(s,t[i-1],1,0);

            if (estTuUnChiffre(t[i+2]))
                ajouterNoeud(s,nombre(t[i+1],t[i+2]),0,0);
            else
                ajouterNoeud(s,t[i+1],0,0);
        }
        i++;
    }while (i<= taille);

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
    // On teste si on a bien que des nombres pour calculer sinon, on redescend d'un niveau pour effectuer l'operation plus bas
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
    {
        arbrefct->valeur = arbrefct->gauche->valeur * arbrefct->droite->valeur;
        arbrefct->oper = NULL;
    }
    else if (arbrefct->oper == '+')
    {
        arbrefct->valeur = arbrefct->gauche->valeur + arbrefct->droite->valeur;
        arbrefct->oper = NULL;
    }
    else if (arbrefct->oper == '-')
    {
        arbrefct->valeur = arbrefct->gauche->valeur - arbrefct->droite->valeur;
        arbrefct->oper = NULL;
    }
}

void affichageEquation(noeud *arbre)
{
    noeud *noeudfct;
    noeud *arbrefct = arbre;
    noeudfct = arbrefct;

    if(noeudfct == NULL)
        return;
    else if (estTuUnOperande(noeudfct->oper) == 0)//Ne tombre içi que si on est au début, avant le égal
    {
        printf("%c%c",noeudfct->valeur,noeudfct->oper);
        affichageEquation(arbrefct->droite);
    }
    else if((arbre->oper == '+') || (arbre->oper == '-') || (arbre->oper == '*'))
    {
        noeudfct = arbrefct->gauche; //positionnement à gauche

        if (estTuUnOperande(noeudfct->oper)) //on va verifier si on a un operande sur la gauche et si c'est le cas, on ouvre une parenthése et on affiche recursivement
        {
            printf("(");
            affichageEquation(noeudfct);
            printf(")");
        }

        noeudfct = arbrefct->droite;

        if (estTuUnOperande(noeudfct->oper)) //même verification sur la droite
        {
            printf("(");
            affichageEquation(noeudfct);
            printf(")");
        }

        //enfin, on peut afficher l'operation

        printf("%d%c%d",arbre->gauche,arbre->oper,arbre->droite->valeur);
    }
}

int main()
{
    char *s;
    noeud *arbre = NULL;

    s = "A=1+2";
    printf("%s",s);
    arbre = creerArbre(s);
    //affichageEquation(s);


    printf("Fin %s\n",s);
}
