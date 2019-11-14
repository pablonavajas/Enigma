//Imperial College London - Department of Computing
//MSc C++ Programming - Assessed Exercise No. 2
//Enigma Machine Implementation
//
//Created by: Pablo Navajas Helguero
//Date: 13th November 2019
//
//File: rotlib.h


#ifndef ROTLIB_H
#define ROTLIB_H

#include <vector>
#include <string>

using std::string;

class rot_board {

  int Err_state;

 public:

  //Constructor and destructor:
  rot_board();
  ~rot_board();

  std::vector<int> start_pos;
  std::vector<int> rot_notches;
  std::vector<std::vector<std::pair<int,int> > > rotor_part;

  //Function to construct sub vectors and return errors according to rotor specification:
  int vectorize_rot(string str,std::vector<std::pair<int,int> >& wires);

  //Function to construct start positions vector and return errors according to rotors' starting positions specification:
  int vectorize(string str,std::vector<int>& start_pos);

  //Function to set rotors' starting positions:
  void initialPositions(std::vector<std::vector<std::pair<int,int> > >& rotor_part, std::vector<int> start_pos);

  //Function to combine all steps in rotor configuration:
  int rot_settings(int argc, char** argv);

  //Function to replicate "odometer-like" behaviour of rotors:
  void rotation(std::vector<std::vector<std::pair<int,int>>> & rotor_part, std::vector<int> rot_notches);

};

#endif
