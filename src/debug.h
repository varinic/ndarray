

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

template <typename T>
void print (const T & x) {           
  std::cout<< x <<std::endl;  
}

template <typename T>
void printcm (const T & x) {           
  std::cout<< x <<", ";  
}

void println () {           
  std::cout<<std::endl;  
}


#endif
