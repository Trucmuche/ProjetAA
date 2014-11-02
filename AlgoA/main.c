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

    if ((car == '+') || (car == '-') || (car == '*') || (car == '(') || (car == ')') || (car == '=') || (car == '\0'))
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
    int i=2,taille=0,nbPOuv=0,nbP=0,tolerance=0, p=1; // i initialis� � 2 pour saut� le =
    taille=strlen(t);

    s->valeur = t[0]; // implicitement, le caract�re est transform� en Code ASCII
    s->oper = '=';  // permet de dire que nous sommes bien dans le premier �lement pour la fonction d'affichage
    s->gauche = NULL;
    s->droite = NULL;

    //maintenant on doit en fonction des parenth�se �tablir une hierarchie
    //Utilisation d'une variable de tol�rance, permettant de refaire des test de aract�res tant que le nombre de parenth�se tol�r�e <= nombre de parenth�se dans la fonction
    while (tolerance <= nbP)
    {
        while (i<= taille)
        {
            //gestion du nombre de parenth�se
            if (t[i] == '(')
            {
                nbPOuv++;
                printf("Parenth�se rencontr�e?\n");
                if (p == 1)
                    nbP++;
            }

            if ((t[i] == ')') && (nbPOuv != 0)) // m�me si �a ne devrait jamais arriver, simple s�curit�
                nbPOuv--;
            printf("On teste le caract�re %c\n",t[i]);
            if (((t[i] == '+') || (t[i] == '-') || (t[i] == '*')) && (nbPOuv == tolerance))  //Si t est soit +, soit -, soit * et qu'en plus, le nombre de parenth�se ouverte est identique au nombre de parenth�se tol�r�e
            {
                printf("Caract�re entrant : %c\n",t[i]);
                ajouterNoeud(&s,t[i],NULL,0);
                printf("TEst des caractere aant apr�s\n");
                //On ajoute � la suite les caract�res pr�cedants et suivant celui trait� uniquement si on a pas de parenth�se aant et apr�s l'op�rateur

                //Ne pas oublier de faire une conversion en nombre � 2 digits si on le doit
                if (estTuUnChiffre(t[i-1]))
                {
                    if (estTuUnChiffre(t[i-2]))
                        ajouterNoeud(&s,NULL,nombre(conversionEntier(t[i-2]),conversionEntier(t[i-1])),1);
                    else
                        ajouterNoeud(&s,NULL,conversionEntier(t[i-1]),1);
                }
                if (estTuUnChiffre(t[i+1]))
                {
                    if (estTuUnChiffre(t[i+2]))
                        ajouterNoeud(&s,NULL,nombre(conversionEntier(t[i+1]),conversionEntier(t[i+2])),0);
                    else
                        ajouterNoeud(&s,NULL,conversionEntier(t[i+1]),0);
                }
            }
            i++;
        }
        //reinitialisation des param�tres
        tolerance++;
        i=2;
        p=0; //le nombre de parenth�ses ouvrante sera ainsi bloqu�
    }while (tolerance <= nbP);

    return s;
}
void ajoutNoeudPlusLoin(noeud **arbre, noeud **elem)
{
    noeud *noeudfct;
    noeud *arbrefct = *arbre;

    noeudfct = arbrefct->gauche;

    //Maintenant, tout se placera en fonction de la position
    if (arbrefct->oper == NULL)
        return;

    if (noeudfct == NULL)
    {
        arbrefct->gauche = elem;
        return;
    }

    noeudfct = arbrefct->droite;

    if (noeudfct == NULL)
    {
        arbrefct->droite = elem;
        return;
    }

    if(arbrefct->gauche != NULL)
    {
        ajoutNoeudPlusLoin(&arbrefct->gauche, &elem);
        return;
    }
    if(arbrefct->droite != NULL)
    {
        ajoutNoeudPlusLoin(&arbrefct->droite, &elem);
        return;
    }
}

void ajouterNoeud(noeud **arbre, char valeur, int nb, int dir)
{
    printf("Entr�e dans la fonction ajout� noeud du caract�re %c et nombre %d\n",valeur,nb);
    noeud *noeudfct;
    noeud *arbrefct = *arbre;

    noeud *elem = malloc(sizeof(noeud));

    //D�finition de l'�lement que l'on ajoute
    if (valeur == NULL)
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
    noeudfct = arbrefct;
    //Maintenant, si c'est le premier �lement de calcul de l'�quation, il viendra forc�ment se placer � droite, et on aura forc�ment NULL
    if ((arbrefct != NULL) && (arbrefct->droite == NULL))
    {
        noeudfct->droite = elem;
        return;
    }
    printf("Pas le premier element !\n");
    //sinon, pas de sortie de fonction, on peut sauter cet �lement
    //maintenant, on ajoute au plus loin d�squ'on peut
    ajoutNoeudPlusLoin(&arbrefct, &elem);


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
    // Si on a bien que des nombres apr�s chaque op�randes, on peut calculer
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
    else if (estTuUnOperande(noeudfct->oper) == 0)//Ne tombre i�i que si on est au d�but, avant le �gal
    {
        printf("%c%c",noeudfct->valeur,noeudfct->oper);
        affichageEquation(arbrefct->droite);
    }
    else if((arbre->oper == '+') || (arbre->oper == '-') || (arbre->oper == '*'))
    {
        noeudfct = arbrefct->gauche; //positionnement � gauche

        if (estTuUnOperande(noeudfct->oper)) //on va verifier si on a un operande sur la gauche et si c'est le cas, on ouvre une parenth�se et on affiche recursivement
        {
            printf("(");
            affichageEquation(noeudfct);
            printf(")");
        }

        noeudfct = arbrefct->droite;

        if (estTuUnOperande(noeudfct->oper)) //m�me verification sur la droite
        {
            printf("(");
            affichageEquation(noeudfct);
            printf(")");
        }

        //enfin, on peut afficher l'operation

        printf("%d%c%d",arbre->gauche->valeur,arbre->oper,arbre->droite->valeur);
    }
}

int main()
{
    char *s;
    noeud *arbre = NULL;

    s = "J=1+2";
    printf("%s\n",s);
    arbre = creerArbre(s);
    affichageEquation(arbre);
    printf("\n");


    printf("Fin %s\n",s);
}
