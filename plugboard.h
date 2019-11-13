//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: plugboard.h

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <vector>
#include <string>

using std::string;

class pb_board {

  int Err_state;

 public:
  
  string pb_str;
  std::vector<string> pb_strvector;
  std::vector<std::pair<int,int> > pb_wires;
  
  //Default constructor and destructor:
  pb_board();
  ~pb_board();

  //Function to construct vector of pairs and return errors according to plugboard specification:
  int pb_vectorized_pairs(std::vector<string> str_vector,std::vector<std::pair<int,int> >& wired_pairs);

  //Function to configure the plugboard:
  int pb_connections(char*& filename);
 
};

#endif
