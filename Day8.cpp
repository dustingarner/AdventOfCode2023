#include "Utils.h"
#include "Day8.h"


std::string leftRightSteps(std::string fileName){
    std::fstream txtfile;
    txtfile.open(fileName);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            return line;
        }
        txtfile.close();
    }
    return "";
}

std::unordered_map<std::string, std::pair<std::string, std::string>> stepMap(std::string fileName){
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::fstream txtfile;
    txtfile.open(fileName);
    if(txtfile.is_open()){
        std::string line;
        bool firstLine = true;
        while(std::getline(txtfile, line)){
            if(firstLine){
                firstLine = false;
                continue;
            }
            if(line.length() == 0){
                continue;
            }
            std::string key = line.substr(0, 3);
            std::string left = line.substr(7, 3);
            std::string right = line.substr(12, 3);
            map[key] = std::make_pair(left, right);
        }
        txtfile.close();
    }
    return map;
}

std::string startPos(std::string fileName){
    std::fstream txtfile;
    txtfile.open(fileName);
    std::string start;
    if(txtfile.is_open()){
        std::string line;
        bool firstLine = true;
        while(std::getline(txtfile, line)){
            if(firstLine){
                firstLine = false;
                continue;
            }
            if(line.length() == 0){
                continue;
            }
            start = line.substr(0, 3);
            break;
        }
        txtfile.close();
    }
    return start;
}

int findSteps(std::string fileName){
    std::string steps = leftRightSteps(fileName);
    auto map = stepMap(fileName);
    std::string currentLoc = "AAA";

    bool goalFound = false;
    int stepsTaken = 0;
    while(!goalFound){
        for(int i = 0; i < steps.length(); i++){
            if(currentLoc == "ZZZ"){
                goalFound = true;
                return stepsTaken;
            }
            stepsTaken++;
            if(steps[i] == 'L'){
                currentLoc = map[currentLoc].first;
            }
            else if(steps[i] == 'R'){
                currentLoc = map[currentLoc].second;
            }
        }
    }
    return stepsTaken;
}

long long int iterativeGhostSteps(std::string fileName){
    std::string steps = leftRightSteps(fileName);
    auto map = stepMap(fileName);
    std::vector<std::string> currentLocs;
    for(auto x: map){
        if(x.first[2] == 'A'){
            currentLocs.push_back(x.first);
        }
    }

    bool allZ = true;
    for(int j = 0; j < currentLocs.size(); j++){
        if(!(currentLocs[j][2] == 'Z')){
            allZ = false;
            break;
        }
    }
    if(allZ){
        return 0;
    }

    bool goalFound = false;
    long long int stepsTaken = 0;
    std::string newLoc;

    while(!goalFound){
        if(stepsTaken % 100000 == 0){
            std::cout << stepsTaken << std::endl;
        }
        for(int i = 0; i < steps.length(); i++){
            stepsTaken++;

            allZ = true;

            for(int j = 0; j < currentLocs.size(); j++){
                if(steps[i] == 'L'){
                    currentLocs[j] = map.at(currentLocs[j]).first;
                }
                else{
                    currentLocs[j] = map.at(currentLocs[j]).second;
                }
                if(allZ && currentLocs[j][2] != 'Z'){
                    allZ = false;
                }
            }

            if(allZ){
                goalFound = true;
                return stepsTaken;
            }
        }
    }
    return stepsTaken;
}

long long int ghostSteps(std::string fileName){
    std::string steps = leftRightSteps(fileName);
    auto map = stepMap(fileName);
    std::vector<std::string> currentLocs;

    for(auto x: map){
        if(x.first[2] == 'A'){
            currentLocs.push_back(x.first);
        }
    }

    std::vector<int> leastSteps;
    for(int i = 0; i < currentLocs.size(); i++){
        int stepsTaken = 0;
        while(true){
            for(int j = 0; j < steps.size(); j++){
                stepsTaken++;
                if(steps[j] == 'L'){
                    currentLocs[i] = map.at(currentLocs[i]).first;
                }
                else{
                    currentLocs[i] = map.at(currentLocs[i]).second;
                }
            }
            if(currentLocs[i][2] == 'Z'){
                leastSteps.push_back(stepsTaken);
                break;
            }
        }
    }
    return leastCommonMultiple(leastSteps);
}


void day8answers(){
    std::cout << "Test 1 Steps: " << findSteps("8_Test1.txt") << std::endl;
    std::cout << "Test 2 Steps: " << findSteps("8_Test2.txt") << std::endl;
    std::cout << "Actual Steps: " << findSteps("8_Map.txt") << std::endl;

    std::cout << "Test Ghost Steps: " << ghostSteps("8_Test3.txt") << std::endl;
    std::cout << "Actual Ghost Steps: " << ghostSteps("8_Map.txt") << std::endl;
}
