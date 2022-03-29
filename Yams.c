/**
 * @file Yams.c
 * @author Maxime Boujeant
 * @brief Documentation doxygen du fichier Yams.c
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief définition de la taille N d'un tableau
 */
# define N 14
/**
 * @brief type tableau d'un tableau de N entier
 * 
 */
typedef int score[N];

/**
 * @brief définition de la taille D d'un tableau
 */
# define D 5
/**
 * @brief type tableau d'un tableau de D entier
 * 
 */
typedef int de[D];

/**
 * @brief constante pour la Borne max de la cellule bonus
 * 
 */
const int BONUS = 62;

/**
 * @brief constante pour le score de la cellule bonus
 * 
 */
const int PTS_BONUS = 35;

/**
 * @brief costante pour le score du full house
 * 
 */
const int FULL_HOUSE = 25;

/**
 * @brief constante pour le score de la petite suite
 * 
 */
const int PETITE_SUITE = 30;

/**
 * @brief constante pour le score de la grande suite
 * 
 */
const int GRANDE_SUITE = 40;

/**
 * @brief constante pour le score du YAMS
 * 
 */
const int YAMS = 50;

/**
 * @brief constante pour le nombre d'essaie max
 * 
 */
const int MAX = 3;

/**
 * @brief constante pour le nombre de tour max d'une partie de YAMS
 * 
 */
const int TOUR_MAX = 13;

/**
 * @brief constante pour la première partie de la grille des scores
 * 
 */
const int BORNE = 7; 

/**
 * @brief constante pour le nombre maximal de dés
 * 
 */
const int MAX_DE = 5;

char proposeLanceDe(char[7]);

void fpseudo(char[7]);
void afficheGrille(char[7],char[7],int[],int[]);
void init_TabJ(int[]);
void init_TabD(int[]);
void pLanceDe(int[],int[]);
void afficheMenu(int *);
void pChoisirDe(int[],int[]); 
void triSelection(int[]);
void affecterScore(char[7],int[],int[]);
void afficherScore(char[7],char[7],int[],int[]);

/**
 * @brief fonction qui demande à l'utilisateur s'il souhaite lancer les dés
 * 
 * @param[in] pseudo pseudo du joueur courant 
 * @return char 
 */
char proposeLanceDe(char pseudo[7]){ // demande à l'utilisateur s'il veut lancer les dés 
    char rep;
    printf("Voulez-vous lance les des %s ? (o/n)\n",pseudo);
    scanf(" %c",&rep);
    printf("\n");
    return rep;
}

/**
 * @brief Procédure qui demande la saisi du pseudo du joueur
 * 
 * @param[out] pseudo pseudo du joueur courant
 * 
 */
void fpseudo(char pseudo[7]){ 
    do{ // boucle répéter si le pseudo dépasse
        printf("Veuillez saisir un pseudo\n");
        scanf("%s",pseudo);
        printf("\n");
    } while (strlen(pseudo)>=7); // vérification de la longueur
}

/**
 * @brief Procédure qui affiche la feuille de mark de la partie
 * 
 * @param[in] pseudo1 pseudo du joueur 1
 * @param[in] pseudo2 pseudo du joueur 2
 * @param[in] j1 tableau des scores du joueur 1
 * @param[in] j2 tableau des scores du joueur 2
 */
