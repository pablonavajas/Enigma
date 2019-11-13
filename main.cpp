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

  cout << Err_state << "\nReady\n";

  enigma->printenigma();
  
  //Encryption and decryption mechanism:

  cout << "\n\nEnter message: \n";

  string line;

  getline(std::cin,line);

  std::istringstream iss(line);

  char letter;
  
  while (iss >> std::ws >> letter){

    cout << letter << endl;

    if (int(letter) < 65 or int(letter) > 90){
      cerr << "Unrecognized character: " << letter << " in standard input stream. Recognized characters must be capital letters: A-Z." << endl;
      return INVALID_INPUT_CHARACTER;
    }
    
    enigma->cypher(letter);

    cout << "New letter is: " << letter << endl;

  }
 
  delete enigma;

  return NO_ERROR;

}

