//
// Created by Student on 10/9/21.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>
#include <map>

class Relation {
private:
    set<Tuple> setOfTuples;
    string theName;
    Header* theHeader; //should this be a pointer?

public:
    Relation(string name, Header* header );

    Relation* select(unsigned int index, string value);
    Relation* select(int indexFirst, int indexSecond);
    Relation* project(vector<int> columnsToKeep);

    Relation* rename(Header *header);
    Header* combineHeader(Header* one, Header* two);
    bool isJoinable(Tuple one, Tuple two, map<int, int> indexForOverlap); //also pass in where supposed to match
    bool unionWithDatabase(Relation*);
    Tuple combineTuples(Tuple, Tuple, map<int, int>);
    Tuple intersectionOfTuples(Tuple, Tuple);
    Relation* naturalJoin(Relation* relationOne);

    string toString();
    string toStringForRules();
    void setName(string name);
    string getName(){ return theName;}
    void setHeader(Header* header);
    Header* getHeader();
    void addTuple(Tuple tupleToAdd);
    void addTupleSet(set<Tuple> newTuples);

    set<Tuple> getTuples() const;

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