void afficheGrille(char pseudo1[7],char pseudo2[7],score j1,score j2){ // affiche la grille de jeu
    int somme1J1=0,somme1J2=0; // variable des sommes de la première partie de la grille
    int somme2J1=0,somme2J2=0; // variable des sommes de la secondes partie de la grille
    int somme3J1=0,somme3J2=0; // variable des sommes de toute la grille
    int i;    

    for (i = 0; i < 7; i++){ // boucle qui fait la somme des éléments de la première partie de la grille 
        if (j1[i]!=-1 && j2[i]!=-1){ // vérification que les 2 cellules des tableaux des joeuurs ne soit pas blocké
            somme1J1= somme1J1 + j1[i]; 
            somme1J2= somme1J2 + j2[i];
        }else if (j1[i]==-1 && j2[i]!=-1){ // vérification que la cellule du joueur 1 soit blocké
            somme1J2= somme1J2 + j2[i];
        }else if (j1[i]!=-1 && j2[i]==-1){ // vérification que la cellule du joueur 2 soit blocké
            somme1J1= somme1J1 + j1[i]; 
        }
    }
    for (i = 7; i < N; i++){ // boucle qui fait la somme des éléments de la seconde partie de la grille
        if (j1[i]!=-1 && j2[i]!=-1){ // vérification que les 2 cellules des tableaux des joeuurs ne soit pas blocké
            somme2J1= somme2J1 + j1[i]; 
            somme2J2= somme2J2 + j2[i];
        }else if (j1[i]==-1 && j2[i]!=-1){ // vérification que la cellule du joueur 1 soit blocké
            somme2J2= somme2J2 + j2[i];
        }else if (j1[i]!=-1 && j2[i]==-1){ // vérification que la cellule du joueur 2 soit blocké
            somme2J1= somme2J1 + j1[i]; 
        }
    }
    somme3J1 = somme1J1 + somme2J1; // affectation de la variable somme total du joueur 1
    somme3J2 = somme1J2 + somme2J2; // affectation de la variable somme total du joueur 2

    // grille du yams
    printf(" ___________________________________\n");
    printf("|         Yams        |%6s|%6s|\n",pseudo1,pseudo2);
    printf("|_____________________|______|______|\n");
    printf("|1 [total de 1]       |%6d|%6d|\n",j1[0],j2[0]);
    printf("|2 [total de 2]       |%6d|%6d|\n",j1[1],j2[1]);
    printf("|3 [total de 3]       |%6d|%6d|\n",j1[2],j2[2]);
    printf("|4 [total de 4]       |%6d|%6d|\n",j1[3],j2[3]);
    printf("|5 [total de 5]       |%6d|%6d|\n",j1[4],j2[4]);
    printf("|6 [total de 6]       |%6d|%6d|\n",j1[5],j2[5]);
    printf("|Bonus si > a 62 [35] |%6d|%6d|\n",j1[6],j2[6]);
    printf("|Total superieur      |%6d|%6d|\n",somme1J1,somme1J2);
    printf("|_____________________|______|______|\n");
    printf("|Brelan       [total] |%6d|%6d|\n",j1[7],j2[7]);
    printf("|Carre        [total] |%6d|%6d|\n",j1[8],j2[8]);
    printf("|Full House   [25]    |%6d|%6d|\n",j1[9],j2[9]);
    printf("|Petite suite [30]    |%6d|%6d|\n",j1[10],j2[10]);
    printf("|Grande suite [40]    |%6d|%6d|\n",j1[11],j2[11]);
    printf("|Yams         [50]    |%6d|%6d|\n",j1[12],j2[12]);
    printf("|Chance       [total] |%6d|%6d|\n",j1[13],j2[13]);
    printf("|Total superieur      |%6d|%6d|\n",somme2J1,somme2J2);
    printf("|_____________________|______|______|\n");
    printf("|Total                |%6d|%6d|\n",somme3J1,somme3J2);
    printf("|_____________________|______|______|\n");
    printf("\n");
} 

/**
 * @brief Procédure permettant l'initialisation à zéro de toutes les cellules du tableau des scores
 * 
 * @param[inout] tab tableau des scores du joueur
 */
void init_TabJ(score tab){ 
    int i;
    for (i = 0; i < N; i++){
        tab[i]=0;
    }
}

/**
 * @brief Procédure permettant l'initialisation à zéro de toutes les cellules du tableau des dés
 * 
 * @param[inout] tab tableau des scores du joueur
 */
void init_TabD(de tab){
    int i;
    for (i = 0; i < D; i++){
        tab[i]=0;
    }
}

/**
 * @brief Procédure permettant de lancé les dés du joueur courant
 * 
 * @param[inout] tabDeCourant tableau des dés courant du joueur courant
 * @param[inout] tabDeRetenu tableau des dé retenue du joueur courant
 */
void pLanceDe(de tabDeCourant,de tabDeRetenu){
    int i;
    srand(time(NULL)); // initialisation du nombre aléatoire en fonction de l'heure
    init_TabD(tabDeCourant); // reinitialise le tableau des dé courant 
    for (i = 0; i < MAX_DE; i++){
        tabDeCourant[i]=tabDeRetenu[i];
        if (tabDeCourant[i]==0){ // vérification que la valeur du tableau soit bien une valeur non sauvegardé
            tabDeCourant[i] = rand() % BORNE; // insert une varleur aléatoire dans 
            while (tabDeCourant[i]==0){ // boucle permettant de regénérer un nombre aléatoire si le nombre générer est 0
                tabDeCourant[i] = rand() % BORNE;
            }
        }
        printf("de %d: %d\n",i+1,tabDeCourant[i]); // affiche le dé 
    }
    init_TabD(tabDeRetenu); // reinitialise le tableau des dé retenu   
    printf("\n");
}

