#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

int char_to_int(char num);

int getStartInd(const std::string &row, int ind);

int getEndInd(const std::string &row, int ind);

int getNumber(const std::string &row, int ind);

unsigned int getUNumber(const std::string &row, int ind);

long long int getLongNumber(const std::string &row, int ind);

#endif