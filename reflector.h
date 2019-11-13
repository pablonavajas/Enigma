//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: reflector.h

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>
#include <string>

using std::string;

class rf_board {

  int Err_state;

 public:

  rf_board();
  ~rf_board();

  string rf_str;
  std::vector<string> rf_strvector;
  std::vector<std::pair<int,int> > rf_wires;

  //Function to construct vector of pairs and return errors according to reflector specification:
  int rf_vectorized_pairs(std::vector<string> str_vector,std::vector<std::pair<int,int> >& wired_pairs);

  //Function to configure the reflector board:
  int rf_connections(char*& filename);

};

#endif