/**
 * @brief Procédure qui affiche le menu permettant au joueur de choisir après son lancement de dé
 * 
 * @param[inout] reponse entier signifiant le choix ou le joueur souhaite se diriger
 */
void afficheMenu(int *reponse){ 
    printf("Que choisissez vous ? \n1 - Garder tout les des \n2 - Relancer Certains des\n3 - Relancer tout les des\n");
    scanf("%d",reponse);
    printf("\n");
}

/**
 * @brief Procédure qui permet de choisir les dés à conserver
 * 
 * @param[inout] tabDeCourant tableau des dés courant du joueur courant
 * @param[inout] tabDeRetenu tableau des dés retenue du joueur courant
 */
void pChoisirDe(de tabDeCourant,de tabDeRetenu){
    int a,i=0;
    int tmp;
    init_TabD(tabDeRetenu); // reinitialise le tableau des dé retenu   
    printf("Veuillez choisir les des a concerver... (terminer la selection par 0 sauf si vous choisissez tous les dés) \n");
    do{
        scanf("%d",&a);
        if ((a!=0) && (a>0) && (a<6)){
            tmp = tabDeCourant[a-1];
            tabDeRetenu[a-1]=tmp;
        }else if ((a<0) || (a>5))
        {
            printf("Valeur incorrect\n");
        }
        
        i++;
    } while ((i<5) && (a!=0));
    printf("\n");
}

/**
 * @brief Procédure de tri par selection par ordre croissant
 * 
 * @param[inout] tabDeCourant tableau des dés courant du joueur courant
 */
void triSelection(de tabDeCourant){
    int i,j,min,indmin;
    int tmp;
    for(i=0;i<D-1;i++){ // boucle qui parcours le tableau
        min=tabDeCourant[i];
        indmin=i;
        for(j=i+1;j<D;j++){ // boucle qui parcours le tableau
            if (tabDeCourant[j]<min){ // vérification que le minimum soit plus petit que l'entier courant
            min=tabDeCourant[j]; // affectation de l'entier courant si le minimum est plus grand
            indmin=j; 
            }
        }
        tmp=tabDeCourant[i]; // permet l'échange de 2 cellules d'un tableau
        tabDeCourant[i]=tabDeCourant[indmin]; 
        tabDeCourant[indmin]=tmp;
    }
}

/**
 * @brief Procédure permettant l'affectation du score du joueur courant dans le tableau du joueur courant
 * 
 * @param[in] pseudo pseudo du joueur courant
 * @param[inout] tabJ tableau des scores du joueur courant
 * @param[inout] tabDeCourant tbleau des dés du joueur courant
 */
