#include <iostream>
#include <string>
#include <fstream>


int char_to_int(char num){
    return num - 48;
}

int colonIndex(std::string game){
    int colon = 0;
    for(int i = 0; i < game.length(); i++){
        if(game[i] == ':'){
            colon = i;
            break;
        }
    }
    return colon;
}


int colorIndex(std::string game, int start_index){
    for(int i = start_index; i < game.length(); i++){
        if(isalpha(game[i])){
            return i;
        }
    }
    return start_index;
}

int cubeQuantity(std::string game, int start_index){
    for(int i = start_index; i < game.length(); i++){
        if(game[i] == ' '){
            start_index = i;
            break;
        }
    }
    int sum = 0;
    int multiplier = 1;
    for(int i = start_index - 1; i >= 0; i--){
        if(game[i] == ' '){
            break;
        }
        sum += char_to_int(game[i]) * multiplier;
        multiplier *= 10;
    }
    return sum;
}


int gameNumber(std::string game){
    int colon = colonIndex(game);
    int sum = 0;
    int factor = 1;
    for(int i = colon - 1; i >= 0; i--){
        if(game[i] == ' '){
            break;
        }
        int digit = char_to_int(game[i]);
        sum += digit * factor;
        factor *= 10;
    }
    return sum;
}

bool gamePossible(std::string game){
    int rCount = 0, gCount = 0, bCount = 0;
    int startIndex = colonIndex(game);
    for(int i = startIndex; i < game.length(); i++){
        if(!isdigit(game[i])){
            continue;
        }
        int colInd = colorIndex(game, i);
        char color = game[colInd];
        int quantity = cubeQuantity(game, i);
        if(color == 'r' && quantity > 12){
            return false;
        }
        if(color == 'g' && quantity > 13){
            return false;
        }
        if(color == 'b' && quantity > 14){
            return false;
        }
        i = colInd;
    }
    return true;
}


int possibleGames(std::string fileName){
    int sum = 0;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            if(!gamePossible(line)){
                continue;
            }
            sum += gameNumber(line);
        }
    }
    txtfile.close();
    return sum;
}


int cubePower(std::string game){
    int minR = 0, minG = 0, minB = 0;
    int startIndex = colonIndex(game);
    for(int i = startIndex; i < game.length(); i++){
        if(!isdigit(game[i])){
            continue;
        }
        int colInd = colorIndex(game, i);
        char color = game[colInd];
        int quantity = cubeQuantity(game, i);
        if(color == 'r'){
            minR = quantity > minR ? quantity : minR;
        }
        else if(color == 'g'){
            minG = quantity > minG ? quantity : minG;
        }
        else if(color == 'b'){
            minB = quantity > minB ? quantity : minB;
        }
    }
    return minR * minG * minB;
}

int sumPowers(std::string fileName){
    int sum = 0;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            sum += cubePower(line);
        }
    }
    txtfile.close();
    return sum;
}


int main(){
    std::cout << "Possible Test: " << possibleGames("2_Test.txt") << std::endl;
    std::cout << "Possible Actual: " << possibleGames("2_CubeGame.txt") << std::endl;
    std::cout << "Power Test: " << sumPowers("2_Test.txt") << std::endl;
    std::cout << "Power Actual: " << sumPowers("2_CubeGame.txt") << std::endl;
}