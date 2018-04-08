#include "grman/grman.h"
#include <iostream>

#include "graph.h"
using namespace std;

int menu(Graph& g)
{
    int q=0;
    do
    {

        cout<<"quelle graphe voulez vous afficher ?"<<endl;
        cout<<"taper:"<<endl;
        cout<<"1 pour foret !"<<endl;
        cout<<"2 pour ocean !"<<endl;
        cout<<"3 pour savane !"<<endl;
        cout<<"4 pour quitter !"<<endl;
        cin>>q;
        if(q==1)
        {
            g.foret();

        }
        if(q==2)
        {
            g.ocean();

        }
        if(q==3)
        {
            g.savane();

        }
    }
    while(q<0 || q>3);
    return q;
}


int main()
{
    int val;
    /// A appeler en 1er avant d'instancier des objets graphiques etc...


    /// Le nom du r�pertoire o� se trouvent les images � charger


    /// Un exemple de graphe

    while (!key[KEY_ESC])
    {
        grman::init();
        grman::set_pictures_path("pics");
        Graph g;
        val=menu(g);
        while ( !key[KEY_V] )
        {


            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            g.update();
            g.ajouter();
            g.supprimerA();
            g.supprimerB();
            g.tab_dyn();
            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();

        }
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
        grman::fermer_allegro();
    }

    return 0;
}
END_OF_MAIN();