void affecterScore(char pseudo[7],score tabJ,de tabDeCourant){
    int i=0;
    int reponse;
    int somme=0;
    int compt1=0;
    int bonus=0;
    do{ // demande à l'utilisateur de saisir une cellule ou inserer le score en vérifiant que la valeur saisit soit supérieur ou égale à 0 et inférieur à 14
        printf("Quelle ligne du tableau choisisez vous ?\n");
        printf("Pour rappel voici les combinaison :\n1-1 / 2-2 / 3-3 / 4-4 / 5-5 / 6-6 / 8-Brelan / 9-Carre / 10-Full House / 11-Petit_suite / 12-Grande suite / 13-YAMS / 14-Chance / un autre nombre si rien\n");
        scanf("%d",&reponse);
        if (tabJ[reponse-1]!=0){ // verification que la cellule du tableau ou le joueur veux entrez son score ne soit pas déjà rempli
            printf("Erreur vous avez tentez d'inserez un score deja present dans le tableau\n\n");
            affecterScore(pseudo,tabJ,tabDeCourant); // relance la procédure
        }else if ((reponse<=0) || (reponse>14)){
            printf("Erreur valeur incohérente\n");
            affecterScore(pseudo,tabJ,tabDeCourant); // relance la procédure
        }
    } while (reponse <=0 && reponse>N); 
    if (reponse < 7){ // si la réponse correspond à la somme des dés (les 6 premières cellules de la grille)
        for (i = 0; i < MAX_DE; i++){ // parcours le tableau 
            if (tabDeCourant[i]==reponse ){ // vérifie que la valeur de la cellule soit égale à la valeurs demandé par l'utilisateur 
                somme=somme+tabDeCourant[i]; // fait la somme
            }  
        }
    }
    for (i = 0; i < 7; i++){ // boucle qui parcours les 6 premières cellules du tableau
       bonus = tabJ[i] + bonus; // fait la somme des valeurs des cellules de tabJ en fonction de i
    }if (bonus>=BONUS){ // vérification que la somme des valeurs des cellules soit supérieurs ou églae à la constante BONUS qui vaux 62
        tabJ[6]=PTS_BONUS; // affectation si de la constante PTS_BONUS
    }  
    switch (reponse)
    {
    case 0:
        break;
    case 1: // cellule 1
        if (somme==0){
            somme=-1;
        }else if (tabJ[3]==-1){
            somme=-1;
        }
        tabJ[0]=somme; // insertion de la somme à la case prévue
        break;
    case 2: // cellule 2
        if (somme==0){
            somme=-1;
        }else if (tabJ[3]==-1){
            somme=-1;
        }
        tabJ[1]=somme; // insertion de la somme à la case prévue
        break;
    case 3: // cellule 3
        if (somme==0){
            somme=-1;
        }else if (tabJ[3]==-1){
            somme=-1;
        }
        tabJ[2]=somme; // insertion de la somme à la case prévue
        break;
    case 4: // cellule 4
        if (somme==0){
            somme=-1;
        }else if (tabJ[3]==-1){
            somme=-1;
        }
        tabJ[3]=somme; // insertion de la somme à la case prévue
        break;
    case 5: // cellule 5
        if (somme==0){
            somme=-1;
        }else if (tabJ[4]==-1){
            somme=-1;
        }
        tabJ[4]=somme; // insertion de la somme à la case prévue
        break;
    case 6: // cellule 6
        if (somme==0){
            somme=-1;
        }else if (tabJ[5]==-1){
            somme=-1;
        }
        tabJ[5]=somme; // insertion de la somme à la case prévue
        printf("%d",tabJ[5]);
        break;
    case 8:
        triSelection(tabDeCourant); // tri le tableau courant des dés par séléction et par ordre croissant
        for (i = 0; i < 3; i++){ // parcours le tabeau jusqu'à 3
            if (tabDeCourant[i]==tabDeCourant[i+1] && tabDeCourant[i]==tabDeCourant[i+2]){ // vérification de i à i+2 que les valeurs sont égale
                somme = tabDeCourant[i]*3; // fait multiplication par 3 de la cellule i qui donne un brelan
            }
        }
        if (somme==0){ // vérification que la somme est nul et si oui, affiche une message d'erreur
            somme=-1;
        }else if (tabJ[7]==-1){
            somme=-1;
        }
        tabJ[7]=somme; // insertion de la somme dans la cellule prévue
        break;
    case 9:
        triSelection(tabDeCourant); // tri le tableau courant des dés par séléction et par ordre croissant
        for (i = 0; i < 2; i++){ // parcours le tableau jusqu'à 2
           if (tabDeCourant[i]==tabDeCourant[i+1] && tabDeCourant[i]==tabDeCourant[i+2] && tabDeCourant[i]==tabDeCourant[i+3]){ // vérifie que les valeurs de i à i+3 sont identique
                somme = tabDeCourant[i]*4; // multiplie par 4 la valeurs de la cellule répété 4 fois
            }
        }
        if (somme==0){ // vérification que la somme est nul et si oui, affiche une message d'erreur
            somme=-1;
        }else if (tabJ[8]==-1){
            somme=-1;
        }
        tabJ[8]=somme; // insertion de la somme dans la cellule prévue
        break;
    case 10:
        triSelection(tabDeCourant); // tri le tableau courant des dés par séléction et par ordre croissant
        for (i = 0; i < D-1; i++){ // boucle qui parcours le tableau
            if (tabDeCourant[i]==tabDeCourant[i+1]){ // vérification des premiers nombre identique du full house
                compt1=compt1+1;
            }else if(tabDeCourant[i+1]==tabDeCourant[i+2]){ //vérification de la seconde partie des nombres du full house
                compt1=compt1+1;
            }
        }if (compt1==4){ // vérification qu'il y ait la bonne combinaison 
            somme=FULL_HOUSE;
        }else if (tabJ[9]==-1){
            somme=-1;
        }else{
            somme=-1;
        }
        tabJ[9]=somme; // insertion de la somme dans la cellule prévue
        break;
    case 11:
        triSelection(tabDeCourant); // tri le tableau courant des dés par séléction et par ordre croissant
        for (i = 0; i < MAX_DE; i++){ // boucle qui parcours le tableau
            if (tabDeCourant[i]==tabDeCourant[i+1]-1){ // vérification que la valeur de la cellule i soit égale à al valeur de la vellule i+1 retrancher 1
                compt1= compt1 + 1; // si oui incrémntation du compteur 
            }    
        }
        if (compt1>=3){ // vérification que que la valeur du commpteur soit supérieur ou égal à 3
            somme = PETITE_SUITE; // somme prend la valeur de la constante PETITE_SUITE
        }else if (tabJ[10]==-1){
            somme=-1;
        }else{
            somme=-1;
        }
        tabJ[10]=somme; // insertion de la somme dans la cellule prévue
        break;
    case 12:
        triSelection(tabDeCourant); // tri le tableau courant des dés par séléction et par ordre croissant
        for (i = 0; i < MAX_DE; i++){ // boucle qui parcoure le tableau
            if (tabDeCourant[i]==tabDeCourant[i+1]-1){ // vérification que la cellule i du tableau est égale à la cellule i+1 retrancher 1
                compt1= compt1 + 1; // si oui incrémntation du compteur
            }    
        }
        if (compt1>=4){ // le le compteur est supérieur ou égal à 4
            somme = GRANDE_SUITE; // somme es égal à la valeur de la consatnte GRNDE_SUITE
        }else if (tabJ[11]==-1){
            somme=-1;
        }else{
            somme=-1;
        }
        tabJ[11]=somme; // insertion de la somme dans la cellule prévue
        break;
    case 13:
        for (i = 0; i < MAX_DE; i++){ // boucle qui parcour le tableau
            if (tabDeCourant[i]==tabDeCourant[i+1]){ // vérification pour savoir si la valeur de la cellule i est égale à celle de la cellule i+1
                compt1 = compt1 +1; // incrémentation du ompteur 
            }
        }
        if (compt1==4){ // vériiaction que le compteur soit égale à 4
            somme = YAMS; // si oui somme prend la valeur de la constante YAMS
        }else if (tabJ[12]==-1){
            somme=-1;
        }else{
            somme=-1;
        }
        tabJ[12]=somme; // insetion de la somme dans la cellule prévue
        break;
    case 14:
        for (i = 0; i < MAX_DE; i++){ // boucle qui parcours le tableau
            somme=somme+tabDeCourant[i]; // somme de toutes les valeurs des cellules du taleau
        }
        tabJ[13]=somme; // insertion de la somme dans la cellule prévue
        break;
    default: // en cas d'erreur et de valeurs autre que celle du switch relancé la procédure
        affecterScore(pseudo,tabJ,tabDeCourant); 
        break;
    }
}

