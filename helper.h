#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::string;

int read_file(const char* filename, string& str);

std::vector<string> split(string str, char delimiter);

void printStr(string str);

void printVecStr(std::vector<string> strvector);

void printVecPairs(std::vector<std::pair<int,int> > const wires);

void printVecVec(std::vector<std::vector<int> > const vect);

void printVec(std::vector<int> const vect);

#endif
