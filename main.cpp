//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: main.cpp

#include <iostream>
#include <string>
#include <sstream>

#include "enigma.h"
#include "errors.h"

using std::cout;
using std::cerr;
using std::string;
using std::endl;

int main(int argc, char** argv) {
  
  Enigma_Machine *enigma = new Enigma_Machine;

  int Err_state;

  //Configure Enigma Machine:
  Err_state = enigma->connections(argc,argv);

  if (Err_state != NO_ERROR)
    return Err_state;
  
  
  //Encryption and decryption mechanism:

  string line;

  getline(std::cin,line);

  std::istringstream iss(line);

  char letter;
  
  while (iss >> std::ws >> letter){

    if (int(letter) < 65 or int(letter) > 90){
      cerr << letter << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    
    enigma->cypher(letter);

    cout << letter;

  }
 
  delete enigma;

  return Err_state;

}

