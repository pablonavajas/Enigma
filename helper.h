//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: helper.h

#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::string;

//Function to read file into string and produce error code: ERROR_OPENING_CONFIGURATION_FILE
int read_file(const char* filename, string& str);

//Function to split string into vector of strings
std::vector<string> split(string str, char delimiter);

//Function to print string
void printStr(string str);

//Function to print vector of strings
void printVecStr(std::vector<string> strvector);

//Function to print vector
void printVec(std::vector<int> const vect);

//Function to print vector of pairs
void printVecPairs(std::vector<std::pair<int,int> > const wires);

//Function to print Vector of Vectors
void printVecVec(std::vector<std::vector<std::pair<int,int> > > const vect);

#endif
