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
    //föreläsning 13, s.3
    Queue<int> Q; //en Queue med ints

    for(int i = 1; i <= size; ++i){
        dist[i] = INFINITY; //Sätter distans till oändligheten.
        path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s); //sätter start vertex i queue.

    while(!Q.isEmpty()){

        int v = Q.getFront();   //Ta bort första elementet från kön.
        Q.dequeue();

        //Från Lab 4: complementary instructions
        Node* temp = array[v].getFirst();  //getFirst returnerar en pekare till den första Noden som är grannen.

        while(temp != nullptr){
            //vertex är grannen
            if(dist[temp->vertex] == INFINITY){    //grannen besöktes aldrig
                dist[temp->vertex] = dist[v] + 1;  //uppdatera distansen, för vi går till nästa (unweighted) därför +1.
                path[temp->vertex] = v;            //uppdatera path till den tillbaka, föregående.
                Q.enqueue(temp->vertex);           //Lägger nästa granne i kön.
            }
            temp = array[v].getNext();             //Itererar, går till nästa granne.
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

    //föreläsning 13, s.6.
    for(int i=1; i<=size; i++){ //Ingen nod har besökts än, så alla distanser sätts till oändligheten.
        done[i] = false;
        dist[i] = INFINITY;
        path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s); //Sätt start vertex i kön.

    while(!Q.isEmpty()){
        int v = Q.getFront();
        Q.dequeue();            //Ta bort första elementet från kön.

        Node *temp = array[v].getFirst(); //Första noden

        while(temp != nullptr){

            if(dist[v] + temp->weight < dist[temp->vertex]){ //föreläsning 13, s.6.
                dist[temp->vertex] = dist[v]+temp->weight; //Lägger till vikten, för weighted graph som har värden.
                path[temp->vertex] = v;
                done[temp->vertex] = true;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
        //Istället för queue som vi gjort nu, gör:
        //loopa element i tabellen som inte är done och är lägst. Det är den som är på tur.
        //loopa alla obesökta och hitta den lägsta distansen

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

//Den här ska vara rekursiv istället för printPath, för att kunna printa ut distansen sist (som var önskat i output.txt).
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
