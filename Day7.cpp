#include "Utils.h"
#include "Day7.h"

int handRank(const std::string &hand, bool jacksWild = false){
    std::unordered_map<char, int> cardMap;
    short int jackCount = 0;
    for(int i = 0; i < hand.length(); i++){
        char card = hand[i];
        if(jacksWild && card == 'J'){
            jackCount++;
            continue;
        }
        if(cardMap.find(card) == cardMap.end()){
            cardMap[card] = 1;
        }
        else{
            cardMap[card]++;
        }
    }
    if(jacksWild && jackCount == 5){
        return 7;
    }

    std::vector<int> amounts;
    for(auto x: cardMap){
        amounts.push_back(x.second);
    }

    std::sort(amounts.begin(), amounts.end());
    if(jacksWild){
        amounts[amounts.size() - 1] += jackCount;
    }
    
    if(amounts[0] == 5){
        return 7;
    }
    else if(amounts[0] == 1 && amounts[1] == 4){
        return 6;
    }
    else if(amounts[0] == 2 && amounts[1] == 3){
        return 5;
    }
    else if(amounts[0] == 1 && amounts[1] == 1 && amounts[2] == 3){
        return 4;
    }
    else if(amounts[0] == 1 && amounts[1] == 2 && amounts[2] == 2){
        return 3;
    }
    else if(amounts[0] == 1 && amounts[1] == 1 && amounts[2] == 1 && amounts[3] == 2){
        return 2;
    }
    return 1;
}

int cardRank(const char &card, bool jacksLow = false){
    if(isdigit(card)){
        return char_to_int(card);
    }
    else if(card == 'T'){
        return 10;
    }
    else if(card == 'J' && !jacksLow){
        return 11;
    }
    else if(card == 'Q'){
        return 12;
    }
    else if(card == 'K'){
        return 13;
    }
    else if(card == 'A'){
        return 14;
    }
    return 1;
}

bool compareHands(const std::pair<std::string, int>  &pair1, const std::pair<std::string, int> &pair2, bool jacksWild = false){
    std::string hand1 = pair1.first, hand2 = pair2.first;
    int rank1 = handRank(hand1, jacksWild), rank2 = handRank(hand2, jacksWild);
    if(rank1 < rank2){
        return true;
    }
    else if(rank1 > rank2){
        return false;
    }
    for(int i = 0; i < 5; i++){
        rank1 = cardRank(hand1[i], jacksWild);
        rank2 = cardRank(hand2[i], jacksWild);
        if(rank1 == rank2){
            continue;
        }
        return rank1 < rank2;
    }
    return false;
}

unsigned int totalWinnings(const std::string &fileName, bool jacksWild = false){
    std::vector<std::pair<std::string, int>> handBids;

    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            std::string hand = line.substr(0, 5);
            handBids.push_back(std::make_pair(hand, getNumber(line, 6)));
        }
        txtfile.close();
    }
    std::sort(handBids.begin(), handBids.end(), 
            [jacksWild](const std::pair<std::string, int>  &pair1, const std::pair<std::string, int> &pair2) -> bool{
                return compareHands(pair1, pair2, jacksWild);
            });

    int counter = 1;
    unsigned int sum = 0;
    for(auto x: handBids){
        sum += x.second * counter;
        counter++;
    }

    return sum;
}

void day7answers(){
    std::cout << "Test Winnings: " << totalWinnings("7_Test.txt") << std::endl;
    std::cout << "Actual Winnings: " << totalWinnings("7_CardValues.txt") << std::endl;

    std::cout << "New Test Winnings: " << totalWinnings("7_Test.txt", true) << std::endl;
    std::cout << "New Actual Winnings: " << totalWinnings("7_CardValues.txt", true) << std::endl;
} 

