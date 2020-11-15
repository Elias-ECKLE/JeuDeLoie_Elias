#include <stdio.h>
#include <stdlib.h>
#include <time.h> //on inclut une biblio pour utiliser la fct aléatoire (lancer de dé)

const int valeurMin_de=2;
const int valeurMax_de=12;
const int caseA_Atteindre=66;
const int caseTeteDeMort=58;
const int multipleCasesOie=9;
const int multipleOie_exception=63;
const char charAbandonPartie='o';



//prototypes____________________________________________________________________________________________
void AffichMessage(int);
int LancerDeDes(int,int,int);
int Somme(int,int);
int DeroulementPartie(int,int,int,int,int,int);
char ChoixAbandonnerPartie();
int PartieEstFinie(int,int, int, char,char);





//main program _______________________________________________________________________________________________
int main()
{
    //init des var : prog principal--------------------------------------------------------------------------

    srand(time(0)); //init de la fct rand --> gère le choix aléatoire du chiffre lors du lancer de dé dans
    //dans la fct LancerDeDes
    int nbDe_1=0;
    int nbDe_2=0;
    int sommeDes=0;
    int placeJoueur=0;
    int etatDeLaPartie=0;
    char charEstAbandon='n';



    //instructions de début de jeu---------------------------------------------------------------------------
    AffichMessage(etatDeLaPartie);


    //instructions de jeu------------------------------------------------------------------------------------
    do{


            //on lance dans un premier tps les deux dés
        nbDe_1=LancerDeDes(1, valeurMin_de, valeurMax_de);
        nbDe_2=LancerDeDes(2, valeurMin_de, valeurMax_de);

            //on fait leur somme
        sommeDes=Somme(nbDe_1,nbDe_2);

            //on ajoute à placeJoueur la somme des dés, ce qui donne une nouvelle place (position)
            //et on regarde si cette position n'entre pas dans l'une des règles du jeu soit :
            //reculer si on se trouve au delà de la case 66
            //doubler le déplacement sur les cases oie
            //retour case 0 tête de mort
        placeJoueur=DeroulementPartie(placeJoueur,sommeDes, caseA_Atteindre,caseTeteDeMort,multipleCasesOie,multipleOie_exception);

            //on demande au joueur s'il veut arrêter la partie en cours ou non
        charEstAbandon= ChoixAbandonnerPartie();
        etatDeLaPartie=PartieEstFinie(etatDeLaPartie, placeJoueur, caseA_Atteindre, charEstAbandon, charAbandonPartie);



    }while((etatDeLaPartie!=1) && (etatDeLaPartie!=-1)); //on continue à faire tourner le jeu tant que le joueur ne gagne pas ou abandonne



    //instructions de fin de jeu-----------------------------------------------------------------------------

    AffichMessage(etatDeLaPartie);
    return 0;
}




//procedures___________________________________________________________________________________________


void AffichMessage(int choixMessage){
    //BUT :Afficher des feedbacks textuels au joueur (victoire, abandon, debut de jeu)
    //ENTREE:chiffre indiquant la nature du message --> 0 pour le debut de jeu/ 1 pour la victoire et -1 pour l'abandon
    //SORTIE: message texte

    switch(choixMessage)
    {
        case 0 :
        printf("Bienvenue dans le jeu de l oie. Il consiste a atteindre la case 66 du plateau\n");
        printf("Pour cela, vous devez lancer deux des et leur somme vous permettra d'avancer d'autant de case que vous avez de chiffres\n\n\n\n");
        break;

        case 1:
        printf("Feliciation, vous avez atteint la case 66. Vous avez gagne la partie\n");
        break;

        case -1:
        printf("Vous avez fait le choix d'abandonner la partie\n");
        break;
    }
}






//fonctions____________________________________________________________________________________________

