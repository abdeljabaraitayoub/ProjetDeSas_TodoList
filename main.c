#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include<string.h>

//--------------------------------------------------------------------------------------------declaration de functions------------------------------------------------------------------------------------------------
void afficherMenu();
void AfficherLesTaches();
void ajouterTache();
void ModifierUneTache();
void SupprimerUneTache();
void RechercherUneTache();
void Statistiques();
//--------------------------------------------------------------------------------------------declaration de structure-------------------------------------------------------------------------------------------------
typedef struct
{
    int annes;
    int mois;
    int jour;
} temp;
typedef struct
{
    int identifiant;
    char titre[25];
    //int deadline;
    temp deadline ;
    char statut[40];
    char description[50];
} Tache;
Tache taches[100];


//--------------------------------------------------------------------------------------------------global variables---------------------------------------------------------------------------------------------------
int numTache=0;
char back;
int mod=0;
int currentjour,currentannes,currentmois;
int restejour,resteannes,restemois;
int realiser,finalisee;
int totalDays;
int counteurdays;
//----------------------------------------------------------------------------------------------------current time--------------------------------------------------------------------------------------------------------
int currenTime()
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    currentjour=t.wDay;
    currentmois=t.wMonth;
    currentannes=t.wYear;
    totalDays=currentjour+currentmois*30+t.wYear*365;
    return totalDays;
}


int main()
{
    // declaration des locals variables.
    int choix;

    do
    {
        system("cls");
        afficherMenu();
        printf("\t\t le Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterTache();
            break;
        case 2:
            AfficherLesTaches();
            break;
        case 3:
            ModifierUneTache();
            break;
        case 4:
            RechercherUneTache();

            break;
        case 5:
            SupprimerUneTache();
            break;
        case 6:
            Statistiques();
            break;
        case 0:
            printf("\t\t Au revoir ;)\n");
            break;
        default:
            printf("Choix invalide. Veuillez ressayer :");

            break;
        }
    }
    while (choix!=0);

    return 0;
}
void afficherMenu()
{
    printf("             *************************************************************************************\n");
    printf("             ************************************* ToDo list *************************************\n");
    printf("             *************************************************************************************\n");
    printf("             *                                [1] L'ajout des taches.                            *\n");
    printf("             *                                   [2] Afficher.                                   *\n");
    printf("             *                            [3] Modification d'une tache.                          *\n");
    printf("             *                              [4] Recherche d'une tache.                           *\n");
    printf("             *                             [5] supression d'une tache.                           *\n");
    printf("             *                                 [6] Statistiques                                  *\n");
    printf("             **************************************[0] Exit.**************************************\n");
}

