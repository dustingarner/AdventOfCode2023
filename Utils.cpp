#include "Utils.h"

int char_to_int(char num){
    return num - 48;
}

int getStartInd(const std::string &row, int ind){
    int startInd = 0;
    for(int i = ind; i >= 0; i--){
        if(isdigit(row[i])){
            startInd = i;
        }
        else{
            break;
        }
    }
    return startInd;
}

int getEndInd(const std::string &row, int ind){
    int endInd = ind;
    for(int i = ind; i < row.length(); i++){
        if(isdigit(row[i])){
            endInd = i;
        }
        else{
            break;
        }
    }
    return endInd;
}

int getNumber(const std::string &row, int ind){
    int startInd = getStartInd(row, ind);
    int endInd = getEndInd(row, ind);
    int num = 0;
    int multiplier = 1;
    for(int i = endInd; i >= startInd; i--){
        char character = row[i];
        num += char_to_int(character) * multiplier;
        multiplier *= 10;
    }
    return num;
}

unsigned int getUNumber(const std::string &row, int ind){
    int startInd = getStartInd(row, ind);
    int endInd = getEndInd(row, ind);
    unsigned int num = 0;
    int multiplier = 1;
    for(int i = endInd; i >= startInd; i--){
        char character = row[i];
        num += char_to_int(character) * multiplier;
        multiplier *= 10;
    }
    return num;
}

long long int getLongNumber(const std::string &row, int ind){
    int startInd = getStartInd(row, ind);
    int endInd = getEndInd(row, ind);
    long long int num = 0;
    long long int multiplier = 1;
    for(int i = endInd; i >= startInd; i--){
        char character = row[i];
        num += char_to_int(character) * multiplier;
        multiplier *= 10;
    }
    return num;
}