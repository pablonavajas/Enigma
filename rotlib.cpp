//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: rotlib.cpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "rotlib.h"
#include "helper.h"
#include "errors.h"

using std::stringstream;
using std::cerr;
using std::endl;

rot_board::rot_board(){

  Err_state = NO_ERROR;
}

rot_board::~rot_board(){
  //The destructor for vector and string class objects are called when the object goes out of scope
}


int rot_board::vectorize_rot(string str, std::vector<int>& wires){
  
  std::vector<string> str_vector = split(str,' ');
  
  for (unsigned int index = 0; index < str_vector.size() and wires.size() < 27; index++){
    
    stringstream ss_val(str_vector[index]);

    int val = 0;
    ss_val >> val;

    if (ss_val.fail()){
      cerr << "Non-numeric character for mapping in rotor file ";
      return NON_NUMERIC_CHARACTER;
    }

    else if (val < 0 or val > 25){
      cerr << "Invalid index for mapping in rotor file ";
      return INVALID_INDEX;
    }

    for (unsigned int rec_idx = 0; rec_idx < wires.size() and wires.size() < 26; rec_idx++){
      if (val == wires[rec_idx]){
	cerr << "Invalid mapping of input " << index << " to output " << val << "(output " << val << " is already mapped to from input " << rec_idx << " in rotor file ";
	return INVALID_ROTOR_MAPPING;
      }
    }

    wires.push_back(val);
  }
  if (wires.size() < 26){
    cerr << "Not all inputs mapped in rotor file: ";
    return INVALID_ROTOR_MAPPING;
  }
    
  return NO_ERROR;
}

int rot_board::vectorize(string str,std::vector<int>& start_pos){
  
  std::vector<string> str_vector = split(str,' ');

  for (unsigned int index = 0; index < str_vector.size(); index++){
    
    stringstream ss_val(str_vector[index]);

    int val = 0;
    ss_val >> val;

    if (ss_val.fail()){
      cerr << "Non-numeric character in rotor positions file ";
      return NON_NUMERIC_CHARACTER;
    }

    else if (val < 0 or val > 25){
      cerr << "Invalid index in rotors positions file ";
      return INVALID_INDEX;
    }

    start_pos.push_back(val);
  }
    
  return NO_ERROR;
}

void rot_board::initialPositions(std::vector<std::vector<int> >& rotor_part, std::vector<int> start_pos){

  for (int rot_index = rotor_part.size()-1; rot_index >= 0; rot_index--){

    while (rotor_part[rot_index][0] != start_pos[rotor_part.size()-1-rot_index]){
      rotate(rotor_part[rot_index].begin(), rotor_part[rot_index].begin()+1,rotor_part[rot_index].end());
    }
  }
}


int rot_board::rot_settings(int argc, char** argv){

  std::vector<int> rot_wires;

  for (int file_idx = argc - 2; file_idx >= 3; file_idx--){

    string rot_str;
    
    Err_state = read_file(argv[file_idx], rot_str);

    if (Err_state != NO_ERROR)
      return Err_state;
    
    Err_state = vectorize_rot(rot_str, rot_wires);

    if (Err_state != 0){
      cerr << argv[file_idx];
      return Err_state;
    }
    
    rot_notches.push_back(rot_wires[26]);

    rot_wires.erase(rot_wires.end()-1);

    rotor_part.push_back(rot_wires);

    rot_wires.clear();
  }

  string start_str;

  Err_state = read_file(argv[argc-1], start_str);

  if (Err_state != NO_ERROR)
    return Err_state;

  Err_state = vectorize(start_str, start_pos);
  
  if (start_pos.size() < rotor_part.size()){
    cerr << "No starting position for rotor 0 in rotor position file: " << argv[argc-1] << endl;
    return NO_ROTOR_STARTING_POSITION;
  }

  initialPositions(rotor_part,start_pos);

  return Err_state;

}

void rot_board::rotation(std::vector<std::vector<int>> & rotor_part, std::vector<int> rot_notches){

  rotate(rotor_part[0].begin(), rotor_part[0].begin()+1,rotor_part[0].end());
  bool prev_rot = true;

  for (unsigned int rot_index = 1; rot_index < rotor_part.size(); rot_index++){
    if (rotor_part[rot_index-1][0] == rot_notches[rot_index-1] and prev_rot == true){
      rotate(rotor_part[rot_index].begin(), rotor_part[rot_index].begin()+1,rotor_part[rot_index].end());
    }
    else {
      prev_rot = false;
    }
  }
}




    

    
	
