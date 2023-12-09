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

bool isPrime(int num){
    if(num < 2){
        return false;
    }
    if(num == 2 || num == 3){
        return true;
    }
    for(int i = 2; i <= std::sqrt(num); i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

bool isPrime(unsigned int num){
    if(num < 2){
        return false;
    }
    if(num == 2 || num == 3){
        return true;
    }
    for(int i = 2; i <= std::sqrt(num); i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

bool isPrime(long long int num){
    if(num < 2){
        return false;
    }
    if(num == 2 || num == 3){
        return true;
    }
    for(int i = 2; i <= std::sqrt(num); i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

std::vector<int> getFactors(long long int num){
    std::vector<int> factorList;
    if(num == 0){
        factorList = {0};
        return factorList;
    }
    if(num < 0){
        factorList.push_back(-1);
        num *= -1;
    }
    if(isPrime(num)){
        factorList.push_back(num);
        return factorList;
    }
    for(int i = 2; i <= num; i++){
        if(num % i == 0){
            factorList.push_back(i);
            num /= i;
            break;
        }
    }
    std::vector<int> newFactors = getFactors(num);
    factorList.insert(factorList.end(), newFactors.begin(), newFactors.end());
    return factorList;
}

long long int leastCommonMultiple(const std::vector<int> &nums){
    std::unordered_map<int, int> factorCounts;
    for(int i = 0; i < nums.size(); i++){
        auto factors = getFactors(nums[i]);
        std::unordered_map<int, int> tempFactorCounts;
        for(int j = 0; j < factors.size(); j++){
            if(tempFactorCounts.find(factors[j]) == tempFactorCounts.end()){
                tempFactorCounts[factors[j]] = 1;
            }
            else{
                tempFactorCounts[factors[j]]++;
            }
        }
        for(auto x: tempFactorCounts){
            if(factorCounts.find(x.first) == factorCounts.end()){
                factorCounts[x.first] = x.second;
            }
            else if(factorCounts.at(x.first) < x.second){
                factorCounts[x.first] = x.second;
            }
        }
    }

    long long int lcm = 1;
    for(auto x: factorCounts){
        for(int i = 0; i < x.second; i++){
            lcm *= x.first;
        }
    }
    return lcm;
}