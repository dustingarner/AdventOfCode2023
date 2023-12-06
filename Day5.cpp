#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>


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

unsigned int getNumber(const std::string &row, int ind){
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

std::vector<unsigned int> getSeeds(const std::string &row){
    std::vector<unsigned int> seeds;
    for(int i = 0; i < row.length(); i++){
        if(isdigit(row[i])){
            unsigned int tempSeed = getNumber(row, i);
            seeds.push_back(tempSeed);
            i = getEndInd(row, i);
        }
    }
    return seeds;
}

std::vector<unsigned int> getRange(const std::string &row){
    std::string rowCopy = row;
    char delimiter = ' ';

    std::vector<unsigned int> numbers;

    while(rowCopy.length() > 0){
        int endInd = rowCopy.length();
        for(int i = 0; i < rowCopy.length(); i++){
            if(rowCopy[i] == ' '){
                endInd = i;
                break;
            }
        }
        std::string tempNum = rowCopy.substr(0, endInd);
        numbers.push_back(getNumber(tempNum, 0));
        rowCopy.erase(0, endInd + 1);
    }

    return numbers;
}

unsigned int getConversion(unsigned int input, const std::vector<std::vector<unsigned int>> &ranges){
    for(int i = 0; i < ranges.size(); i++){
        if((input >= ranges[i][1]) && (ranges[i][2] + ranges[i][1] > input)){
            unsigned int difference = input - ranges[i][1];
            return ranges[i][0] + difference;
        }
    }
    return input;
}

unsigned int seedLocation(unsigned int seed, 
        const std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> &umap){
    std::vector<std::string> conversions;
    conversions.push_back("seed-to-soil map:");
    conversions.push_back("soil-to-fertilizer map:");
    conversions.push_back("fertilizer-to-water map:");
    conversions.push_back("water-to-light map:");
    conversions.push_back("light-to-temperature map:");
    conversions.push_back("temperature-to-humidity map:");
    conversions.push_back("humidity-to-location map:");

    unsigned int tempNum = seed;
    for(int i = 0; i < conversions.size(); i++){
        std::string tempConv = conversions[i];
        std::vector<std::vector<unsigned int>> vec = umap.at(tempConv);
        tempNum = getConversion(tempNum, vec);
    }
    return tempNum;
}


unsigned int lowestLocation(std::string fileName){
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    std::vector<unsigned int> seeds;
    std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> umap;

    if(txtfile.is_open()){
        std::string line;
        bool seedsFound = false;
        std::string tempKey;
        
        while(std::getline(txtfile, line)){
            if(!seedsFound){
                std::vector<unsigned int> tempSeeds = getSeeds(line);
                seeds.insert(seeds.end(), tempSeeds.begin(), tempSeeds.end());
                seedsFound = true;
                continue;
            }
            if(line.length() == 0){
                continue;
            }
            if(isalpha(line[0])){
                tempKey = line;
                std::vector<std::vector<unsigned int>> vec;
                umap[tempKey] = vec;
                continue;
            }
            std::vector<unsigned int> tempRange = getRange(line);
            umap[tempKey].push_back(tempRange);

        }
        txtfile.close();
    }

    unsigned int location = seedLocation(seeds[0], umap);
    for(int i = 1; i < seeds.size(); i++){
        unsigned int tempLoc = seedLocation(seeds[i], umap);
        location = tempLoc < location ? tempLoc : location;
    }

    return location;
}

bool sortCol(const std::vector<unsigned int> &v1, const std::vector<unsigned int> &v2){
    return v1[0] < v2[0];
}

bool seedExists(unsigned int number, const std::vector<unsigned int> &seeds, 
        const std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> &umap){
    if(number == 2493982655){
        int a = 5;
    }
    std::vector<std::string> conversions;
    conversions.push_back("seed-to-soil map:");
    conversions.push_back("soil-to-fertilizer map:");
    conversions.push_back("fertilizer-to-water map:");
    conversions.push_back("water-to-light map:");
    conversions.push_back("light-to-temperature map:");
    conversions.push_back("temperature-to-humidity map:");
    conversions.push_back("humidity-to-location map:");
    std::reverse(conversions.begin(), conversions.end());

    for(int i = 0; i < conversions.size(); i++){
        std::vector<std::vector<unsigned int>> tempArr = umap.at(conversions[i]);
        for(int j = 0; j < tempArr.size(); j++){
            std::vector<unsigned int> tempValues = tempArr[j];
            if(number >= tempValues[0] && number < tempValues[0] + tempValues[2]){
                unsigned int difference = number - tempValues[0];
                number = tempValues[1] + difference;
                break;
            }
        }
    }

    for(int i = 0; i < seeds.size(); i+=2){
        if(number >= seeds[i] && number < seeds[i] + seeds[i + 1]){
            return true;
        }
    }
    return false;
}

unsigned int newLowestLocation(std::string fileName){
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    std::vector<unsigned int> seeds;
    std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> umap;

    if(txtfile.is_open()){
        std::string line;
        bool seedsFound = false;
        std::string tempKey;

        while(std::getline(txtfile, line)){
            if(!seedsFound){
                std::vector<unsigned int> tempSeeds = getSeeds(line);
                seeds.insert(seeds.end(), tempSeeds.begin(), tempSeeds.end());
                seedsFound = true;
                continue;
            }
            if(line.length() == 0){
                continue;
            }
            if(isalpha(line[0])){
                tempKey = line;
                std::vector<std::vector<unsigned int>> vec;
                umap[tempKey] = vec;
                continue;
            }
            std::vector<unsigned int> tempRange = getRange(line);
            umap[tempKey].push_back(tempRange);
            std::sort(umap.at(tempKey).begin(), umap.at(tempKey).end(), sortCol);

            int a = 0;

        }
        txtfile.close();
    }

    unsigned int maxValue = umap.at("humidity-to-location map:")[umap.at("humidity-to-location map:").size() - 1][0] + 
            umap.at("humidity-to-location map:")[umap.at("humidity-to-location map:").size() - 1][2];
    if(maxValue == 0){
        maxValue = UINT_MAX;
    }
    for(unsigned int i = 0; i < maxValue; i++){
        if(seedExists(i, seeds, umap)){
            std::cout << std::endl;
            return i;
        }
        if(i % 10000000 == 0){
            std::cout << i << " ";
        }
    }
    
    return maxValue - 1;
}


    

int main(){
    std::cout << "Test Location: " << lowestLocation("5_Test.txt") << std::endl;
    std::cout << "Actual Location: " << lowestLocation("5_SeedLocations.txt") << std::endl;

    std::cout << "Test Range Location: " << newLowestLocation("5_Test.txt") << std::endl;
    std::cout << "Actual Range Location: " << newLowestLocation("5_SeedLocations.txt") << std::endl;
}



