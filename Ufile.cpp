//
//  Ufile.cpp
//
//
//  Created by nash on 10/6/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//
//

#include "Ufile.h"


void iBS::u8ifile::getraw_v(std::string& fname, raw_u8str& raw_v)
{
    unsigned char  temp=0;     
    std::ifstream    inf;
    
    inf.open(fname.c_str());
    raw_v.ref.clear();
    raw_v.ref.reserve(sizeof(inf));
    while(inf >> temp)
    {
        raw_v.ref.push_back(temp);
    }
    inf.close();
}    
