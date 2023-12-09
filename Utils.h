#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <cmath>
#include <ctime>

int char_to_int(char num);

int getStartInd(const std::string &row, int ind);

int getEndInd(const std::string &row, int ind);

int getNumber(const std::string &row, int ind);

unsigned int getUNumber(const std::string &row, int ind);

long long int getLongNumber(const std::string &row, int ind);

bool isPrime(int num);
bool isPrime(unsigned int num);
bool isPrime(long long int num);

std::vector<int> getFactors(long long int num);

long long int leastCommonMultiple(const std::vector<int> &nums);

#endif