int LancerDeDes(int lancerDe, int min, int max){
    //BUT:Obtenir un chiffre en lançant le dé
    //ENTREE:dé sélectionné : soit le premier soit le deuxième
    //SORTIE: chiffre du dé obtenu (par l'utilisation d'un random)

    int nbDe=1; //par défaut, le chiffre inscrit sur le dé est à 1

    if(lancerDe==1){
        printf("Veuillez appuyer sur entree pour lancer le premier de :");
        nbDe=(rand()%(max-min+1)) + min;//nb aléatoire entre 1 et 6
        getchar(); // touche entree
        printf("Le résultat du premier de est : %d\n\n",nbDe);
    }
    else if (lancerDe==2){
        printf("Veuillez appuyer sur entree pour lancer le deuxieme de :");
        nbDe=(rand()%(max-min+1)) + min;//nb aléatoire entre 1 et 6
        getchar(); //touche entree
        printf("Le résultat du deuxieme de est : %d\n\n\n\n",nbDe);
    }

    return nbDe;
}


int Somme(int nbDe_1, int nbDe_2){
    //BUT: Faire la somme des deux chiffres tirés avec les dés
    //ENTREE:deux chiffres
    //SORTIE:somme des deux chiffres

    int somme=0;

    somme= nbDe_1+nbDe_2;

    return somme;
}



int DeroulementPartie(int caseJoueurInit, int somme, int caseVictoire, int caseMort, int multiple, int multipleException){
    //BUT:
    //ENTREE:
    //SORTIE:

    int caseJoueur=caseJoueurInit;
        //on ajoute la somme des dés à la place du joueur où il se trouve
    caseJoueur=caseJoueur+somme;


//conséquences déplacement du joueur. En fct de la case qur laquelle il atterit, des règles s'appliquent :
    //si on dépasse 66, on recule de la différence entre la nouvelle case et 66, le tout à partir de la case sur laquelle on se trouve initialement
    if(caseJoueur>caseVictoire){

        printf("Vous avez depasse la case victoire du nombre de %d. ",caseVictoire);
        printf("Vous devez alors reculer de la difference entre votre nouvelle case, soit %d et celle voulue\n",caseJoueur);
        caseJoueur=caseJoueurInit-(caseJoueur-caseVictoire);
        printf("Ce qui revient a etre sur la case : %d\n\n\n",caseJoueur);
    }
    //oie toute les 9 cases sauf en 63
    else if((caseJoueur%multiple==0) && (caseJoueur!=multipleException)){

        printf("Votre nouvelle case est la case : %d. Il s'agit d'une case oie\n",caseJoueur);
        caseJoueur=caseJoueur+somme; //on ajoute encore une fois la somme vu que le déplacmeent double
        printf("Vous doublez alors votre déplacement ce qui revient a aller sur la case : %d\n\n",caseJoueur);
    }
    //tête de mort : case 58
    else if(caseJoueur==caseMort){

        printf("Pas de chance, vous etes tombe sur la case tete de mort soit %d\n",caseMort);
        caseJoueur=0;
        printf("Vous revenez alors a la case 0\n\n");
    }
    else{

        printf("Vous avez avance de %d cases. ",somme);
        printf("Ainsi vous vous retrouvez a la case %d\n\n",caseJoueur);
    }


    return caseJoueur;
}



char ChoixAbandonnerPartie(){
    //BUT: Demander au joueur de choisir un caractère pour savoir s'il veut poursuivre le jeu ou non
    //ENTREE: rien
    //SORTIE: caractère choisi

    char choix='n';

    printf("Voulez-vous abandonner la partie en cours ?: (o pour oui/n pour non)\n");
    scanf("%c",&choix);
    printf("\n\n");

    return choix;
}


int PartieEstFinie(int etatPartie, int caseJoueur, int caseVictoire, char charEstAbandon, char charAbandon){
    //BUT:Indiquer si la partie doit se poursuivre, est abandonnée ou que le joueur a gagné la partie
    //ENTREE: etatPartie initial, la case du joueur, la case à atteindre pour la victoire, le caractère choisi pour l'abandon de partie, le caractère d'abandon
    //SORTIE: nouveau etat de la partie

    //0 pour partie non finie
    //1 pour victoire partie
    //-1 pour abandon de la partie

    if(caseJoueur==caseVictoire){
        etatPartie=1;
    }
    else if(charEstAbandon==charAbandon){
        etatPartie=-1;
    }
    else{
        etatPartie=0;
    }

    return etatPartie;
}



