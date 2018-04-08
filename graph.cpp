#include "graph.h"
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::foret()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    /// La ligne précédente est en gros équivalente à :
    /// m_interface = new GraphInterface(50, 0, 750, 600);
    ///initialisation des variables
    int na, ns, i;

    int n_sommet, posx, posy,n_arreteA, n_arreteB,i_arrete;
    double p_sommet, p_arrete;
    std::string nom;

    ///ouvre le fichier
    ifstream fic("foret.txt", ios::in); //ouverture du fichier contenant le nb de sommets s et le nb d'aretes a
    if(fic)
    {
        fic >> ns;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');

        for(i=0; i<ns; i++)
        {
            fic>>n_sommet>> p_sommet>> posx>> posy>> nom;
            add_interfaced_vertex(n_sommet, p_sommet, posx, posy, nom);
        }
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        fic>>na;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        for(i=0; i<na; i++)
        {
            fic>> i_arrete>>n_arreteA>> n_arreteB>> p_arrete;
            add_interfaced_edge(i_arrete, n_arreteA, n_arreteB, p_arrete);
        }

        fic.close();

    }
}
void Graph::ocean()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    int na, ns, i;

    int n_sommet, posx, posy,n_arreteA, n_arreteB,i_arrete;
    double p_sommet, p_arrete;
    std::string nom;


    ifstream fic("ocean.txt", ios::in); //ouverture du fichier contenant le nb de sommets s et le nb d'aretes a
    if(fic)
    {
        fic >> ns;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');

        for(i=0; i<ns; i++)
        {
            fic>>n_sommet>> p_sommet>> posx>> posy>> nom;
            add_interfaced_vertex(n_sommet, p_sommet, posx, posy, nom);
        }
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        fic>>na;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        for(i=0; i<na; i++)
        {
            fic>> i_arrete>>n_arreteA>> n_arreteB>> p_arrete;
            add_interfaced_edge(i_arrete, n_arreteA, n_arreteB, p_arrete);
        }

        fic.close();

    }
}
void Graph::savane()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    int na, ns, i;

    int n_sommet, posx, posy,n_arreteA, n_arreteB,i_arrete;
    double p_sommet, p_arrete;
    std::string nom;


    ifstream fic("savane.txt", ios::in); //ouverture du fichier contenant le nb de sommets s et le nb d'aretes a
    if(fic)
    {
        fic >> ns;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');

        for(i=0; i<ns; i++)
        {
            fic>>n_sommet>> p_sommet>> posx>> posy>> nom;
            add_interfaced_vertex(n_sommet, p_sommet, posx, posy, nom);
        }
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        fic>>na;
        fic.ignore(numeric_limits<streamsize>::max(), '\n');
        for(i=0; i<na; i++)
        {
            fic>> i_arrete>>n_arreteA>> n_arreteB>> p_arrete;
            add_interfaced_edge(i_arrete, n_arreteA, n_arreteB, p_arrete);
        }

        fic.close();

    }
}

