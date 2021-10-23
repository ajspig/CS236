//
// Created by Student on 10/9/21.
//

#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H
#include <vector>
#include <sstream>


using namespace std;
class Header {
//vector of attributes, strings
private:
    vector <string> attributes;
public:
    Header(vector <string> attr){ attributes = attr;}
    vector <string> getAttributes(){
        return attributes;
    }
    void setAttributes(vector <string> newAttributes){
        attributes = newAttributes;
    }
    string toString() { //should this just print out the header?
        ostringstream output;
        for(unsigned int i =0; i < attributes.size(); ++i){
            output << attributes.at(i) << " " << endl;
        }
        return output.str();
    }
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
