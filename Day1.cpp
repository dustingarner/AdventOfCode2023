#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int char_to_int(char num){
    return num - 48;
}

int search(std::string code, std::vector<std::string> subStrings){
    int firstDig;
    int num;
    
    for(int i = 0; i < subStrings.size(); i++){
        int tempInd = code.find(subStrings[i]);
        if(tempInd == std::string::npos){
            continue;
        }
        if(tempInd < firstDig){
            firstDig = tempInd;
            num = i + 1;
        }
    }

    for(int i = 0; i < firstDig; i++){
        if(isdigit(code[i])){
            return char_to_int(code[i]);
        }
    }

    return num;
}



int getCalibration(std::string code){
    int num1;
    int num2;

    int length = code.length();
    for(int i = 0; i < length; i++){
        if(isdigit(code[i])){
            num1 = char_to_int(code[i]);
            break;
        }
    }
    for(int i = length - 1; i >= 0; i--){
        if(isdigit(code[i])){
            num2 = char_to_int(code[i]);
            break;
        }
    }

    return (num1 * 10) + num2;
}


int getNewCalibration(std::string code){
    std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int num1 = search(code, numbers);

    for(int i = 0; i < numbers.size(); i++){
        std::string tempNum = numbers[i];
        std::reverse(tempNum.begin(), tempNum.end());
        numbers[i] = tempNum;
    }
    std::reverse(code.begin(), code.end());
    int num2 = search(code, numbers);

    return (num1 * 10) + num2;
}


int calibration(std::string fileName, int (*func)(std::string)){
    int sum = 0;
    std::fstream txtfile;
    txtfile.open(fileName, std::ios::in);
    if(txtfile.is_open()){
        std::string line;
        while(std::getline(txtfile, line)){
            sum += func(line);
        }
        txtfile.close();
    }
    return sum;
}


int main(){
    std::cout << "Test Old: " << calibration("Test.txt", &getCalibration) << std::endl;
    std::cout << "Test New: " << calibration("Test.txt", &getNewCalibration) << std::endl;

    std::cout << "Calibration Old: " << calibration("CalibrationValues.txt", &getCalibration) << std::endl;
    std::cout << "Calibration New: " << calibration("CalibrationValues.txt", &getNewCalibration) << std::endl;
}
