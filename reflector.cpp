//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: reflector.cpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "reflector.h"
#include "helper.h"
#include "errors.h"

using std::stringstream;
using std::cerr;
using std::endl;


rf_board::rf_board(){

  Err_state = NO_ERROR;
}

rf_board::~rf_board(){
  //The destructor for vector and string class objects are called when the object goes out of scope
}


int rf_board::rf_vectorized_pairs(std::vector<string> str_vector,std::vector<std::pair<int,int> >& wired_pairs){

  for (unsigned int index = 0; index < str_vector.size() ; index+=2){

    if (wired_pairs.size() >= 13 or index >= str_vector.size()-1){
      cerr << "Incorrect number of parameters in reflector file ";
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    stringstream ss_val1(str_vector[index]);
    stringstream ss_val2(str_vector[index+1]);

    int val1 = 0;
    int val2 = 0;

    ss_val1 >> val1;
    ss_val2 >> val2;

    if (ss_val1.fail() or ss_val2.fail()){
      cerr << "Non-numeric character in reflector file ";
      return NON_NUMERIC_CHARACTER;
    }

    else if (val1 < 0 or val1 > 25 or val2 < 0 or val2 > 25){
      cerr << "Invalid index in reflector file ";
      return INVALID_INDEX;
    }

    for (unsigned int rec_ind = 0; rec_ind < wired_pairs.size(); rec_ind++){

      if (val1 == val2 or val1 == wired_pairs[rec_ind].first or val1 == wired_pairs[rec_ind].second or val2 == wired_pairs[rec_ind].first or val2 == wired_pairs[rec_ind].second) {

	cerr << "Impossible configuration in reflector file ";
        return INVALID_REFLECTOR_MAPPING;
      }
    }

    wired_pairs.push_back(std::make_pair(val1,val2));
  }
  if (wired_pairs.size() < 13){
    cerr << "Insufficient number of mappings in reflector file: ";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  
  return NO_ERROR;
}


int rf_board::rf_connections(char*& filename){

  //Read file using "helper.h" function:
  Err_state = read_file(filename,rf_str);

  if (Err_state != NO_ERROR)
    return Err_state;
  
  rf_strvector = split(rf_str,' ');

  Err_state = rf_vectorized_pairs(rf_strvector, rf_wires);

  if (Err_state != NO_ERROR){
    cerr << filename << endl;
    return Err_state;
  }
  
  return Err_state;
}
