//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: plugboard.cpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <locale>

#include "plugboard.h"
#include "helper.h"
#include "errors.h"

using std::stringstream;
using std::cerr;
using std::endl;

pb_board::pb_board(){

  Err_state = NO_ERROR;
}

pb_board::~pb_board(){
  //Destructors for vector/string are called when the object goes out of scope by default
}


int pb_board::pb_vectorized_pairs(std::vector<string> str_vector,std::vector<std::pair<int,int> > &wired_pairs){

  
  std::locale loc;
  
  for (unsigned int index = 0; index < str_vector.size() ; index+=2){

    if (index >= str_vector.size()-1){
      cerr << "Incorrect number of parameters in plugboard file ";
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    string line1 = str_vector[index];
    string line2 = str_vector[index+1];

    for (unsigned int line_idx = 0; line_idx < line1.length() ; line_idx++){
      if (!isdigit(line1[line_idx],loc)){
	cerr << "Non-numeric character in plugboard file ";
	return NON_NUMERIC_CHARACTER;
      }
    }

    for (unsigned int line_idx = 0; line_idx < line2.length() ; line_idx++){
      if (!isdigit(line2[line_idx],loc)){
	cerr << "Non-numeric character in plugboard file ";
	return NON_NUMERIC_CHARACTER;
      }
    }
    
    stringstream ss_val1(str_vector[index]);
    stringstream ss_val2(str_vector[index+1]);

    int val1 = 0;
    int val2 = 0;

    ss_val1 >> val1;
    ss_val2 >> val2;

    /*
    if (ss_val1.fail() or ss_val2.fail()){
      cerr << "Non-numeric character in plugboard file ";
      return NON_NUMERIC_CHARACTER;
      }*/

    if (val1 < 0 or val1 > 25 or val2 < 0 or val2 > 25){
      cerr << "Invalid index in plugboard file ";
      return INVALID_INDEX;
    }

    for (unsigned int rec_ind = 0; rec_ind < wired_pairs.size(); rec_ind++){

      if (val1 == val2 or val1 == wired_pairs[rec_ind].first or val1 == wired_pairs[rec_ind].second or val2 == wired_pairs[rec_ind].first or val2 == wired_pairs[rec_ind].second) {

	cerr << "Impossible configuration in plugboard file ";
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }

    wired_pairs.push_back(std::make_pair(val1,val2));
  }
  return NO_ERROR;
}


int pb_board::pb_connections(char*& filename){
  
  //Read file using "helper.h" function:
  Err_state = read_file(filename,pb_str);

  if (Err_state != NO_ERROR)
    return Err_state;
  
  pb_strvector = split(pb_str,' ');

  Err_state = pb_vectorized_pairs(pb_strvector, pb_wires);

  if (Err_state != NO_ERROR){
    cerr << filename << endl;
    return Err_state;
  }
  
  return Err_state;
}
