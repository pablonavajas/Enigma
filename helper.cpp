//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: helper.cpp


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "helper.h"
#include "errors.h"

using std::string;
using std::ifstream;
using std::cerr;
using std::stringstream;
using std::cout;
using std::setw;
using std::endl;


int read_file(const char* filename, string& str){

  ifstream in(filename);

  string line;

  if (in.fail()) {

    cerr << "Error opening configuration file " << filename << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  while (!in.eof()){

    getline(in,line);
    str += line;
  }
  in.close();

  return NO_ERROR;
}


std::vector<string> split(string str, char delimiter){

  std::vector<string> splited_str;
  string value;

  stringstream strstream(str);

  //Separate string according to delimiter, and introduce value in vector
  while (getline(strstream,value,delimiter)){
    splited_str.push_back(value);
  }
  return splited_str;
}


void printStr(string str){
  cout << "\n";
  cout << str << '\n';
}


void printVecStr(std::vector<string> strvector){
  cout << "\n";
  for (unsigned int index = 0; index < strvector.size(); index++){
    cout << setw(2) << strvector[index] << setw(1) << ", ";
  }
  cout << "\n";
}


void printVec(std::vector<int> const vect){
  cout << '\n';
  for (unsigned int index = 0; index < vect.size(); index++){
    cout << setw(1) << "|" << setw(2) << vect[index];
  }
  cout << "|\n";
}


void printVecPairs(std::vector<std::pair<int,int> > const wires){
  cout << "\n";
  for (unsigned int index = 0; index < wires.size(); index++){
    cout << setw(1) << wires[index].first << setw(1) << ":" << setw(1) << wires[index].second << setw(1) << "|";
  }
  cout << "\n";
}
  

void printVecVec(std::vector<std::vector<std::pair<int,int> > > const vect){
  cout << "\n";
  
  //Print indexes to improve readability
  for (unsigned int index = 0; index < vect[0].size(); index++){
    cout << setw(1) << "|" << setw(2) << index;
  }
  cout << "|\n-------------------------------------------------------------------------------\n";

  for (unsigned int vec_idx = 0; vec_idx < vect.size(); vec_idx++){
    for (unsigned int val = 0; val < vect[vec_idx].size(); val++){
      cout << setw(1) << "|" << setw(2) << vect[vec_idx][val].first;
    }
    cout << "|\n";
  }
}

  
    
