//
// Created by Student on 10/9/21.
//

#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H
#include <map>
#include "Relation.h"

class Database {
private:
map<string, Relation* > theDatabase;
public:
    Database(){
        //theDatabase =  map<string, relations>();
    }
    map<string, Relation*> getDatabase(){return theDatabase;}

    Relation* getValue(const string& key) {
        return theDatabase.at(key);
    }
    void setValue(const string key, Relation* relation){
        theDatabase.insert(pair<string,Relation*>(key,relation) );
        //theDatabase[key] = relation;
    }

};

#endif //PROJECT1_STARTER_CODE_DATABASE_H
