/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    int dist[size+1];
    bool done[size+1];
    int path[size+1];
    Edge edges[size];

    //föreläsning 14, s.3
    for(int i=0; i<=size; i++){
        done[i] = false;
        dist[i] = INFINITY;
        path[i] = 0;
    }

    int nextNode= 1;
    dist[nextNode] = 0;
    done[nextNode] = true;
    int nextCloudMember = 0;
    int nEdges = 0;

    while(nEdges < size-1){
        //Lägger en nod till molnet.
        done[nextNode] = true;
        nextCloudMember = 0;
        //Loopa igenom alla ihopkopplade edges på molnet.
        for(int i = 1; i <= size; i++){
            if(done[i]){
                Node *temp = array[i].getFirst();
                while (temp != nullptr){
                    if(!done[temp->vertex]){
                        if(temp->weight < dist[temp->vertex]){  //uppdatera om en kortar path hittas.
                            path[temp->vertex] = i;             //Föreläsning 14, s3, path(u) = w(v,y);
                            dist[temp->vertex] = temp->weight;  //dist(u) = w(v,u) (vikten)
                        }
                        //Spara närmsta grannen till molnet.
                        if(dist[temp->vertex] < dist[nextCloudMember]){
                            nextCloudMember = temp->vertex;
                        }
                    }
                    temp = temp->next;
                }
            }
        }
        //lägger in allt i ordning till edge, alltså head, tail, weight. E = (u,v,w)
        edges[nEdges] = Edge(path[nextCloudMember], nextCloudMember, dist[nextCloudMember]);
        nextNode = nextCloudMember;
        nEdges++;
    }

    //Räkna totala vikten.
    int totalWeight = 0;
    for(int i = 0; i<size-1; i++){
        cout << edges[i] << endl;
        totalWeight += edges[i].weight;
    }
    cout<< endl << "Total weight = " << totalWeight <<endl;
}


// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
    //föreläsning 14, s5
    Heap<Edge> H(size);
    DSets D(size+1);
    bool done[size+1]; //använder mer minne i algoritmen, onödigt.

    for(int i=0; i<=size; i++){
        done[i] = false;
    }
    //Sätt in grafens edges.
    for(int i = 1; i <= size; i++){
        Node *temp = array[i].getFirst(); //Pekare till första noden.
        done[i] = true;
        while(temp != nullptr){
            if(!done[temp->vertex]){
                Edge e(i, temp->vertex, temp->weight);
                H.insert(e);
            }
            temp = temp->next;
        }
    }

    int counter = 0;
    int totalWeight = 0;
    while (counter < size-1){
        Edge e = H.deleteMin();
        //Noderna länkas om de inte är i samma träd.
        if (D.find(e.tail) != D.find(e.head)){
            D.join(D.find(e.tail), D.find(e.head));
            counter++;
            cout << e << endl;
            totalWeight += e.weight; //Räkna totala vikten.
        }
    }
    cout<< endl << "Total weight = " << totalWeight <<endl;

}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
