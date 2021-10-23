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
    //recommended to not use pointers for select, project and rename functions

    Relation select(int index, string value){
        Relation relation(theName, theHeader); //make an empty relation
        //fill the relation
        //return the relation
        //• select: parameters are index and value (relation column and value to select)
        //what changes after select? number of tuples
        //number of columns and what the scheme says stay the same
        //need to know what column to check for and what value should be in the column
        //or what two columns are supposed to have the same value

        //columns are indexed by number
        //column&int is an int and a string two columns is two ints
        return relation;
    }
    Relation select(int indexFirst, int indexSecond){
        Relation relation(theName, theHeader); //make an empty relation

        return relation;
    }
    Relation project(vector<int> columnsToKeep) { //ints for project
        Relation relation(theName, theHeader); //make an empty relation
        //• project: parameter is list of indices (the columns to keep)

        return relation;
    }
    //advise that it is a vector or columns to keep
    //a whole new header
    Relation rename(Header *header) {  //strings for rename
        Relation relation(theName, header); //make an empty relation
        //• rename: parameter is list of attributes (defines the new header)
        return relation;
    }

    string toString() {
        ostringstream output;
        for(Tuple t:setOfTuples ){
            output << t.toString() << theHeader->toString() << endl;
        }
        //okay this is for sure not right
        //becuase I think this will just print out all the attributes and then all teh headers
        //when really I want header = 'attribute'
        return output.str();
    }
    void setName(string name){ theName = name;}
    void setHeader(Header* header){ theHeader = header;}
    void addTuple(Tuple tupleToAdd){ setOfTuples.insert(tupleToAdd);}

    set<Tuple> getTuples() const {return setOfTuples;};

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
