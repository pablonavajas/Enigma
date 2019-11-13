//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: enigma.h


#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "reflector.h"
#include "rotlib.h"


class Enigma_Machine {

 public:

  int no_rot;
  
  int Err_state;
  
  pb_board *plugboard;
  rf_board *reflector;
  rot_board *rotors;
  
  //Constructor and Destructor;
  Enigma_Machine();
  ~Enigma_Machine();

  //Function to assign values to plugboard, reflector and rotors:
  int connections(int argc, char** argv);

  //Function to print current enigma settings:
  void printenigma();

  //Function to perform plugboard letter swap:
  void pb_cypher(int& let_int);

  //Function to perform rotor forward mapping:
  void rot_forward(int& let_int);

  //Function to perform reflector letter swap:
  void rf_cypher(int& let_int);

  //Function to perform rotor backwards mapping:
  void rot_back(int& let_int);

  //Function to combine all encryption mechanisms above:
  void cypher(char& letter);
  
};

#endif
