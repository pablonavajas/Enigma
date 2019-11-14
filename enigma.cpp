//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: enigma.cpp


#include <iostream>
#include <string>
#include <vector>

#include "enigma.h"
#include "helper.h"
#include "errors.h"

using std::cerr;
using std::endl;
using std::cout;


Enigma_Machine::Enigma_Machine(){

  Err_state = NO_ERROR;
  no_rot = 0;

  plugboard = nullptr;
  reflector = nullptr;
  rotors = nullptr;
}

Enigma_Machine::~Enigma_Machine(){
  
  delete plugboard;
  delete reflector;
  delete rotors;
}


int Enigma_Machine::connections(int argc, char** argv){

  //Raise error if insufficient number of parameters introduced:
  if (argc < 4){
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    Err_state = INSUFFICIENT_NUMBER_OF_PARAMETERS;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  //Determine number of rotors:
  if (argc > 3)
    no_rot = argc - 4;

  //Configure Plugboard:
  plugboard = new pb_board;
  Err_state = plugboard->pb_connections(argv[1]);

  if (Err_state != NO_ERROR)
    return Err_state;
  
  //Configure Reflector:
  reflector = new rf_board;
  Err_state = reflector->rf_connections(argv[2]);

  if (Err_state != NO_ERROR)
    return Err_state;
  
  //Configure rotors if introduced:
  if (no_rot > 0){

    rotors = new rot_board;
    Err_state = rotors->rot_settings(argc,argv);
  }

  return Err_state;
}


void Enigma_Machine::printenigma(){

  //Use of "helper.h" functions to print Enigma Machine configuration:

  printVecPairs(plugboard->pb_wires);

  printVecPairs(reflector->rf_wires);

  if (no_rot > 0){
    cout << "\nrotors: \n";
    printVecVec(rotors->rotor_part);
    cout << "\nnotches: \n";
    printVec(rotors->rot_notches);
    cout << "\nstart: \n";
    printVec(rotors->start_pos);
  }
}


void Enigma_Machine::pb_cypher(int& let_int){

  //Check elements inside the vector of pairs:
  for (unsigned int idx = 0; idx < plugboard->pb_wires.size();idx++){

    //Assign the corresponding paired element if any:
    if (let_int == plugboard->pb_wires[idx].first){

      let_int = plugboard->pb_wires[idx].second;
    }
    else if (let_int == plugboard->pb_wires[idx].second){

      let_int = plugboard->pb_wires[idx].first;
    }
  }
}


void Enigma_Machine::rot_forward(int& let_int){

  //Check vectors from right to left:
  for (unsigned int idx = 0; idx < rotors->rotor_part.size();idx++){
    
    //Assign element occupying the current element's index:
    let_int = rotors->rotor_part[idx][let_int].first;
  }
}


void Enigma_Machine::rf_cypher(int& let_int){

  //Check elements inside the vector of pairs:
  for (unsigned int idx = 0; idx < reflector->rf_wires.size();idx++){

    //Assign the corresponding paired element:
    if (let_int == reflector->rf_wires[idx].first){
      
      let_int = reflector->rf_wires[idx].second;
    }
    else if (let_int == reflector->rf_wires[idx].second){

      let_int = reflector->rf_wires[idx].first;
    }
  }
}


void Enigma_Machine::rot_back(int& let_int){

  //Initialize helper variable:
  int help_int = let_int;

  //Check vectors from left to right:
  for (int vec_idx = rotors->rotor_part.size()-1; vec_idx >= 0; vec_idx--){

    //Check values inside vector:
    for (unsigned int val_idx = 0; val_idx < rotors->rotor_part[vec_idx].size(); val_idx++){

      //When value is found assign index to helper variable:
      if (let_int == rotors->rotor_part[vec_idx][val_idx].first){

	//Assign index to helper variable to avoid further swaps:
	help_int = val_idx;
      }
    }
    let_int = help_int;
  }
}

  

void Enigma_Machine::cypher(char& letter){

  int let_int = int(letter) - 65;
  
  pb_cypher(let_int);

  if (no_rot > 0){

    //Rotation BEFORE closing circuit as specified:
    rotors->rotation(rotors->rotor_part,rotors->rot_notches);

    rot_forward(let_int);
  }
    
  rf_cypher(let_int);

  if (no_rot > 0){

    rot_back(let_int);
  }

  pb_cypher(let_int);

  letter = char(let_int + 65);
}



  
