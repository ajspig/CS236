//
// Created by Abigail Spigarelli on 11/30/21.
//

#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

graph::graph(map<int, set<int>> mapWithHeadPredicates) {
    mapOfEdges = mapWithHeadPredicates;
}

void graph::addEdge(int key, int newEdge){
    //grab the set in the mapOfEdges corresponding to the key
    //add the newedge to the set
    //then
    map<int,set<int>>::iterator it;
    set<int> setToChange = mapOfEdges.at(key);
    setToChange.insert(newEdge);
    it = mapOfEdges.find(key);

   if (it != mapOfEdges.end()) {
       it->second = setToChange;
   }

    //find the key in the graph
    //add newEdge to my associated set of ints
}
//vector<set<int>> graph::depthFirstSearchForest(map<int, set<int>>) {
//    //forest := empty
//    //for each vertex v in G (so does that mean for each rule?)
//        //clear the visit mark for v
//    //make my visit markers
//    //vector of bools
//    //should be the same size as teh number of rules
//    // for each vertex v in G
//    //if v is not marked
//        //tree := DepthFirstSearch(v)
//        //add tree to forest
//}

//vector<set <int>> graph::postOrder() {
//    vector<set <int>>
//    //we are updating postorder based off reverse graph
//}

void graph::DFS(int key, set<int> adjList, vector<bool>& listOfMarkers) {
    listOfMarkers.at(key) = true; //mark rule/node/key as visited
    //for(unsigned int i = 0; i < adjList.size(); ++i){     //for each adjacent node in set of ints
    for(set<int>::iterator it = adjList.begin(); it != adjList.end(); ++it){
        // we are checking the wrong place in our list of markers
        // instead we want to check our mapOfEdges for the matching value in our adjList
        // adjList.at(i) thats what we want to check
        if(listOfMarkers.at(*it) != true)//if !visited || if int in marker == false
            DFS(*it, mapOfEdges.find(*it)->second, listOfMarkers); //DFS(int)
        //add node to post order stack
    }
    topologialSort.push(key);
    //can I push the iterator here too? becuase what if it never enters the for loop?
}

void graph::DFSWithSCC(int rule, vector<bool> & listOfMarkers) {
    //set<int> SCCToReturn;
    set<int> adjList = mapOfEdges.find(rule)->second;
    //need to mark the node as visited
    listOfMarkers.at(rule) = true;
    for(set<int>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
        if(!listOfMarkers.at(*it)) //if !visited
            // I want to insert the values in my SCCToReturn into the current functions SCCToReturn
            //everytime I run it, it is updating itself with new values
            //when I instead just want it to
            DFSWithSCC(*it,listOfMarkers);
            //I don't think this is right because it is just going to set everything to that new SCC
            //one solution to this is to make it a private datamember and update it there
    }
    SCC.insert(rule);
    //is this right?

    //return SCCToReturn;
}

//void graph::addSCC(set<int> newSCC){
//
//    for(set<int>::iterator it = newSCC.begin(); it != newSCC.end(); ++it) {
//        newSCC.insert()
//
//    }
//}

string graph::toString() {
    ostringstream output;
    //going to loop through the map based of mapOfEdges.size() not sure if that is right
    for(unsigned int i =0; i < mapOfEdges.size(); i++){
        output << "R" << i << ":";
        //we then want to loop through the set that is associated with that index
        // and print out each of the ints in the set.
        map<int,set<int>>::iterator it;
        unsigned int size = 0;
        for(int rule : mapOfEdges.find(i)->second){
            output << "R" << rule;
            if(size != mapOfEdges.find(i)->second.size()-1){
                output << ",";
            }
            ++size;
        }
//        for(unsigned int j =0; j < it->second.size(); j++){
//            output << "R" << it->second.at(j);
//            if(j != it->second.size() -1){
//                output << ",";
//            }
//        }
        output << endl;
    }

    return output.str();
}

