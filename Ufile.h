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
const int Ufile_MINOR_VERSION = 4;

namespace iBS 
{
    

class u8ifile 
{
public:
    u8ifile(std::string filename)
    {   
        fin.open(filename.c_str());
        if (fin.fail()) {} 
    };
    ~u8ifile(){ if (fin.is_open())  fin.close(); };
    
    operator bool(){   return fin.fail();  }; 
    bool eof()   {   return fin.eof();  }; 
    void getraw_v(raw_u8str& raw_v)
    {
        unsigned char  temp=0;     
        //fin.open(fname.c_str());
        raw_v.ref.clear();
        raw_v.ref.reserve(sizeof(fin));
        while(fin >> temp)
        {//todo_isthisright?
            raw_v.ref.push_back(temp);
        }
        fin.close();
    };    
private:
    std::ifstream    fin   ;      
    
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
    std::ofstream    fout;      
    
};
    
    u8ofile& operator << (u8ofile& out_file , unsigned char& a)
    {
        out_file << a;
        return out_file;
    };
    
    //-----------------------------------------


};//end of iBS namespace

#endif // iBS_Ufile_h