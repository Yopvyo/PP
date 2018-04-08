#include "grman/grman.h"
#include <iostream>
#include <cstdlib>

#include "graph.h"
using namespace std;

int menu(Graph& g)
{
    cout<< "Bienvenue sur le projet de theorie des graphes !"<<endl;
    cout<< "les regles sont les suivantes:"<<endl;
    cout<< "respecter le menue pour savoir quoi afficher comme graphe "<<endl;
    cout<< "une fois un graphe ouvert appuyer sur l'interface graphique: "<<endl;
    cout<< "- sur clique droit pour ajouter un sommet !!"<<endl;
    cout<< "- sur B pour ajouter juste une arrete !!"<<endl;
    cout<< "- sur F pour supprimer un sommet !! "<<endl;
    cout<< "- sur S pour supprimer une arrete !!"<<endl;
    cout<< "- sur R pour faire apparaitre le dynamisme !!"<<endl;
    cout<< "- sur V pour sauvegarder et pouvoir ouvrir un nouveau graphe !!"<<endl<<endl;
    int q=0;
    do
    {

        cout<<"quelle graphe voulez vous afficher ?"<<endl;
        cout<<"taper:"<<endl;
        cout<<"1 pour foret !"<<endl;
        cout<<"2 pour ocean !"<<endl;
        cout<<"3 pour savane !"<<endl;
        cin>>q;
        ///ouvre le fichier foret et le li et l'affiche graphiquement
        if(q==1)
        {
            g.foret();

        }
        ///ouvre le fichier ocean et le li et l'affiche graphiquement
        if(q==2)
        {
            g.ocean();

        }
        ///ouvre le fichier savane et le li et l'affiche graphiquement
        if(q==3)
        {
            g.savane();

        }
    }///blindage si on saisie un autre chiffre
    while(q<0 || q>3);
    ///return Q pour la sauvegrade
    return q;
}


int main()
{
    int val;

    while (!key[KEY_ESC])
    {
        ///ouvre allegro
        grman::init();
        ///donne le chemin pour trouver les photos
        grman::set_pictures_path("pics");
        ///creation d'un graphe appele g
        Graph g;
        ///Appelle le menu
        val=menu(g);
        ///boucle de jeu graphique
        while ( !key[KEY_V] )
        {


            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();
            ///ajouter sommet
            g.ajouter();
            ///ajouter une arrete
            g.ajouter_arrete();
            ///supprimer un sommet
            g.supprimerA();
            ///supprier un sommet et ses arrete adjacente
            g.supprimerB();
            ///lance le dynamisme
            g.dynamisme();
            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();

        }
        ///permet de sauvegarder le graphe quon a ouvert
          switch(val)
            {
                case 1 :
                    g.sauvegarde("foret");
                    break;
                case 2 :
                    g.sauvegarde("ocean");
                    break;
                case 3 :
                    g.sauvegarde("savane");
                    break;
            }
        ///permet de nettoyer la console
        system("cls");
        ///ferme allegro
        grman::fermer_allegro();
    }

    return 0;
}
END_OF_MAIN();


