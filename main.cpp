//
//  main.cpp
//  UTF-8_Vector
//
//  Created by nash on 9/23/15.
//  Copyright 2015 iBean_Software. All rights reserved.
//

#include <iostream>
#include "Uchar.h"

int main (int argc, const char * argv[])
{
     unsigned int value= 0x0391;  
    std::vector<unsigned char> c;
    Uchar  uc(value);
    //c=uc.uc_v;
  //  uc+=value;
    std::cout << value<<std::endl;
    std::cout << c.size()<<std::endl;
        
     std::cout << uc.uc_v.size()<<std::endl;
  // std::cout << uc.c_str()<<std::endl;
    return 0;
}

