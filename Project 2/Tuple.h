//
// Created by Student on 10/9/21.
//

#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H
#include <string>
#include <vector>
#include <sstream>

using namespace std;


class Tuple {
private:
    vector <string> theValues;
public:
    Tuple(vector<string> values){theValues = values;}
    bool operator< (const Tuple &other) const {
        return theValues < other.theValues;
    }
    vector <string> getValues() const{
        return theValues;
    }
    void setValues(vector <string> newValues){
        theValues = newValues;
    }
    string toString() {
        ostringstream output;
        for(unsigned int i =0; i < theValues.size(); ++i){
            output << theValues.at(i) << " " << endl;
        }
        return output.str();
    }

};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
