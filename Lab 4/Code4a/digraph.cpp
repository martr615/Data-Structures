/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    //f�rel�sning 13, s.3
    Queue<int> Q; //en Queue med ints

    for(int i = 1; i <= size; ++i){
        dist[i] = INFINITY; //S�tter distans till o�ndligheten.
        path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s); //s�tter start vertex i queue.

    while(!Q.isEmpty()){

        int v = Q.getFront();   //Ta bort f�rsta elementet fr�n k�n.
        Q.dequeue();

        //Fr�n Lab 4: complementary instructions
        Node* temp = array[v].getFirst();  //getFirst returnerar en pekare till den f�rsta Noden som �r grannen.

        while(temp != nullptr){
            //vertex �r grannen
            if(dist[temp->vertex] == INFINITY){    //grannen bes�ktes aldrig
                dist[temp->vertex] = dist[v] + 1;  //uppdatera distansen, f�r vi g�r till n�sta (unweighted) d�rf�r +1.
                path[temp->vertex] = v;            //uppdatera path till den tillbaka, f�reg�ende.
                Q.enqueue(temp->vertex);           //L�gger n�sta granne i k�n.
            }
            temp = array[v].getNext();             //Itererar, g�r till n�sta granne.
        }
    }
}


// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    Queue<int> Q;

    //f�rel�sning 13, s.6.
    for(int i=1; i<=size; i++){ //Ingen nod har bes�kts �n, s� alla distanser s�tts till o�ndligheten.
        done[i] = false;
        dist[i] = INFINITY;
        path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s); //S�tt start vertex i k�n.

    while(!Q.isEmpty()){
        int v = Q.getFront();
        Q.dequeue();            //Ta bort f�rsta elementet fr�n k�n.

        Node *temp = array[v].getFirst(); //F�rsta noden

        while(temp != nullptr){

            if(dist[v] + temp->weight < dist[temp->vertex]){ //f�rel�sning 13, s.6.
                dist[temp->vertex] = dist[v]+temp->weight; //L�gger till vikten, f�r weighted graph som har v�rden.
                path[temp->vertex] = v;
                done[temp->vertex] = true;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
        //Ist�llet f�r queue som vi gjort nu, g�r:
        //loopa element i tabellen som inte �r done och �r l�gst. Det �r den som �r p� tur.
        //loopa alla obes�kta och hitta den l�gsta distansen

    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    printHelp(t);

    //skriva ut distansen sist
    cout << " (" << dist[t] << ")" << endl;

}

//Den h�r ska vara rekursiv ist�llet f�r printPath, f�r att kunna printa ut distansen sist (som var �nskat i output.txt).
void Digraph::printHelp(int t) const{

    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }
    // *** TODO ***
    if(dist[t] != 0){
        printHelp(path[t]); //rekursivt
    }
    cout << " " << t;

}