/**
 * @brief Procédure permettant d'afficher le vainqueur après une partie de YAMS
 * 
 * @param pseudo1 pseudo du joueur 1
 * @param pseudo2 pseudo du joueur 2
 * @param j1 tableau des scores du joueur 1
 * @param j2 tableau des scores du joueur 2
 */
void afficherScore(char pseudo1[7],char pseudo2[7],score j1,score j2){ 
    int sommej1=0,sommej2=0;
    for (int i = 0; i < N; i++){ // boucle qui parcours les tableaux
        if (j1[i]!=-1 && j2[i]!=-1){ // vérification que les 2 cellules des tableaux des joeuurs ne soit pas blocké
            sommej1 = sommej1 + j1[i];
            sommej2 = sommej2 + j2[i];
        }else if (j1[i]==-1 && j2[i]!=-1){ // vérification que la cellule du joueur 1 soit blocké
            sommej2 = sommej2 + j2[i];
        }else if (j1[i]!=-1 && j2[i]==-1){ // vérification que la cellule du joueur 2 soit blocké
            sommej1 = sommej1 + j1[i];
        }
    }
    if (sommej1>sommej2){ // vérification que le score total du joueur 1 est supérieur au score total du joueur 2
        printf("Le vainqueur est le joueur 1 avec %d comme score !\n",sommej1);
        printf("Le perdant est le joueur 2 avec %d comme score !\n",sommej2);
    }else if (sommej1<sommej2){ // vérification que le score total du joueur 2 est supérieur au score total du joueur 1
        printf("Le vainqueur est le joueur 2 avec %d comme score !\n",sommej2);
        printf("Le perdant est le joueur 1 avec %d comme score !\n",sommej1);
    }else{ // sinon dire qu'il a égalité
        printf("C'est ne égalité tout les joueurs on %d comme score\n",sommej1);
    }
}