void Graph:: ajouter()
{   ///si on appuit sur clique droit
    if(mouse_b&2)
    {
        int a,j,n_sommet, posx, posy,n_arreteA, n_arreteB,i_arrete;
        double p_sommet, p_arrete;
        ///position de x prend la valeur de la position de la souri au moment du clique
        posx=mouse_x;
         ///position de y prend la valeur de la position de la souri au moment du clique
        posy=mouse_y;

        std::string nom;

        cout<<"Saisir l'indice de votre nouveau sommet: "<<endl;
        cin>> n_sommet;
        cout<<"Saisir le poids de votre nouveau sommet: "<<endl;
        cin>> p_sommet;
        cout<<"Saisir le nom du sommet: "<<endl;
        cin>>nom;
        ///affichage graphique du sommet
        add_interfaced_vertex(n_sommet, p_sommet, posx, posy, nom);

        cout<<"combien d'aretes seront relies au sommet?"<<endl;
        cin>>a;

        for(j=0; j<a; j++)
        {
            cout<<"Saisir l'indice de votre nouvelle arete "<<endl;
            cin>> i_arrete;
            cout<<"Saisir le sommet de depart "<<endl;
            cin>> n_arreteA;
            cout<<"Saisir le sommet d'arrivee"<<endl;
            cin>>n_arreteB;
            cout<<"Saisir le poids de l'arete "<<endl;
            cin>> p_arrete;
            ///affichqage graphiue des arrete
            add_interfaced_edge(i_arrete, n_arreteA, n_arreteB, p_arrete);
        }
    }

}
void Graph::ajouter_arrete()
{
    ///si on appui sur B
    if (key[KEY_B])
    {

        int j,n_arreteA, n_arreteB,i_arrete;
        double  p_arrete;

        cout<<"Saisir l'indice de votre nouvelle arete "<<endl;
        cin>> i_arrete;
        cout<<"Saisir le sommet de depart "<<endl;
        cin>> n_arreteA;
        cout<<"Saisir le sommet d'arrivee"<<endl;
        cin>>n_arreteB;
        cout<<"Saisir le poids de l'arete "<<endl;
        cin>> p_arrete;
        ///affichage graphique de larrete
        add_interfaced_edge(i_arrete, n_arreteA, n_arreteB, p_arrete);
    }
}
void Graph::sauvegarde(string nom_fichier)
{
    string numero;

    ofstream fic(nom_fichier+".txt",ios::out);
    if(fic)
    {
        /// on ecrit dans le fichier la taille de notre maps
        fic<<m_vertices.size()<<endl;
        for(auto &el:m_vertices)
        {
            ///on increment un conteur
            numero=to_string(el.first+1);

            fic<<el.first<<" "<< el.second.m_value<<" "<<el.second.m_interface ->m_top_box.get_posx()<<" "<<el.second.m_interface->m_top_box.get_posy()<<" "<<nom_fichier+numero+".jpg"<<endl;

        }
        /// on ecrit dans le fichier les arretes
        fic<<m_edges.size()<<endl;
        for(auto &el:m_edges)
        {
            fic<<el.first<<" "<<el.second.m_to<<" "<<el.second.m_from<<" "<<el.second.m_weight<<endl;
        }
    }

}
void Graph::test_remove_vertex(int eidx)
{
    /// référence vers le Edge à enlever
    Vertex &remed=m_vertices.at(eidx);
    std::cout << "Removing vertex " << eidx << " "<< remed.m_value << std::endl;


    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );
    }
    /// on parcourt la maps de sommet
    for(int i = m_vertices[eidx].m_in.size()-1; i>=0; i--)
    {
        test_remove_edge(m_vertices[eidx].m_in[i]);
    }
    /// on parcourt la maps darrete
    for(int i = m_vertices[eidx].m_out.size()-1; i>=0; i--)
    {
        test_remove_edge(m_vertices[eidx].m_out[i]);
    }
    ///on supprime le sommet
    m_vertices.erase(eidx);
}

void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l 'ajout de l'arc :
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

}
void Graph::supprimerA()
{
    ///Supprimer juste une arrete
    if(key[KEY_S])
    {
        int x;
        cout<<"quelle arete souhaitez vous supprimer ? "<<endl;
        cin>>x;
        test_remove_edge(x);
    }
}
void Graph::supprimerB()
{
    ///Suprimer un sommet avec ses arrete adjacentes
    if(key[KEY_F])
    {
        int x;
        cout<<"quel sommet voulez vous supprimer ? "<<endl;
        cin>>x;
        test_remove_vertex(x);
    }
}
void Graph::dynamisme()
{
    ///faire du dynamisme
    if(key[KEY_R])
    {

        double k=1;
///on parcours notre map de sommet
        for(auto& i:m_vertices)
        {
            ///on parcourt les sommets entrant a ce sommet
            for(const auto& j: i.second.m_in)
            {
                ///on parcour la map de sommet
                for(auto& l:m_edges)
                {
                    k = k + m_vertices[j].m_value*l.second.m_weight;
                    k=k/100;
                }
            }

            if(i.second.m_value>0)
            {
                i.second.m_value = i.second.m_value + 0.001*i.second.m_value*(1-i.second.m_value/k);
            }
        }
    }
}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

