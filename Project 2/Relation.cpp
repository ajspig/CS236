//
// Created by Student on 10/9/21.
//

#include "Relation.h"
#include <iostream>


Relation::Relation(string name, Header *header) {
    theName = name;
    theHeader = header;
}

void Relation::setName(string name) { theName = name; }

void Relation::setHeader(Header *header) { theHeader = header; }

Header *Relation::getHeader() { return theHeader; }

void Relation::addTuple(Tuple tupleToAdd) { setOfTuples.insert(tupleToAdd); }

void Relation::addTupleSet(set<Tuple> newTuples) { setOfTuples = newTuples; }

set<Tuple> Relation::getTuples() const { return setOfTuples; }

Relation *Relation::select(unsigned int index, string value) {
    Relation *relation = new Relation(theName, theHeader); //make an empty relation
    set<Tuple> newSetOfTuples;
    vector<string> vectorForHeader;
    for (Tuple t: setOfTuples) {
        if (t.getValues().at(index) == value) {
            newSetOfTuples.insert(Tuple(t));
        }
    }
    vector<int> vectorForProject;
    for (unsigned int i = 0; i < theHeader->getAttributes().size(); i++) {
        if (i != index)
            vectorForProject.push_back(i);
    }

    relation->addTupleSet(newSetOfTuples);
    relation->project(vectorForProject);

    return relation;
}

Relation *Relation::select(int indexFirst, int indexSecond) {
    Relation *relation = new Relation(theName, theHeader); //make an empty relation
    set<Tuple> newSetOfTuples;
    for (Tuple t: setOfTuples) {
        //for each of the tuples grab the values that match the vector index of indexFirst and indexSecond
        //if they do match add them to a new set of tuples
        if (t.getValues().at(indexFirst) == t.getValues().at(indexSecond)) {
            newSetOfTuples.insert(t);
        }
    }
    relation->addTupleSet(newSetOfTuples);

    return relation;
}

Relation *Relation::project(vector<int> columnsToKeep) { //ints for project
    Relation *relation = new Relation(theName, theHeader); //make an empty relation
    //• project: parameter is list of indices (the columns to keep)
    //we want newHeader
    //make a vector of strings for newHeader and then declare newHeader with them
    vector<string> forNewHeader;
    for (unsigned int i = 0; i < columnsToKeep.size(); i++) {
        //for each int in columnsToKeep grab the associated column in theHeader and add it to newHeader
        forNewHeader.push_back(theHeader->getAttributes().at(columnsToKeep.at(i)));
        //forNewHeader.push_back(theHeader->getAttributes().at(i));

    }
    //for each tuple in relation make a new tuple that is only the incices of corresponding columns we are keeping
    set<Tuple> newSetOfTuples;
    //make a vector of strings for the new tuple and then create the set<tuple> of f that
    for (Tuple t: setOfTuples) {
        vector<string> newTupleVector;
        for (unsigned int i = 0; i < columnsToKeep.size(); i++) {
            newTupleVector.push_back(t.getValues().at(columnsToKeep.at(i)));
            //make a new vector in here
            //we want to make a straight up new tuple
        }
        t.setValues(newTupleVector);
        newSetOfTuples.insert(t);
    }
    relation->addTupleSet(newSetOfTuples);
    //we will want to do the same thing for all of the tuples in our relation
    Header *newHeader = new Header(forNewHeader);
    //also move the new relation line here and make a new relation with my theHeader
    //theHeader = newHeader;
    relation->setHeader(newHeader);
    return relation;
}

Relation *Relation::rename(Header *header) {  //strings for rename
    Relation *relation = new Relation(theName, header); //make an empty relation
    //also add the tuples to the relation
    relation->addTupleSet(setOfTuples);
    //• rename: parameter is list of attributes (defines the new header)
    return relation;
}
Tuple Relation::combineTuples(Tuple one, Tuple two, map<int, int> indexOfHeaderToConnect){
    vector<string> vectorForCombinedTuple = one.getValues();
    map<int, int>::iterator it;
    bool unique;
    for(unsigned int i =0; i < two.getValues().size(); i ++){
        unique = true;
        for (it = indexOfHeaderToConnect.begin(); it != indexOfHeaderToConnect.end(); it++) {
                if(i == it->second){
                    unique = false;
                }
            }
        if(unique){
            vectorForCombinedTuple.push_back(two.getValues().at(i));
        }

    }
//        if (one.getValues().at(it->first) == two.getValues().at(it->second)) {
//            unique = true;
//            //break;
//        }

        //could do while( i != it->second)
            //vectorForCombinedTuple.push_back(two.getValues().at(i)
            //i++



    Tuple newSetOfTuples = vectorForCombinedTuple;
    return newSetOfTuples;
}
Header* Relation::combineHeader(Header *one, Header *two) {
    vector<string> newHeaderAttr = one->getAttributes();
    bool unique = true;
    for (unsigned int i = 0; i < two->getAttributes().size(); i++) {
        for (unsigned int j = 0; j < one->getAttributes().size(); j++) {
            if (two->getAttributes().at(i) == one->getAttributes().at(j)) {
                unique = false;
                break;
            }
        }
        if (unique) {
            newHeaderAttr.push_back(two->getAttributes().at(i));
        }
        unique = true;

    }
    Header *newHeader = new Header(newHeaderAttr);

    return newHeader;
}