/**
 * \brief Programme principal
 * 
 * Programme principal permettant de jouez au yams grade au procdure et fonction ci-dessus !
 * 
 */
int main(){
    char pseudo1[7]; 
    char pseudo2[7];
    char rep;
    int i,essaie;
    int reponse;
    score tabJ1 = {};
    score tabJ2 = {};
    de tabDeCourant = {};
    de tabDeRetenue = {};
    fpseudo(pseudo1); // affectation du pseudo 1
    fpseudo(pseudo2); // affectation du pseudo 2
    init_TabJ(tabJ1); // initialisation du tableau des scores du joueur 1
    init_TabJ(tabJ2); // initialisation du tableau des scores du joueur 2
    init_TabD(tabDeCourant); // initialisation du tableau des dés courants
    init_TabD(tabDeRetenue); // initialisation du tableau des dés retenues
    for (i = 0; i < TOUR_MAX; i++){ // boucle représentant les 13 tours de jeux 
        printf("tours %d\n",i+1);
        afficheGrille(pseudo1,pseudo2,tabJ1,tabJ2); // affiche la grille des scores
        do{ // vérification que le joueurs veuillez bien lancé les dés
            rep = proposeLanceDe(pseudo1); // rep prend la valeurs retourné par la fonction proposeLanceDe
        } while (rep!='o');
        for (essaie = 0; essaie < MAX; essaie++){ // boucle représentant les 3 essaies de lancement des dés du joueur lors de son tour
            pLanceDe(tabDeCourant,tabDeRetenue); // lancement des dés
            if (essaie<MAX-1){ // vérification que le joueur n'est pas fait plus de 3 tours
                do{ // vérification que le joueur entre bien l'une des 3 posibilités du menus
                    afficheMenu(&reponse); // affiche le menu
                    if (reponse==1){ 
                        essaie=MAX; // affecte essaie à la valeur de la constante MAX pour pouvoir sortir de la boucle
                    }else if (reponse==2){
                        pChoisirDe(tabDeCourant,tabDeRetenue); // permet de choisir les dés à concerver
                    }else if (reponse==3){
                        printf("Relance de tout les des...\n\n"); 
                    }else{
                        printf("Veuillez saisir une valeurs correct\n");
                    }
                } while (reponse!=1 && reponse!=2 && reponse!=3);      
            }
        }
        affecterScore(pseudo1,tabJ1,tabDeCourant); // permet la demande de la ligne ou l'utilisateur veux entrer son score dans la grille des score

        afficheGrille(pseudo1,pseudo2,tabJ1,tabJ2); // affiche la grille des scores
        do{ // vérification que le joueurs veuillez bien lancé les dés
            rep = proposeLanceDe(pseudo2); // rep prend la valeurs retourné par la fonction proposeLanceDe
        } while (rep!='o');
        for (essaie = 0; essaie < MAX; essaie++){ // boucle représentant les 3 essaies de lancement des dés du joueur lors de son tour
            pLanceDe(tabDeCourant,tabDeRetenue); // lancement des dés
            if (essaie<MAX-1){ // vérification que le joueur n'est pas fait plus de 3 tours
                do{ // vérification que le joueur entre bien l'une des 3 posibilités du menus
                    afficheMenu(&reponse); // affiche le menu
                    if (reponse==1){ 
                        essaie=MAX; // affecte essaie à la valeur de la constante MAX pour pouvoir sortir de la boucle
                    }else if (reponse==2){
                        pChoisirDe(tabDeCourant,tabDeRetenue); // permet de choisir les dés à concerver
                    }else if (reponse==3){
                        printf("Relance de tout les des...\n\n"); 
                    }else{
                        printf("Veuillez saisir une valeurs correct\n");
                    }
                } while (reponse!=1 && reponse!=2 && reponse!=3);      
            }
        }
        affecterScore(pseudo2,tabJ2,tabDeCourant); // permet la demande de la ligne ou l'utilisateur veux entrer son score dans la grille des score
    }
    afficherScore(pseudo1,pseudo2,tabJ1,tabJ2); // permet d'afficher le vainqueur avec la grille des score
}