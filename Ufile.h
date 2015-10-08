//
//  Ufile.h
//
//
//  Created by nash on 10/6/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//

#ifndef iBS_Ufile_h
#define iBS_Ufile_h

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Udata.h"

const int Ufile_MAJOR_VERSION = 0;
const int Ufile_MINOR_VERSION = 3;

namespace iBS 
{
    

class u8ifile 
{
public:
    void getraw_v(std::string& fname, raw_u8str& raw_v)
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
    };    
    
};

u8ifile& operator >> (u8ifile& in_file , unsigned char& a)
{
    in_file >> a;
    return in_file;
};

//-----------------------------------------

class u8ofile 
{
    
    
public:
    u8ofile(std::string filename)
    {   
             fout.open(filename.c_str());
        if (fout.fail()) {} 
    };
    ~u8ofile(){ if (fout.is_open())  fout.close(); };
    
    operator bool(){   return fout.fail();  }; 
    bool eof()   {   return fout.eof();  }; 
    
    
private:
    unsigned char  fstatus;     
    std::ofstream    fout;      
    
};

};//end of iBS namespace

#endif // iBS_Ufile_h