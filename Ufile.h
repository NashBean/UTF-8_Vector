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
#include "Ufile.h"
const int Ufile_MAJOR_VERSION = 0;
const int Ufile_MINOR_VERSION = 2;

namespace iBS 
{
    
struct raw_u8str 
{
    std::vector <unsigned char> ref;
};
    enum  file_status{fs_good=0,fs_fail};   

class u8ifile 
{
    
    
public:
    void getrow(u8ifile& rff, raw_u8str& cv);    
    
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