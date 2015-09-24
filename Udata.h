//
//  Udata.h
//
//
//  Created by nash on 9/24/15.
//  Copyright 2015+ iBean Software.
//  https://www.facebook.com/iBeanSowtware
//  allrightsreserved.

#ifndef iBS_Udata_h
#define iBS_Udata_h

const int Ustr_MAJOR_VERSION = 0;
const int Ustr_MINOR_VERSION = 1;

struct switch_board 
{
    unsigned int sw;
    switch_board():sw(0x00000000){};
    switch_board(unsigned int& v):sw(v){};
    ~switch_board(){};
    switch_board& operator=(const switch_board& x)
    {   sw=x.sw;   return *this;    };
    bool isOn(unsigned short& index)
    {// 32  bool switches  indexes: 0-31
        if (index>31) index=31;
        return  !((sw & 1<<index)==0);
    };  
    void flip(unsigned short& index)
    {   
        if (index>31) index=31; 
        sw=sw^1<<index;    
    };
};
struct switch_board;

struct data_v//for UTF-8 formatted data   
{
    std::vector <unsigned char>  d_v;
    
    data_v():d_v(0){d_v.reserve(125);};//uc_v[0]='\x0000';};
    data_v(std::vector<unsigned char>& v):d_v(v.size())
    {
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=v[i];   }
    };
    ~data_v(){if(d_v.size())d_v.clear();};
    
    data_v& operator=(const data_v& x)
    {
        if (!resize(x.d_v.size())){return *this;};//out of memory
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=x.d_v[i];   }
        return *this;
    };

private:
    bool resize(size_t nsize)
    {
        if (d_v.size()!=nsize) 
        {   
            if (d_v.max_size()<nsize){ return false; }//out of memory
            else {  d_v.resize(nsize); }   
        }
        return true;
    };  
};
struct data_v;

struct uint_v//for raw unicodes and others
{
    std::vector <unsigned int>  i_v;
    
    uint_v():i_v(0){i_v.reserve(30);};//uc_v[0]='\x0000';};
    uint_v(std::vector<unsigned int>& v):i_v(v.size())
    {
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=v[i];   }
    };
    ~uint_v(){if(i_v.size())i_v.clear();};
    
    uint_v& operator=(const uint_v& x)
    {
        if (!resize(x.i_v.size())){return *this;};//out of memory
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=x.i_v[i];   }
        return *this;
    };
    
private:
    bool resize(size_t nsize)
    {
        if (i_v.size()!=nsize) 
        {   
            if (i_v.max_size()<nsize){ return false; }//out of memory
            else {  i_v.resize(nsize); }   
        }
        return true;
    };  
};
struct uint_v;


#endif // iBS_Udata_h
