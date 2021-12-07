//
// Created by Abigail Spigarelli on 11/30/21.
//

#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H
#include <stack>
#include <map>
#include <set>
#include <vector>
using namespace std;

//what does a graph object look like?

class graph {
private:
    stack<int> topologialSort;
    //.push(node) onto the stack to get the post order
    map<int, set<int>> mapOfEdges;
    set<int> SCC;
public:
    graph(map<int, set<int>> );
    void addEdge(int key, int newEdge);
    string toString(); //prints out the dependency graph
    map<int, set<int>> getMapOfEdges(){return mapOfEdges;}
    stack<int> getPostOrder(){ return topologialSort;}
    set<int> getSCC(){ return SCC;}
    void updateSCC(set<int> newSCC){SCC = newSCC;};

    void DFS(int, set<int>, vector<bool>&);
    //set<int> DFSWithSCC(int, vector<bool>&);
    void DFSWithSCC(int, vector<bool>&);

};


#endif //PROJECT1_STARTER_CODE_GRAPH_H
