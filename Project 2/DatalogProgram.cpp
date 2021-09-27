//
// Created by Abigail Spigarelli on 9/22/21.
//

#include "DatalogProgram.h"
#include <sstream>
#include <set>


//BELOW ALL FROM PARSER
DatalogProgram::DatalogProgram(){
    //create a function to start the parsing
    //do I even need my parse() function?

}
string DatalogProgram::datalogProgramToString() {
    ostringstream output;

    output << "Schemes(" << vectorOfSchemes.size() << "):" << endl;
    for(unsigned int i =0; i < vectorOfSchemes.size(); i++){
        output << "  " << vectorOfSchemes.at(i)->getParameterType() << "(";
        output << vectorOfSchemes.at(i)->predicateToString() << ")" << endl;
        //my token description is not being set correctly
    }
    output << "Facts(" << vectorOfFacts.size() << "):" << endl;
    for(unsigned int i =0; i < vectorOfFacts.size(); i++){
        output << "  " << vectorOfFacts.at(i)->getParameterType() << "(";
        output << vectorOfFacts.at(i)->predicateToString() << ")." << endl;
    }
    if(vectorOfRules.size()>0){
        output << "Rules(" << vectorOfRules.size() << "):" << endl;
        for(unsigned int i =0; i < vectorOfRules.size(); i++){
            output << "  " << vectorOfRules.at(i)->ruleToString();
        }
    }else{
        output << "Rules(0):" << endl;

    }
    if(predForRules.size()>0){
        output << "Queries(" << predForRules.size() << "):" << endl;
        for(unsigned int i =0; i < predForRules.size(); i++){
            output << "  " << predForRules.at(i)->getParameterType() << "(";
            output << predForRules.at(i)->predicateToString() << ")?" << endl;
        }
    }

output << "Domain(";
    output << domain.size() << "):" << endl;
    set<string>::iterator it = domain.begin();
    //while (it != domain.end()){
    for(it = domain.begin(); it != domain.end();it++){
        output << "  " << (*it) << endl;

    }
        return output.str();

}
string DatalogProgram::getFailedToken() {
    return tokenFailedOn;
}

void DatalogProgram::parseSyntax(vector<Token*>* tokens){
    parserTokens = tokens;
    parseDatalogProgram();
    //this is what is going to except the vector of tokens
}
bool DatalogProgram::getSyntaxCheck() {
    return syntaxCheck;
}
void DatalogProgram::easyMatching(TokenType tokenToCompare) {

    if(parserTokens->at(index)->getType() == tokenToCompare){
        index++;
    }else {
        //tokenInParser->toString();
        throw parserTokens->at(index)->toString();
    }
}

//datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
void DatalogProgram::parseDatalogProgram() {
    index = 0;
    try {
        easyMatching(TokenType::SCHEMES);
        easyMatching(TokenType::COLON);
        parseScheme();
        parseSchemeList();
        easyMatching(TokenType::FACTS);
        easyMatching(TokenType::COLON);
        parseFactList();
        easyMatching(TokenType::RULES);
        easyMatching(TokenType::COLON);
        parseRuleList();
        easyMatching(TokenType::QUERIES);
        easyMatching(TokenType::COLON);
        parseQuery();
        parseQueryList();
        easyMatching(TokenType::EOF_TYPE);

    }catch(string tokenThrown){

        syntaxCheck = false;
        tokenFailedOn = tokenThrown;

        //print failure because token was thrown
    }
}
//schemeList	->	scheme schemeList | lambda
void DatalogProgram::parseSchemeList(){
    if(parserTokens->at(index)->getType() == TokenType::FACTS){
        //lambda
        //do nothing
    }else{
        parseScheme();
        parseSchemeList(); //recursion!!!
    }
}
//factList	->	fact factList | lambda
void DatalogProgram::parseFactList(){
    if(parserTokens->at(index)->getType() == TokenType::RULES) {
        //lambda
        //do nothing
    }else{
        parseFact();
        parseFactList();
    }
    //return vectorOfFacts;
}
//ruleList	->	rule ruleList | lambda
void DatalogProgram::parseRuleList(){
    if(parserTokens->at(index)->getType() == TokenType::QUERIES) {
        //lambda
        //do nothing
    }else{
        parseRule();
        parseRuleList();
    }
    //return vectorOfRules;
}
//queryList	->	query queryList | lambda
void DatalogProgram::parseQueryList(){
    if(parserTokens->at(index)->getType() == TokenType::EOF_TYPE) {
        //lambda
        //do nothing
    }else{
        parseQuery();
        //++index; //uncommented at Sep 25
        parseQueryList();
    }
    //return vectorOfQueries;
}
//scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
void DatalogProgram::parseScheme(){
    try {
        easyMatching(TokenType::ID);
        //declare idVal to be the part of the string ID
        string idVal = parserTokens->at(index-1)->getDescript();
        easyMatching(TokenType::LEFT_PAREN);

        //for each of the following IDs push onto a vector of parameter objects
        easyMatching(TokenType::ID);
        vectorOfParam.push_back(new Parameter(parserTokens->at(index-1)->getDescript()));

        parseIdList();//this needs to return a vector of parameters
        easyMatching(TokenType::RIGHT_PAREN);
        //we want to create a new predicate and push it on the back of vectorOfSchemes
        vectorOfSchemes.push_back(new Predicate(idVal, vectorOfParam)); //add newToken to collection of all tokens
        vectorOfParam.clear();
        //return my vector of Schemes?
        //I actually dont think I need to return anything since I have the vectorOfParam
    }catch(Token& tokenThrown){
        syntaxCheck = false;

        tokenThrown.toString();
        //print failure because token was thrown
    }

}
//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void DatalogProgram::parseFact(){
    try {
        easyMatching(TokenType::ID);
        string idVal = parserTokens->at(index-1)->getDescript();
        easyMatching(TokenType::LEFT_PAREN);
        easyMatching(TokenType::STRING);
        vectorOfParam.push_back(new Parameter(parserTokens->at(index-1)->getDescript()));
        parseStringList();
        easyMatching(TokenType::RIGHT_PAREN);
        easyMatching(TokenType::PERIOD);
        vectorOfFacts.push_back(new Predicate(idVal, vectorOfParam)); //add newToken to collection of all tokens
        for(unsigned int i=0; i <vectorOfParam.size(); i++){
            domain.insert(vectorOfParam.at(i)->parameterToString());
        }
            vectorOfParam.clear();
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //need to add the bool statement
        //print failure because token was thrown
    }
}
//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
void DatalogProgram::parseRule() {
    try {
        parseHeadPredicate(); //in here I need to make sure I set headPreddy to headPred for rules
        easyMatching(TokenType::COLON_DASH);
        parsePredicate();

        parsePredicateList();
        //after we are done parsing all the predicates on to Pred for rules
        //we can push it onto the vector of Rules

        easyMatching(TokenType::PERIOD);
        vectorOfRules.push_back(new Rule(headPredForRules,predForRules)); //add newToken to collection of all tokens
        predForRules.clear();
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//query	        ->      predicate Q_MARK
void DatalogProgram::parseQuery(){
    parsePredicate();
    easyMatching(TokenType::Q_MARK);
}
//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
void DatalogProgram::parseHeadPredicate(){
    try {
        easyMatching(TokenType::ID);
        //declare idVal to be the part of the string ID
        string idVal = parserTokens->at(index-1)->getDescript();
        easyMatching(TokenType::LEFT_PAREN);
        easyMatching(TokenType::ID);
        vectorOfParam.push_back(new Parameter(parserTokens->at(index-1)->getDescript()));
        parseIdList();
        easyMatching(TokenType::RIGHT_PAREN);
        //want to be able to save the head predicate as its own predicate
        headPredForRules = new Predicate(idVal, vectorOfParam);

        vectorOfParam.clear();
        //this is were we push the vector of predicates onto the
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void DatalogProgram::parsePredicate(){
    try {
        easyMatching(TokenType::ID);
        string rulePredicateID = parserTokens->at(index-1)->getDescript();
        easyMatching(TokenType::LEFT_PAREN);
        parseParameter();//I am pretty sure everything that follows should just be treated as a normal scheme
        parseParameterList();
        //we have now gone through all the parameters in the predicate and we can push the predicate on to the predicate of rules
        predForRules.push_back(new Predicate(rulePredicateID,vectorOfParam));
        //predForQueries for Queries
        vectorOfParam.clear();

        easyMatching(TokenType::RIGHT_PAREN);

    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//predicateList	->	COMMA predicate predicateList | lambda
void DatalogProgram::parsePredicateList(){
    if (parserTokens->at(index)->getType() == TokenType::PERIOD) {
        //lambda
    } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
        ++index;
        //this is where I push the rest of them on
        parsePredicate();
        parsePredicateList();
    }
}
//parameterList	-> 	COMMA parameter parameterList | lambda
void DatalogProgram::parseParameterList(){
    if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
        //lambda
    } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
        ++index;
        parseParameter();
        //do I push vector of parameters onto predicate here
        //predForRules.push_back(vectorOfParam);
        parseParameterList();

    } else { throw (parserTokens->at(index)->toString()); }


}
//stringList	-> 	COMMA STRING stringList | lambda
void DatalogProgram::parseStringList() {
    if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
        //lambda
    } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
        ++index; //advance the input
        easyMatching(TokenType::STRING);
        vectorOfParam.push_back(new Parameter(parserTokens->at(index-1)->getDescript()));

        parseStringList();
    } else { throw (parserTokens->at(index)->toString()); }
}
//idList  	-> 	COMMA ID idList | lambda
void DatalogProgram::parseIdList(){
    //parserTokens->
    if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
        //checking the follow set
        //lambda
        //simply do nothing <3
    } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
        ++index; //advance the input
        easyMatching(TokenType::ID);
        //Parameter otherID = Parameter(parserTokens->at(index-1)->getDescript());
        //vectorOfParam.push_back(&otherID);
        vectorOfParam.push_back(new Parameter(parserTokens->at(index-1)->getDescript()));
        //add to vector of parameters
        parseIdList();
    }
}
//parameter	->	STRING | ID
void DatalogProgram::parseParameter(){
    if (parserTokens->at(index)->getType() == TokenType::STRING) {
        vectorOfParam.push_back(new Parameter(parserTokens->at(index)->getDescript()));
        ++index;
    } else if (parserTokens->at(index)->getType() == TokenType::ID) {
        vectorOfParam.push_back(new Parameter(parserTokens->at(index)->getDescript()));
        ++index;
        //do I need two separate statements or can they just be the same if statement with an or
    }
}