void ajouterTache()
{
    int NombreDajout;
    int status;
    printf("====>Combien de taches voulez-vous entrer : ");
    scanf("%d", &NombreDajout);
    NombreDajout+=numTache;

    for (int i = numTache; i<NombreDajout; i++)
    {
        printf("                 *****************************l'ajout de tache numero %d*******************************\n",i+1);
        //printf("\tEntrer l'identifiant de la tache : ");
        // scanf("%d",&taches[i].identifiant);
        taches[i].identifiant=i+1;

        printf("----> Entrer le titre de la tache : ");
        getchar();
        gets(taches[i].titre);
        printf("\n");

        printf("----> Entrer la description de la tache : ");
        gets(taches[i].description);
        printf("\n");


        do
        {
            printf("----> Entrer le nombre de statut de la tache : \n");
            printf("---------> [1] realiser                 \n");
            printf("---------> [2] en cours de realisation  \n");
            printf("---------> [3] finalisee                \n");
            printf("---------> ");
            scanf("%d",&status);
            switch(status)
            {
            case 1 :
                strcpy(taches[i].statut,"realiser");
                realiser++;
                break;
            case 2 :
                strcpy(taches[i].statut,"en cours de realisation");
                break;
            case 3 :
                strcpy(taches[i].statut,"finalisee");
                finalisee++;
                break;
            }
        }
        while(status !=1 && status != 2 && status !=3);

        printf("---->le deadline de la tache.\n");

        printf("--------->entrer le jour : ");
        scanf("%d",&taches[i].deadline.jour);

        printf("--------->entrer le mois : ");
        scanf("%d",&taches[i].deadline.mois);

        printf("--------->entrer l'annes : ");
        scanf("%d",&taches[i].deadline.annes);
        printf("\n");



        printf("--------> BRAVO,Cette tache est ajoutee ;)\n");
        printf("\n");
        numTache ++;
    }
    printf("-->Appuyez sur n'importe quelle touche pour revenir au menu : ");
    scanf("%s",&back);
}
void AfficherLesTaches()
{
    int i,j;
    int TypeAffichage;
    if (numTache<=0)
    {
        printf("\n\t\tajouter une tache avant d'afficher :'(\n");
        printf("\n");
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
    }
    else
    {
        do
        {
            printf("\t[1] affichage normale .\n");
            printf("\t[2] affichage par tri alphabetique .\n");
            printf("\t[3] affichage par tri de deadline .\n");
            printf("\t[4] Afficher les t�ches dont le deadline est dans 3 jours ou moins. \n");
            printf("\t\t le choix : ");
            scanf("%d",&TypeAffichage);
            switch(TypeAffichage)
            {

            case 1 :
                for(i=0; i<numTache; i++)
                {
                    printf("                 ===================================tache numero %d=====================================\n",i+1);
                    printf("\tl'dentifiant est : %d\n",taches[i].identifiant);
                    printf("\tle titre est : %s\n",taches[i].titre);
                    printf("\tla status est : %s\n",taches[i].statut);
                    printf("\tle description est : %s\n",taches[i].description);
                    printf("\tle deadline est : %d/%d/%d\n",taches[i].deadline.annes,taches[i].deadline.mois,taches[i].deadline.jour);
                    printf("                 --------------------------------------------------------------------------------------\n");
                }
                printf("Appuyez n'importe quelle touche pour revenir au menu : ");
                scanf("%s",&back);
                break;
            case 3:
                for (i = 0; i < numTache - 1; i++)
                {
                    for (j = i + 1; j < numTache; j++)
                    {
                        if (taches[i].deadline.mois*30+taches[i].deadline.jour+taches[i].deadline.annes*365<taches[j].deadline.mois*30+taches[j].deadline.jour+taches[j].deadline.annes*365)
                        {
                            // Swap the tasks
                            Tache temp = taches[i];
                            taches[i] = taches[j];
                            taches[j] = temp;
                        }
                    }
                }
                for (i = 0; i < numTache; i++)
                {
                    printf("=================================== Tache numero %d =====================================\n", i + 1);
                    printf("L'identifiant est : %d\n", taches[i].identifiant);
                    printf("Le titre est : %s\n", taches[i].titre);
                    printf("Le statut est : %s\n", taches[i].statut);
                    printf("La description est : %s\n", taches[i].description);
                    printf("\tle deadline est : %d/%d/%d\n",taches[i].deadline.annes,taches[i].deadline.mois,taches[i].deadline.jour);
                    printf("-----------------------------------------------------------------------------------------\n");
                }
                printf("Appuyez n'importe quelle touche pour revenir au menu : ");
                scanf("%s",&back);
                break;
            case 2:
                for (i = 0; i < numTache - 1; i++)
                {
                    for (j = i + 1; j < numTache; j++)
                    {
                        if ((taches[i].deadline.mois*30+taches[i].deadline.jour+taches[i].deadline.annes*365<taches[j].deadline.mois*30+taches[j].deadline.jour+taches[j].deadline.annes*365))
                        {
                            // Swap the tasks
                            Tache temp = taches[i];
                            taches[i] = taches[j];
                            taches[j] = temp;
                        }
                    }
                }
                for (i = 0; i < numTache; i++)
                {
                    printf("=================================== Tache numero %d =====================================\n", i + 1);
                    printf("L'identifiant est : %d\n", taches[i].identifiant);
                    printf("Le titre est : %s\n", taches[i].titre);
                    printf("Le statut est : %s\n", taches[i].statut);
                    printf("La description est : %s\n", taches[i].description);
                    printf("\tle deadline est : %d/%d/%d\n",taches[i].deadline.annes,taches[i].deadline.mois,taches[i].deadline.jour);
                    printf("-----------------------------------------------------------------------------------------\n");
                }
                printf("Appuyez n'importe quelle touche pour revenir au menu : ");
                scanf("%s",&back);
                break;
            case 4 :
                for (int i=0; i<numTache; i++)
                {
                    if (taches[i].deadline.mois*30+taches[i].deadline.jour+taches[i].deadline.annes*365-totalDays<=3)
                    {
                        printf("=================================== Tache numero %d =====================================\n",i+1);
                        printf("L'identifiant est : %d\n", taches[i].identifiant);
                        printf("Le titre est : %s\n", taches[i].titre);
                        printf("\tle deadline est : %d/%d/%d\n",taches[i].deadline.annes,taches[i].deadline.mois,taches[i].deadline.jour);
                        printf("-----------------------------------------------------------------------------------------\n");
                        counteurdays++;
                        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
                        scanf("%s",&back);
                    }
                    if(counteurdays==0)
                    {
                        printf("\taucune resultat . ");
                        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
                        scanf("%s",&back);

                    }
                }


                break;


            }
        }

        while(TypeAffichage<0&&TypeAffichage>3);
    }
}
void ModifierUneTache()
{
    int status;
    if (numTache<=0)
    {
        printf("\n\t\tajouter une tache avant de modifier :'(\n");
        printf("\n");
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
    }
    else
    {
        for (int i = 0; i < numTache; i++)
        {
            printf("=================================== Tache numero %d =====================================\n", i + 1);
            printf("L'identifiant est : %d\n", taches[i].identifiant);
            printf("Le titre est : %s\n", taches[i].titre);
            printf("-----------------------------------------------------------------------------------------\n");

        }
        printf("entrer le numero de la tache qui vous vouler modifier : ");
        scanf("%d",&mod);

        printf("----> Entrer le nouveau titre de la tache : ");
        getchar();
        gets(taches[mod-1].titre);
        printf("\n");

        do
        {
            printf("----> Entrer le nombre de la nouvelle statut de votre tache : \n");
            printf("---------> [1] realiser                 \n");
            printf("---------> [2] en cours de realisation  \n");
            printf("---------> [3] finalisee                \n");
            printf("---------> ");
            scanf("%d",&status);
            switch(status)
            {
            case 1 :
                strcpy(taches[mod-1].statut,"realiser");
                break;
            case 2 :
                strcpy(taches[mod-1].statut,"en cours de realisation");
                break;
            case 3 :
                strcpy(taches[mod-1].statut,"finalisee");
                break;
            }
        }
        while(status !=1 && status != 2 && status !=3);


        printf("----> Entrer la nouvelle description de la tache : ");
        gets(taches[mod-1].description);
        printf("\n");


        printf("----> Entrer le nouveua deadline de la tache. \n ");
        printf("--------->entrer le jour : ");
        scanf("%d",&taches[mod-1].deadline.jour);
        printf("--------->entrer le mois : ");
        scanf("%d",&taches[mod-1].deadline.mois);
        printf("--------->entrer l'annes : ");
        scanf("%d",&taches[mod-1].deadline.annes);
        printf("\n");


        printf("--------> BRAVO,Cette tache est modifier ;)\n");
        printf("\n");
    }
}
void RechercherUneTache()
{
    int recherche=0;
    int Typerecherche=1;
    char titre[25];
    int RechercheResultat;
    int counteur=0;
    if (numTache<=0)
    {
        printf("\n\t\tajouter une tache avant de rechercher :'(\n");
        printf("\n");
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
    }
    else
    {
        printf("\t[1] recherche par Identicateur .\n");
        printf("\t[2] recherche par titre .\n");
        printf("\t\t le choix : ");
        scanf("%d",&Typerecherche);
        switch(Typerecherche)
        {
        case 1 :
            for (int i = 0; i < numTache; i++)
            {
                printf("=================================== Tache numero %d =====================================\n", i + 1);
                printf("L'identifiant est : %d\n", taches[i].identifiant);
                printf("Le titre est : %s\n", taches[i].titre);
                printf("-----------------------------------------------------------------------------------------\n");

            }
            printf("entrer l'identicateur de la tache qui vous vouler rechercher: ");
            scanf("%d",&recherche);
            system("cls");
            afficherMenu();
            printf("\n");
            printf("=================================== Tache numero %d =====================================\n", recherche);
            printf("L'identifiant est : %d\n", taches[recherche-1].identifiant);
            printf("Le titre est : %s\n", taches[recherche-1].titre);
            printf("Le statut est : %s\n", taches[recherche-1].statut);
            printf("La description est : %s\n", taches[recherche-1].description);
            printf("\tle deadline est : %d/%d/%d\n",taches[recherche-1].deadline.annes,taches[recherche-1].deadline.mois,taches[recherche-1].deadline.jour);
            printf("-----------------------------------------------------------------------------------------\n");
            printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
            scanf("%s",&back);
            break;
        case 2 :
            for (int i = 0; i < numTache; i++)
            {
                printf("=================================== Tache numero %d =====================================\n", i + 1);
                printf("L'identifiant est : %d\n", taches[i].identifiant);
                printf("Le titre est : %s\n", taches[i].titre);
                printf("-----------------------------------------------------------------------------------------\n");

            }
            printf("entrer le titre de la tache qui vous vouler rechercher: ");
            scanf("%s",&titre);
            printf("\n");
            for (int i=0; i<numTache; i++)
            {
                RechercheResultat=strcmp(taches[i].titre,titre);
                if(RechercheResultat==0)
                {
                    printf("=================================== Tache numero %d =====================================\n",i+1);
                    printf("L'identifiant est : %d\n", taches[i].identifiant);
                    printf("Le titre est : %s\n", taches[i].titre);
                    printf("Le statut est : %s\n", taches[i].statut);
                    printf("La description est : %s\n", taches[i].description);
                    printf("\tle deadline est : %d/%d/%d\n",taches[i].deadline.annes,taches[i].deadline.mois,taches[i].deadline.jour);
                    printf("-----------------------------------------------------------------------------------------\n");
                    printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
                    scanf("%s",&back);
                    counteur++;
                }
            }
            if(counteur==0)
            {
                printf("\tpas de tache avec ce nom .");
                printf("\n\tAppuyez n'importe quelle touche pour revenir au menu : ");
                scanf("%s",&back);
            }
            break;
        }
    }

}
void SupprimerUneTache()
{
    int sup;
    int i,j;
    printf("veuiller emtrer l'identicateur de la tache qui vous voullez supprimer : ");
    scanf("%d",&sup);
    for (i=0; i<numTache; i++)
    {
        if(sup==taches[i].identifiant)
        {
            for(j=i+1; j<numTache; j++)
            {
                taches[i]=taches[j];
            }
            numTache--;
        }
    }
}
void Statistiques()
{
    int TypeStat;
    if (numTache<=0)
    {
        printf("\n\t\tajouter une tache avant de voir les statistiques :'(\n");
        printf("\n");
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
    }
    else
    {
        printf("\t[1] afficher le nombre total des taches .\n");
        printf("\t[2] afficher le nombre de taches complete et incomplete .\n");
        printf("\t[3] afficher le nombre de jours restants jusqu'au delai de chaque tache .\n");
        printf("\t\t le choix : ");
        scanf("%d",&TypeStat);
    }
    switch(TypeStat)
    {
    case 1 :
        printf("\t---->le nombre total des taches est : %d\n\n",numTache);
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
        break;
    case 2 :
        printf("\t---->le nombre total des taches realiser est : %d\n\n",realiser);
        printf("\t---->le nombre total des taches finalisee est : %d\n\n",finalisee);
        printf("\tAppuyez n'importe quelle touche pour revenir au menu : ");
        scanf("%s",&back);
        break;





    }


}


