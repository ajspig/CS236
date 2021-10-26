//
// Created by Student on 10/9/21.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>

class Relation {
private:
    set<Tuple> setOfTuples;
    string theName;
    Header* theHeader; //should this be a pointer?

public:
    Relation(string name, Header* header ){
        theName = name;
        theHeader = header;
    }

    Relation* select(int index, string value){
        Relation* relation = new Relation(theName, theHeader); //make an empty relation
        set<Tuple> newSetOfTuples;
        vector<string> vectorForHeader;
        for(Tuple t:setOfTuples ){
            if(t.getValues().at(index) == value){
//                vector <string> newTuple;
//                for(int j =0; j <t.getValues().size(); j++){
//                    if(j!=index){
//                        newTuple.push_back(t.getValues().at(j));
//                        vectorForHeader.push_back(theHeader->getAttributes().at(j));
//                    }
//                }
                //create a new tuple without the tuple that matches the index
                newSetOfTuples.insert( Tuple(t));
            }
        }
        vector <int> vectorForProject;
        for(unsigned int i =0; i < theHeader->getAttributes().size(); i++){
            if(i != index)
            vectorForProject.push_back(i);
        }

        //relation->setHeader(new Header(vectorForHeader));
        relation->addTupleSet(newSetOfTuples);
        relation->project(vectorForProject);

        return relation;
    }
    Relation* select(int indexFirst, int indexSecond){
        Relation* relation = new Relation(theName, theHeader); //make an empty relation
        set<Tuple> newSetOfTuples;
        for(Tuple t:setOfTuples ){
            //for each of the tuples grab the values that match the vector index of indexFirst and indexSecond
            //if they do match add them to a new set of tuples
            if(t.getValues().at(indexFirst) == t.getValues().at(indexSecond)){
                newSetOfTuples.insert(t);
            }
        }
        relation->addTupleSet(newSetOfTuples);

        return relation;
    }
    Relation* project(vector<int> columnsToKeep) { //ints for project
        Relation* relation = new Relation(theName, theHeader); //make an empty relation
        //• project: parameter is list of indices (the columns to keep)
        //we want newHeader
        //make a vector of strings for newHeader and then declare newHeader with them
        vector<string> forNewHeader;
        for(unsigned int i = 0; i < columnsToKeep.size(); i++){
            //for each int in columnsToKeep grab the associated column in theHeader and add it to newHeader
            forNewHeader.push_back(theHeader->getAttributes().at(columnsToKeep.at(i)));
            //forNewHeader.push_back(theHeader->getAttributes().at(i));

        }
        //for each tuple in relation make a new tuple that is only the incices of corresponding columns we are keeping
        set<Tuple> newSetOfTuples;
        //make a vector of strings for the new tuple and then create the set<tuple> of f that
    //TODO: below is the error
        for(Tuple t:setOfTuples ) {
            vector<string> newTupleVector;
            for( unsigned int i =0; i < columnsToKeep.size(); i++) {
                newTupleVector.push_back(t.getValues().at(columnsToKeep.at(i)));
                //make a new vector in here
                //we want to make a straight up new tuple
            }
            t.setValues(newTupleVector);
            newSetOfTuples.insert(t);
        }
        relation->addTupleSet(newSetOfTuples);
            //we will want to do the same thing for all of the tuples in our relation
        Header* newHeader = new Header(forNewHeader);
        //also move the new relation line here and make a new relation with my theHeader
        //theHeader = newHeader;
        relation->setHeader(newHeader);
        return relation;
    }

    Relation* rename(Header *header) {  //strings for rename
        Relation* relation = new Relation(theName, header); //make an empty relation
        //also add the tuples to the relation
        relation->addTupleSet(setOfTuples);
        //• rename: parameter is list of attributes (defines the new header)
        return relation;
    }

    string toString() {
        ostringstream output;
        //if setOftuples.size() >0 print "Yes" followed by setofTuples.size()
        if(setOfTuples.empty()){
            output << "No" <<endl;
        }else{
            output << "Yes(" << setOfTuples.size() << ")" <<endl << " ";
        }
        if(!theHeader->getAttributes().empty()) {
            for (Tuple t: setOfTuples) {
                for (unsigned int i = 0; i < theHeader->getAttributes().size(); i++) {
                    output << " " << theHeader->getAttributes().at(i) << "=" << t.getValues().at(i);
                    if(i!=theHeader->getAttributes().size()-1){
                        output << ",";
                    }
                }
                output << endl << " ";
            }
        }
        return output.str();
    }
    void setName(string name){ theName = name;}
    void setHeader(Header* header){ theHeader = header;}
    Header* getHeader(){return theHeader;}
    void addTuple(Tuple tupleToAdd){ setOfTuples.insert(tupleToAdd);}
    void addTupleSet(set<Tuple> newTuples){setOfTuples = newTuples;}

    set<Tuple> getTuples() const {return setOfTuples;};

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
