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
#include "Uchar.h"
#include "Udata.h"

const int Ufile_MAJOR_VERSION = 0;
const int Ufile_MINOR_VERSION = 6;

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
    void getraw_v(u8str& u8_v)
    {
        unsigned char  temp=0;   
        u8char   u8temp();
        unsigned short sz=0;  
        std::vector<unsigned char> ref; 
        ref.reserve(6);
       
        if (u8_v.ref.size())u8_v.ref.clear();
        u8_v.ref.reserve(sizeof(fin));
        while(fin >> temp)
        {
            if (isTrailByte(temp)) {
                ref.push_back(temp);  
            }
            else
            {
                sz = ByteCount(temp);  
                if (ref.size()) 
                {
                     u8_v.append(u8char(ref));
                    ref.clear();
                }
                ref.resize(sz);
                ref[0]=temp;
            }
        }
        if (ref.size()) 
        {
            u8_v.append(u8char(ref));
            ref.clear();
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