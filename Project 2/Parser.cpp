//
// Created by Abigail Spigarelli on 9/18/21.
//

#include "Parser.h"

Parser::Parser(){
    //create a function to start the parsing
    //do I even need my parse() function?

}
string Parser::getFailedToken() {
    return tokenFailedOn;
}

void Parser::parseSyntax(vector<Token*>* tokens){
    parserTokens = tokens;
    parseDatalogProgram();
    //this is what is going to except the vector of tokens
}
bool Parser::getSyntaxCheck() {
    return syntaxCheck;
}
void Parser::easyMatching(TokenType tokenToCompare) {

    if(parserTokens->at(index)->getType() == tokenToCompare){
        index++;
    }else {
        //tokenInParser->toString();
        throw parserTokens->at(index)->toString();
    }
}

//datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
void Parser::parseDatalogProgram() {
    index = 0;
    try {
        easyMatching(TokenType::SCHEMES);
        easyMatching(TokenType::COLON);
        parseScheme();
        parseSchemelist();
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
void Parser::parseSchemelist(){
    if(parserTokens->at(index)->getType() == TokenType::FACTS){
        //lambda
        //do nothing
    }else{
        parseScheme();
        //index++;
        parseSchemelist(); //recursion!!!
    }
}
//factList	->	fact factList | lambda
void Parser::parseFactList(){
    if(parserTokens->at(index)->getType() == TokenType::RULES) {
        //lambda
        //do nothing
    }else{
        parseFact();
        //index++;
        parseFactList();
    }
}
//ruleList	->	rule ruleList | lambda
void Parser::parseRuleList(){
    if(parserTokens->at(index)->getType() == TokenType::QUERIES) {
        //lambda
        //do nothing
    }else{
        parseRule();
        //++index;
        parseRuleList();
    }
}
//queryList	->	query queryList | lambda
void Parser::parseQueryList(){
    if(parserTokens->at(index)->getType() == TokenType::EOF_TYPE) {
        //lambda
        //do nothing
    }else{
        parseQuery();
        ++index;
        parseQueryList();
    }
}
//scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::parseScheme(){
    try {
        easyMatching(TokenType::ID);
        //the error ocures here because we are one token ahead
        easyMatching(TokenType::LEFT_PAREN);
        easyMatching(TokenType::ID);
        parseIdList();
        easyMatching(TokenType::RIGHT_PAREN);
    }catch(Token& tokenThrown){
        syntaxCheck = false;

        tokenThrown.toString();
        //print failure because token was thrown
    }

}
//fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::parseFact(){
    try {
        easyMatching(TokenType::ID);
        easyMatching(TokenType::LEFT_PAREN);
        easyMatching(TokenType::STRING);
        parseStringList();
        easyMatching(TokenType::RIGHT_PAREN);
        easyMatching(TokenType::PERIOD);
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //need to add the bool statement
        //print failure because token was thrown
    }
}
//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::parseRule() {
    try {
        parseHeadPredicate();
        easyMatching(TokenType::COLON_DASH);
        parsePredicate();
        //++index;//just added 9:34
        parsePredicateList();
        easyMatching(TokenType::PERIOD);
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//query	        ->      predicate Q_MARK
void Parser::parseQuery(){
    parsePredicate();
    easyMatching(TokenType::Q_MARK);
}
//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::parseHeadPredicate(){
    try {
        easyMatching(TokenType::ID);
        easyMatching(TokenType::LEFT_PAREN);
        easyMatching(TokenType::ID);
        parseIdList();
        easyMatching(TokenType::RIGHT_PAREN);
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::parsePredicate(){
    try {
        easyMatching(TokenType::ID);
        easyMatching(TokenType::LEFT_PAREN);
        parseParameter();
        //++index;//this is new
        parseParameterList();
        easyMatching(TokenType::RIGHT_PAREN);
        //parseIdList();
    }catch(Token& tokenThrown){
        tokenThrown.toString();
        //print failure because token was thrown
    }
}
//predicateList	->	COMMA predicate predicateList | lambda
void Parser::parsePredicateList(){
        if (parserTokens->at(index)->getType() == TokenType::PERIOD) {
            //lambda
        } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
            ++index;
            parsePredicate();
            //++index;//this is new
            parsePredicateList();
            //++index; //advance the input
        }
}
//parameterList	-> 	COMMA parameter parameterList | lambda
void Parser::parseParameterList(){
        if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
            //lambda
            //TODO: should this be inside my try catch statement?
        } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
            ++index; //just added 1:33pm
            parseParameter();
            //++index;//just added 1:33pm
            parseParameterList();
            //++index; //advance the input

        } else { throw (parserTokens->at(index)->toString()); }


}
//stringList	-> 	COMMA STRING stringList | lambda
void Parser::parseStringList() {
        if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
            //lambda
            //TODO: should this be inside my try catch statement?
        } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
            ++index; //advance the input
            easyMatching(TokenType::STRING);
            parseStringList();
            } else { throw (parserTokens->at(index)->toString()); }
}
//idList  	-> 	COMMA ID idList | lambda
void Parser::parseIdList(){
    //parserTokens->
        if (parserTokens->at(index)->getType() == TokenType::RIGHT_PAREN) {
            //checking the follow set
            //lambda
            //simply do nothing <3
        } else if (parserTokens->at(index)->getType() == TokenType::COMMA) {
            ++index; //advance the input
            easyMatching(TokenType::ID);
            parseIdList();
        }
}
//parameter	->	STRING | ID
void Parser::parseParameter(){
        if (parserTokens->at(index)->getType() == TokenType::STRING) {
            ++index;
        } else if (parserTokens->at(index)->getType() == TokenType::ID) {
            ++index;
            //do I need two separate statements or can they just be the same if statement with an or
    }
}