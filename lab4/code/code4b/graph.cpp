/*********************************************
 * file:	~\tnd004\lab\lab4b\graph.h        *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert
#include <limits>   //std::numeric_limits

 using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int infinity = numeric_limits<int>::max();

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create an empty graph with n vertices
Graph::Graph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
}

Graph::Graph(const std::vector<std::tuple<int, int, int>> &V, int n) : Graph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);
    table[v].insert(u, w);

    n_edges += 2;
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);
    table[v].remove(u);

    n_edges -= 2;
}

// Prim's minimum spanning tree algorithm, starts from any given vertex
void Graph::mstPrim() const {

    int *dist = new int[size]; //weight
    int *path = new int[size]; //edges
    bool *done = new bool[size]; //visited node
    
    for (int i = 1; i<=size; i++){ //for all i thats in V //ORDER O(n) //put default values
        dist[i] = infinity; //record the distance
        path[i] = 0; //record the path
        done[i] = false;
    }
    
    //First node values
    int v = 1;
    dist[v] = 0;
    done[v] = true;
    int totalWeight = 0;
    
    
    while (true) {
        Node *temp = table[v].getFirst(); // u = temp->vertex, first value in the table
        
        while(temp != nullptr) //every vertex that can be reached from node v
        {
            if(done[temp->vertex]==false && dist[temp->vertex]>(temp->weight)) //check if the node has not yet been visited (we may have loops/cycles in the graph)
            {
                dist[temp->vertex] = temp->weight; //update the distance, the distance we have to reach node v + 1
                path[temp->vertex] = v; //record in the path, i can reach node u coming from node v
            }

            temp = table[v].getNext(); //Go to the next vertex
        }
        
        int smallestDistance = infinity;

                for(int i = 1; i <= size; ++i)
                {
                    if(!done[i] && dist[i] < smallestDistance) //If the node has not been visited and the distance is smaller than the smallest distance so far
                    {
                        smallestDistance = dist[i]; //update vertex for the shortest path
                        v = i;
                    }
                }

                if (smallestDistance == infinity) break;
                Edge myEdge(path[v], v, dist[v]);
                cout << myEdge << endl;
                totalWeight += dist[v];
        
                done[v] = true;
    }

            cout << "Total weight is: " << totalWeight << endl;
}

// Kruskal's minimum spanning tree algorithm, starts from the vertex that carries the minimum weight
void Graph::mstKruskal() const {

    // *** TODO ***
       Heap<Edge> myHeap(size - 1); //create heap that stores edges, same size as the graph/tree (as many nodes as the graph minus one)
       DSets mySets(size); //from dsets.cpp
       int counter = 0;
       int totalWeight = 0;

       //Add all edges to heap "heapfify"
       for(int i = 1; i <= size; ++i)
       {
           Node* temp = table[i].getFirst();
           
           while(temp != nullptr)
           {
               if(i < temp->vertex) //sort
               {
                   Edge myEdge(i, temp->vertex, temp->weight); //create the edge
                   myHeap.insert(myEdge); //add edge to heap
               }

               temp = temp->next;
           }
       }
       
       //From FÖ14

       while(counter < size - 1)
       {
           Edge myEdge = myHeap.deleteMin();   //Find the edge with lowest cost

           //u and v are in different trees, avoid cycles
           if(mySets.find(myEdge.head) != mySets.find(myEdge.tail))
           {
               cout << myEdge << endl;
               
               //merge two different trees
               mySets.join(mySets.find(myEdge.head), mySets.find(myEdge.tail));
               totalWeight += myEdge.weight;
               counter++;
           }

       }

       cout << "Total weight is: " << totalWeight << endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}
