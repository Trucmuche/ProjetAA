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
    int i=2,taille=0,nbPOuv=0,nbP=0,tolerance=0; // i initialisé à 2 pour sauté le =
    taille=strlen(t);

    s->valeur = t[0]; // implicitement, le caractère est transformé en Code ASCII
    s->oper = '=';  // permet de dire que nous sommes bien dans le premier élement pour la fonction d'affichage
    s->gauche = NULL;
    s->droite = NULL;

    //maintenant on doit en fonction des parenthèse établir une hierarchie
    //Utilisation d'une variable de tolérance, permettant de refaire des test de aractères tant que le nombre de parenthèse tolérée <= nombre de parenthèse dans la fonction
    while (tolerance <= nbP)
    {
        while (i<= taille)
        {
            //gestion du nombre de parenthèse
            if (t[i] == '(')
            {
                nbPOuv++;
                nbP++;
            }

            if ((t[i] == ')') && (nbPOuv != 0)) // même si ça ne devrait jamais arriver, simple sécurité
                nbPOuv--;

            if (((t[i] == '+') || (t[i] == '-') || (t[i] == '*')) && (nbPOuv == tolerance))  //Si t est soit +, soit -, soit * et qu'en plus, le nombre de parenthèse ouverte est identique au nombre de parenthèse tolérée
            {
                printf("Caractère entrant : %c\n",t[i]);
                printf("dafuk?\n");
                ajouterNoeud(s,t[i],0);
                printf("dafuka?\n");
                //On ajoute à la suite les caractères précedants et suivant celui traité uniquement si on a pas de parenthése aant et après l'opérateur
                if ((estTuUnChiffre(t[i-1])) && (estTuUnChiffre(t[i+1])))
                {
                //Ne pas oublier de faire une conversion en nombre à 2 digits si on le doit
                    if (estTuUnChiffre(t[i-2]))
                        ajouterNoeud(s,nombre(t[i-2],t[i-1]),1);
                    else
                        ajouterNoeud(s,t[i-1],1);

                    if (estTuUnChiffre(t[i+2]))
                        ajouterNoeud(s,nombre(t[i+1],t[i+2]),0);
                    else
                        ajouterNoeud(s,t[i+1],0);
                }
            }
            i++;
        }
        //reinitialisation des paramètres
        tolerance++;
        i=2;
    }while (tolerance <= nbP);

    return s;
}

void ajouterNoeud(noeud **arbre, char valeur, int dir)
{
    noeud *noeudfct;
    noeud *arbrefct = *arbre;

    noeud *elem = malloc(sizeof(noeud));
    //Définition de l'élement que l'on ajoute
    if (estTuUnChiffre(valeur))
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
    printf("Hey\n");
    noeudfct = arbrefct;
    printf("Hey\n");
    //Maintenant, si c'est le premier élement de calcul de l'équation, il viendra forcément se placer à droite, et on aura forcément NULL
    if (arbrefct != NULL && arbrefct->droite == NULL)
    {
        printf("Premier élement\n");
        noeudfct->droite = elem;
        return;
    }
    printf("Yolo\n");
    //sinon, pas de sortie de fonction, on peut sauter cet élement
    //On saute le premier element (car forcement NULL a gauche et ne doit pas bouger)
    arbrefct = arbrefct->droite;
    //Duplication de la case mémoire pour test
    noeudfct = arbrefct;

    //Maintenant, tou se placera en fonction de la position
    if (dir == 0)
    {
        if(arbrefct)
        while(arbrefct != NULL)
        {
            noeudfct = arbrefct;
            arbrefct = arbrefct->droite;
            printf("dafuk?\n");


        }while(arbrefct != NULL);
        noeudfct->droite = elem;
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
    printf("%s\n",s);
    arbre = creerArbre(s);
    //affichageEquation(s);


    printf("Fin %s\n",s);
}
