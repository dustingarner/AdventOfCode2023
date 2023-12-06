#include <iostream>
#include <vector>
#include <string>
#include <fstream>


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


std::vector<int> readLine(const std::string &line){
    std::vector<int> numbers;
    for(int i = 0; i < line.length(); i++){
        if(!isdigit(line[i])){
            continue;
        }
        int tempNum = getNumber(line, i);
        numbers.push_back(tempNum);
        i = getEndInd(line, i);
    }
    return numbers;
}

int timeRange(int time, int dist){
    int range = 0;
    for(int i = 0; i <= time; i++){
        int timeLeft = time - i;
        int tempDist = i * timeLeft;
        if(tempDist > dist){
            range++;
        }
    }
    return range;
}

int timeRange(long long int time, long long int dist){
    int range = 0;
    for(int i = 0; i <= time; i++){
        long long int timeLeft = time - i;
        long long int tempDist = i * timeLeft;
        if(tempDist > dist){
            range++;
            continue;
        }
        if(tempDist <= dist){
            continue;
        }
    }
    return range;
}

int raceTimes(std::string fileName){
    std::vector<std::vector<int>> timeDists;

    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            timeDists.push_back(readLine(line));
        }
        txtfile.close();
    }

    int ranges = 1;
    for(int i = 0; i < timeDists[0].size(); i++){
        ranges *= timeRange(timeDists[0][i], timeDists[1][i]);
    }

    return ranges;
}

long long int getFullNum(const std::string &line){
    std::string number;
    for(int i = 0; i < line.length(); i++){
        if(isdigit(line[i])){
            number.push_back(line[i]);
        }
    }
    return getLongNumber(number, 0);
}

int newRaceTimes(std::string fileName){
    std::vector<long long int> timeDist;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            timeDist.push_back(getFullNum(line));
        }
        txtfile.close();
    }
    return timeRange(timeDist[0], timeDist[1]);
}


int main(){
    std::cout << "Test Race Times: " << raceTimes("6_Test.txt") << std::endl;
    std::cout << "Actual Race Times: " << raceTimes("6_RaceTimes.txt") << std::endl;

    std::cout << "Test Full Race Times: " << newRaceTimes("6_Test.txt") << std::endl;
    std::cout << "Actual Full Race Times: " << newRaceTimes("6_RaceTimes.txt") << std::endl;

}