bool Relation::isJoinable(Tuple one, Tuple two, map<int, int> indexForOverlap) {
    map<int, int>::iterator it;
    bool doesItMatch = false;

    for (it = indexForOverlap.begin(); it != indexForOverlap.end(); it++) {
        if (one.getValues().at(it->first) == two.getValues().at(it->second)) {
            doesItMatch = true;
            //break;
        }

    }

    //also need to pass in where they are supposed to match
    return doesItMatch;
}

///Pass one relation into the function called by the other relation you want to union.
bool Relation::unionWithDatabase(Relation *relationWeUpdateWith) {
    //the relation we are inside of = database relation
    //the relation that is a parameter = result of rule evaluation
    //add the tuples of one relation to the other relations set of tuples
    //add a tuple to a set
    //inserting new tuples into relation
    bool wasTupleInserted = false;
    string printable;

    for (Tuple t: relationWeUpdateWith->getTuples()) {
        //loop through all the tuples and add them to the main relation's data members
        //when adding a tuple from rule evaluation to database check if it already existed
        if (setOfTuples.insert(t).second) {
            //if true if new element was inserted
            //print the new tuple out
            printable += t.toString();
            for(unsigned int i =0; i < relationWeUpdateWith->getHeader()->getAttributes().size(); i++){
                cout << relationWeUpdateWith->getHeader()->getAttributes().at(i) << "=" << t.getValues().at(i);
                if (i != theHeader->getAttributes().size() - 1) {
                    cout << ",";
                }
            }
            cout << endl;
            wasTupleInserted = true;
        }

        //if no tuple is inserted update to true;
    }
    return wasTupleInserted;

}

Relation *Relation::naturalJoin(Relation *relationOne) {
    map<int, int> mapOfCommonColumns;

    //make a map that is full of the connections between the two relations
    //do a for loop through both headers and if they match put the indexes into a map

    for (unsigned int i = 0; i < relationOne->getHeader()->getAttributes().size(); i++) {
        for (unsigned int j = 0; j < theHeader->getAttributes().size(); j++) {
            if (relationOne->getHeader()->getAttributes().at(i) == theHeader->getAttributes().at(j)) {
                mapOfCommonColumns.insert(pair<int, int>(j, i));
                break;
            }
        }
    }


    Header *combinedHeader = combineHeader(theHeader, relationOne->getHeader());
    Relation *combinedRelation = new Relation(theName, combinedHeader);
    //for tuple in databaseRelation
    //for tuple in relationOne

    for (Tuple p: setOfTuples) {
        for (Tuple t: relationOne->getTuples()) {

            if(!mapOfCommonColumns.empty()) {
                if (isJoinable(p, t, mapOfCommonColumns)) {
                    //if they are joinable add them to the tuples for the combinedRelation
                    Tuple combinedTuple = combineTuples(p, t, mapOfCommonColumns);
                    //first combine the tuples
                    combinedRelation->addTuple(combinedTuple);
                    //then add the new combined tuple to vector of tuples for the combinedRelation
                }
            }else{
                vector<string> vectorForCombinedTuple = p.getValues();
                for (unsigned int j = 0; j < t.getValues().size(); j++) {
                    vectorForCombinedTuple.push_back(t.getValues().at(j));
                }
                Tuple combinedTuple = vectorForCombinedTuple;
                combinedRelation->addTuple(combinedTuple);
            }
//not quite right because my relation isnt correct when it comes to me and my vector isnt quite right becuase of this
//////TODODODODOD todo you got this queen
        }
    }
    return combinedRelation;
}
string Relation::toStringForRules() {
    ostringstream output;
    if (!theHeader->getAttributes().empty()) {
        for (Tuple t: setOfTuples) {
            output << "  ";
            for (unsigned int i = 0; i < theHeader->getAttributes().size(); i++) {
                output << theHeader->getAttributes().at(i) << "=" << t.getValues().at(i);
                if (i != theHeader->getAttributes().size() - 1) {
                    output << ",";
                }
            }
            output << endl;
        }
    }
    return output.str();
}

string Relation::toString() {
    ostringstream output;
    //if setOftuples.size() >0 print "Yes" followed by setofTuples.size()
    if (setOfTuples.empty()) {
        output << "No" << endl;
    } else {
        output << "Yes(" << setOfTuples.size() << ")" << endl;
    }
    if (!theHeader->getAttributes().empty()) {
        for (Tuple t: setOfTuples) {
            output << "  ";
            for (unsigned int i = 0; i < theHeader->getAttributes().size(); i++) {
                output << theHeader->getAttributes().at(i) << "=" << t.getValues().at(i);
                if (i != theHeader->getAttributes().size() - 1) {
                    output << ",";
                }
            }
            output << endl;
        }
    }
    return output.str();
}
