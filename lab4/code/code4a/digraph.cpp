/*********************************************
 * file:	~\lab4a\digraph.cpp               *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

// NOTE: graph vertices are numbered from 1 -- i.e. there is no vertex zero

const int infinity = numeric_limits<int>::max();
// -- CONSTRUCTORS

Digraph::Digraph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
    dist.resize(size + 1);
    path.resize(size + 1);
    done.resize(size + 1);
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<std::tuple<int, int, int>> &V, int n) : Digraph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);

    n_edges += 1;
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);

    n_edges -= 1;
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    // *** TODO ***
    
    Queue<int> Q; //a queue, similar to level order of binary trees
    
    for (int i = 1; i<=size; i++){ //for all i thats in V //ORDER O(n)
        dist[i] = infinity; //record the distance
        path[i] = 0; //record the path
    }
    
    dist[s] = 0; //start node, distance is zero
    Q.enqueue(s); //place the start node in the queue
    
    while (!Q.isEmpty()){ //while the queue is not empty, continue //ORDER O(n + m) n=nodes m=edges
        
        int v = Q.getFront(); //get the node that is in the front of the queue
        Q.dequeue();
        
        Node *temp = table[v].getFirst();

            while(temp != nullptr) //every vertex that can be reached from node v
            {
                if(dist[temp->vertex] == infinity) //check if the node has not yet been visited (we may have loops/cycles in the graph) infinity is the distance if we have not yet visited the node
                {
                    dist[temp->vertex] = dist[v] + 1; //update the distance, the distance we have to reach node v +1
                    path[temp->vertex] = v; //record in the path, i can reach node u coming from node v
                    Q.enqueue(temp->vertex); //place in the queue node u
                }

                temp = table[v].getNext();
            }
        
    }
}

// positive weighted single source shortest paths
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    // *** TODO ***
    for (int i = 1; i <= size; ++i) //for all i thats in V //ORDER O(n)
        {
            dist[i] = infinity; //record the distance
            path[i] = 0; //record the path
            done[i] = false; //mark as visited
        }

        dist[s] = 0;
        done[s] = true;
        int v = s; //start  node

        while(true)
        {
            Node *temp = table[v].getFirst();

            while (temp != nullptr) //every vertex that can be reached from node v
            {
                if (!done[temp->vertex] && dist[temp->vertex] > (dist[v] + temp->weight)) //comparing whats the cost of reaching u coming from v with the cost we have from node u so far
                {
                    dist[temp->vertex] = dist[v] + temp->weight; //update the distance from node u
                    path[temp->vertex] = v; //update path
                }

                temp = table[v].getNext();
            }

            int smallestDistance = infinity;
            
            // Update vertex according to shortest distance
            for (int i = 1; i <= size; ++i)
            {
                if (!done[i] && dist[i] < smallestDistance)
                {
                    smallestDistance = dist [i]; // update shortest path
                    v = i;
                }
            }
            
            
            if (smallestDistance == infinity) break; // All nodes have been added to the tree => exit

            done[v] = true;   //Else, add to the tree.
        }
}

// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }

    std::cout << "----------------------\n";
}

//// print shortest path from s to t
//void Digraph::printPath(int t) const {
//    if (t < 1 || t > size) {
//        std::cout << "\nERROR: expected target t in range 1.." << size << " !\n";
//        return;
//    }
//
//    // *** TODO ***
//    printPathOnly(path[t]);
//
//        std::cout << " " << t << " ";
//        std::cout << "(" << dist[t] << ")";
//}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
    if (path[t] == 0)
    {
        cout << " " << t << " ";
        return;
    }

    printPath(path[t]);
    
    cout << "-> " << t << " ";
    
    cout << "(" << dist[t] << ")";

}

void Digraph::printPathOnly(int t) const{

   if(path[t] == 0){
       std::cout << " " << t << " ";
       return;
   }

   //Visit the previous node in the path
   printPathOnly(path[t]);
   std::cout << " " << t << " ";

}
