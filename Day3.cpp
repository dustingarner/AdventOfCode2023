#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int char_to_int(char num){
    return num - 48;
} 

bool isSymbol(char character){
    if(isdigit(character)){
        return false;
    }
    if(character == '.'){
        return false;
    }
    return true;
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

bool isPart(const std::vector<std::string> &parts, int row, int startInd){
    int endInd = getEndInd(parts[row], startInd);
    bool left = startInd != 0;
    bool right = endInd != parts[row].length() - 1;
    bool up = row != 0;
    bool down = row != parts.size() - 1;

    if((left && up) && (isSymbol(parts[row - 1][startInd - 1]))){
        return true;
    }
    if((left && down) && (isSymbol(parts[row + 1][startInd - 1]))){
        return true;
    }
    if((right && up) && (isSymbol(parts[row - 1][endInd + 1]))){
        return true;
    }
    if((right && down) && (isSymbol(parts[row + 1][endInd + 1]))){
        return true;
    }
    if(left && isSymbol(parts[row][startInd - 1])){
        return true;
    }
    if(right && isSymbol(parts[row][endInd + 1])){
        return true;
    }
    if(up){
        for(int i = startInd; i < endInd + 1; i++){
            if(isSymbol(parts[row - 1][i])){
                return true;
            }
        }
    }
    if(down){
        for(int i = startInd; i < endInd + 1; i++){
            if(isSymbol(parts[row + 1][i])){
                return true;
            }
        }
    }
    return false;
}

std::vector<int> adjacentNumbers(const std::string row, int ind){
    std::vector<int> numbers;
    bool left = false, center = false, right = false;
    if(ind != 0 && isdigit(row[ind - 1])){
        left = true;
    }
    if(isdigit(row[ind])){
        center = true;
    }
    if(ind != row.length() - 1 && isdigit(row[ind + 1])){
        right = true;
    }
    if(!left && !center && !right){
        return numbers;
    }
    if(left && right && !center){
        numbers.push_back(getNumber(row, ind - 1));
        numbers.push_back(getNumber(row, ind + 1));
    }
    else if(left){
        numbers.push_back(getNumber(row, ind - 1));
    }
    else if(center){
        numbers.push_back(getNumber(row, ind));
    }
    else if(right){
        numbers.push_back(getNumber(row, ind + 1));
    }
    return numbers;
}

int gearRatio(std::vector<std::string> &parts, int row, int col){
    std::vector<int> numbers;
    bool left = col != 0;
    bool right = col != parts[row].length() - 1;
    bool up = row != 0;
    bool down = row != parts.size() - 1;

    if(left && isdigit(parts[row][col - 1])){
        numbers.push_back(getNumber(parts[row], col - 1));
    }
    if(right && isdigit(parts[row][col + 1])){
        numbers.push_back(getNumber(parts[row], col + 1));
    }
    if(up){
        std::vector<int> upNumbers = adjacentNumbers(parts[row - 1], col);
        numbers.insert(numbers.end(), upNumbers.begin(), upNumbers.end());
    }
    if(down){
        std::vector<int> downNumbers = adjacentNumbers(parts[row + 1], col);
        numbers.insert(numbers.end(), downNumbers.begin(), downNumbers.end());
    }
    if(numbers.size() != 2){
        return 0;
    }
    return numbers[0] * numbers[1];
}

int sumParts(std::vector<std::string> &parts){
    int sum = 0;
    for(int i = 0; i < parts.size(); i++){
        for(int j = 0; j < parts[i].length(); j++){
            if(!isdigit(parts[i][j])){
                continue;
            }
            if(isPart(parts, i, j)){
                int num = getNumber(parts[i], j);
                sum += num;
                //std::cout << num << " ";
            }
            j = getEndInd(parts[i], j);
        }
        //std::cout << std::endl;
    }
    return sum;
}

int sumGearRatios(std::vector<std::string> &parts){
    int sum = 0;
    for(int i = 0; i < parts.size(); i++){
        for(int j = 0; j < parts[i].length(); j++){
            if(parts[i][j] != '*'){
                continue;
            }
            sum += gearRatio(parts, i, j);
        }
    }
    return sum;
}

std::vector<std::string> parseFile(std::string fileName){
    std::vector<std::string> parts;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            parts.push_back(line);
        }
        txtfile.close();
    }
    return parts;
}

int sumPartsFromFile(std::string fileName){
    std::vector<std::string> parts = parseFile(fileName);
    return sumParts(parts);
}

int gearRatioFromFile(std::string fileName){
    std::vector<std::string> parts = parseFile(fileName);
    return sumGearRatios(parts);
}

int main(){
    std::cout << "Test Parts: " << sumPartsFromFile("3_Test.txt") << std::endl;
    std::cout << "Actual Parts: " << sumPartsFromFile("3_EngineParts.txt") << std::endl;

    std::cout << "Test Gear Ratios: " << gearRatioFromFile("3_Test.txt") << std::endl;
    std::cout << "Actual Gear Ratios: " << gearRatioFromFile("3_EngineParts.txt") << std::endl;
}
