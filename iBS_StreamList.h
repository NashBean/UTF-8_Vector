//
//  iBS_StreamList.h
//  UTF-8_Vector
//
//  Created by nash on 11/12/15.
//  Copyright 2015 iBean Software. 
//  All rights reserved.
//
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//
//  a struct to hold a multi length UTF-8 char
//  Constructs using 0-6: 8 bit bytes
//  to hold a UTF-8 char.
//  Should be std::vector safe
//  And should be fast.

#ifndef iBS_Uchar_h
#define iBS_Uchar_h
#include <vector>
#include <sstream>
#include <fstream>

const int STREAMLIST_MAJOR_VERSION = 0;
const int STREAMLIST_MINOR_VERSION = 1;

namespace iBS 
{
    struct StreamList
    {
        std::vector<std::stringstream> ref; 
    };
    
}//end of namespace iBS