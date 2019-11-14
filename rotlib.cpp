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
#include <locale>

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
  //Destructors for vector/string are called when the object goes out of scope by default
}


int rot_board::vectorize_rot(string str, std::vector<std::pair<int,int> >& wires){
  
  std::vector<string> str_vector = split(str,' ');
  //Use locale to check if character is decimal
  std::locale loc;

  //Check first 26 strings inside vector individually:
  for (unsigned int index = 0; index < str_vector.size() and wires.size() < 27; index++){

    string line = str_vector[index];

    //Check if all characters in string are digits and raise exception if not:
    for (unsigned int str_idx = 0; str_idx < line.length() ; str_idx++){
      if (!isdigit(line[str_idx],loc)){
	cerr << "Non-numeric character for mapping in rotor file ";
	return NON_NUMERIC_CHARACTER;
      }
    }

    //Convert strings to integers:
    stringstream ss_val(line);

    int val = 0;
    ss_val >> val;

    //Raise exception if invalid index found:
    if (val < 0 or val > 25){
      cerr << "Invalid index for mapping in rotor file ";
      return INVALID_INDEX;
    }

    //Check if value is duplicate:
    //Do not check last value (it must be)
    for (unsigned int rec_idx = 0; rec_idx < wires.size() and wires.size() < 26; rec_idx++){
      if (val == wires[rec_idx].first){
	//Print error message as similar as possible to test solution:
	cerr << "Invalid mapping of input " << index << " to output " << val << " (output " << val << " is already mapped to from input " << rec_idx << ") in rotor file: ";
	return INVALID_ROTOR_MAPPING;
      }
    }
    //Save index in pair to keep absolute frame of reference:
    wires.push_back(std::make_pair(val,index));
  }

  //Raise exception if incorrect number of parameters provided:
  if (wires.size() < 26){
    cerr << "Not all inputs mapped in rotor file: ";
    return INVALID_ROTOR_MAPPING;
  }
  return NO_ERROR;
}

int rot_board::vectorize(string str,std::vector<int>& start_pos){
  
  std::vector<string> str_vector = split(str,' ');
  std::locale loc;

  //Convert to vector of integers:
  for (unsigned int index = 0; index < str_vector.size(); index++){

    string line = str_vector[index];

    //Raise exception if non-digit:
    for (unsigned int str_idx = 0; str_idx < line.length() ; str_idx++){
      if (!isdigit(line[str_idx],loc)){
	cerr << "Non-numeric character in rotor positions file ";
	return NON_NUMERIC_CHARACTER;
      }
    }

    stringstream ss_val(line);
    int val = 0;
    ss_val >> val;

    //Raise exception if invalid index:
    if (val < 0 or val > 25){
      cerr << "Invalid index in rotors positions file ";
      return INVALID_INDEX;
    }
    start_pos.push_back(val);
  }
  return NO_ERROR;
}


void rot_board::initialPositions(std::vector<std::vector<std::pair<int,int> > >& rotor_part, std::vector<int> start_pos){

  //Set initial position for all rotors:
  for (int rot_index = rotor_part.size()-1; rot_index >= 0; rot_index--){

    //Perform rotation established in starting position vector:
    //Note there can be extra initial positions (assigned left to right)
    std::rotate(rotor_part[rot_index].begin(), rotor_part[rot_index].begin()+start_pos[rotor_part.size()-1-rot_index],rotor_part[rot_index].end());

    //Update mapping values in each rotor:
    for (unsigned int val_idx = 0; val_idx < rotor_part[rot_index].size(); val_idx++){
      
      int new_val = (rotor_part[rot_index][val_idx].first - start_pos[rotor_part.size()-1-rot_index])%26;
      //Avoid negative value:
      rotor_part[rot_index][val_idx].first = (new_val >= 0) ? new_val : 26+new_val;
    }
  }
}



int rot_board::rot_settings(int argc, char** argv){

  std::vector<std::pair<int,int> > rot_wires;

  //Read rotor files right to left:
  for (int file_idx = argc - 2; file_idx >= 3; file_idx--){

    string rot_str;
    Err_state = read_file(argv[file_idx], rot_str);

    //Raise error if failed to read:
    if (Err_state != NO_ERROR)
      return Err_state;

    Err_state = vectorize_rot(rot_str, rot_wires);

    //Raise error if failed to vectorize:
    if (Err_state != NO_ERROR){
      cerr << argv[file_idx] << endl;
      return Err_state;
    }

    //Copy first element of pair of last value (notch)
    rot_notches.push_back(rot_wires[26].first);

    //Erase notch pair from vector
    rot_wires.erase(rot_wires.end()-1);

    rotor_part.push_back(rot_wires);

    rot_wires.clear();
  }

  string start_str;

  Err_state = read_file(argv[argc-1], start_str);

  //Raise error if failed to read:
  if (Err_state != NO_ERROR)
    return Err_state;

  Err_state = vectorize(start_str, start_pos);

  //Raise error if failed to vectorize:
  if (Err_state != NO_ERROR){
    cerr << argv[argc-1] << endl;
    return Err_state;
  }

  //Raise error if insufficient starting positions:
  else if (start_pos.size() < rotor_part.size()){
    cerr << "No starting position for rotor 0 in rotor position file: " << argv[argc-1] << endl;
    return NO_ROTOR_STARTING_POSITION;
  }

  //Configure initial positions:
  initialPositions(rotor_part,start_pos);

  return Err_state;

}

void rot_board::rotation(std::vector<std::vector<std::pair<int,int>>> & rotor_part, std::vector<int> rot_notches){

  //Always rotate first rotor and update its values:
  std::rotate(rotor_part[0].begin(), rotor_part[0].begin()+1,rotor_part[0].end());
  for (unsigned int val_idx = 0; val_idx < rotor_part[0].size(); val_idx++){

    int new_val = (rotor_part[0][val_idx].first - 1)%26;
    rotor_part[0][val_idx].first = (new_val >= 0) ? new_val : 26+new_val;
  }
  //Set flag for "previous rotor rotated":
  bool prev_rot = true;

  //For all other rotors, check if previous one rotated and
  //Use frame of reference (vector pair) to check if equal to notch
  for (unsigned int rot_index = 1; rot_index < rotor_part.size(); rot_index++){
    
    if (rotor_part[rot_index-1][0].second == rot_notches[rot_index-1] and prev_rot == true){
      
      std::rotate(rotor_part[rot_index].begin(), rotor_part[rot_index].begin()+1,rotor_part[rot_index].end());
      for (unsigned int val_idx = 0; val_idx < rotor_part[rot_index].size(); val_idx++){

	//Avoid negative value:
	int new_val = (rotor_part[rot_index][val_idx].first - 1)%26;
	rotor_part[rot_index][val_idx].first = (new_val >= 0) ? new_val : 26+new_val;
      }
    }
    //Change flag if not notched to avoid further turns:
    else {
      prev_rot = false;
    }
  }
}




    

    
	
