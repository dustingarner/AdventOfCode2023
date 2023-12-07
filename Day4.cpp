#include "Utils.h"
#include "Day4.h"


int getGameNumber(const std::string &game){
    int number = 0;
    for(int i = 0; i < game.length(); i++){
        if(game[i] == ':'){
            number = getNumber(game, i - 1);
        }
    }
    return number;
}

std::vector<int> getSortedNumbers(std::string game, char startingDelineator, char endingDelineator = '~'){
    std::vector<int> numbers;
    int startInd = 0;
    int endInd = game.length();
    for(int i = 0; i < game.length(); i++){
        if(game[i] == startingDelineator){
            startInd = i + 1;
        }
        if(game[i] == endingDelineator){
            endInd = i;
        }
    }

    for(int i = startInd; i < endInd; i++){
        if(!isdigit(game[i])){
            continue;
        }
        int number = getNumber(game, i);
        numbers.push_back(number);
        i = getEndInd(game, i);
    }
    std::sort(numbers.begin(), numbers.end());
    return numbers;
}


int getScore(std::string game){
    std::vector<int> winningNumbers = getSortedNumbers(game, ':', '|');
    std::vector<int> yourNumbers = getSortedNumbers(game, '|');

    int score = 0;
    int currentInd = 0;
    for(int i = 0; i < yourNumbers.size(); i++){
        int tempNum = yourNumbers[i];
        while(tempNum > winningNumbers[currentInd]){
            if(currentInd >= winningNumbers.size()){
                break;
            }
            currentInd++;
        }
        if(winningNumbers[currentInd] == tempNum){
            if(score == 0){
                score = 1;
            }
            else{
                score *= 2;
            }
        }
    }
    return score;
}

int getNewScore(std::string game){
    std::vector<int> winningNumbers = getSortedNumbers(game, ':', '|');
    std::vector<int> yourNumbers = getSortedNumbers(game, '|');

    int score = 0;
    int currentInd = 0;
    for(int i = 0; i < yourNumbers.size(); i++){
        int tempNum = yourNumbers[i];
        while(tempNum > winningNumbers[currentInd]){
            if(currentInd >= winningNumbers.size()){
                break;
            }
            currentInd++;
        }
        if(winningNumbers[currentInd] == tempNum){
            score += 1;
        }
    }
    return score;
}

std::vector<int> getScratchcards(const std::string &game){
    std::vector<int> newCards;
    int score = getNewScore(game);
    int gameNum = getGameNumber(game);

    for(int i = gameNum + 1; i < gameNum + score + 1; i++){
        newCards.push_back(i);
    }
    return newCards;
}

int score(std::string fileName){
    int sum = 0;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            sum += getScore(line);
        }
        txtfile.close();
    }
    return sum;
}

int numScratchcards(std::string fileName){
    std::unordered_map<int, int> map;
    std::fstream txtfile;

    int lastGame = 0;

    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            int gameNum = getGameNumber(line);
            map[gameNum] = 1;
            lastGame = gameNum > lastGame ? gameNum : lastGame;
        }
        txtfile.close();
    }

    int sum = 0;

    int tempGame = 1;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            std::vector<int> tempCards = getScratchcards(line);
            for(auto x : tempCards){
                if(x > lastGame){
                    continue;
                }
                map[x] += map[tempGame];
            }
            tempGame++;
        }
        txtfile.close();
    }
    for(auto i : map){
        sum += i.second;
    }
    return sum;
}


void day4answers(){
    std::cout << "Test Score: " << score("4_Test.txt") << std::endl;
    std::cout << "Actual Score: " << score("4_Scratchcards.txt") << std::endl;

    std::cout << "Test Cards: " << numScratchcards("4_Test.txt") << std::endl;
    std::cout << "Actual Cards: " << numScratchcards("4_Scratchcards.txt") << std::endl;
}