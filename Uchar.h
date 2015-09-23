//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright 2015+ iBean Software.
//
//  a struct to hold a multi length UTF-8 char
//  and still compile with c++98
//  Constructs using 0-4 unsigned char
//  to hold all the 8 bit section of a UTF-8 char.
//  Should be std::vector safe
//  And should be fast.

#ifndef iBS_Uchar_h
#define iBS_Uchar_h
#include <vector>

const int Uchar_MAJOR_VERSION = 0;
const int Uchar_MINOR_VERSION = 6;

const unsigned char endc= '\n';  

//this is a function that turns a unacode into UTF-8 format
extern inline void SetUnacode(std::vector<unsigned char>& uc_v, unsigned int& unacode)
{   
    if (unacode<=0x7f) 
    {
        resize(uc_v,1);    
        uc_v[0]=unacode;
    }  
    else if (unacode>=0x80 && unacode<=0x07ff) 
    {
        resize(uc_v,2);    
        uc_v[1]=unacode;//   &   0x3f;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unacode>>6;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if (unacode>=0x0800 && unacode<=0xffff) 
    {
        resize(uc_v,3);    
        unsigned char temp;     
        
        temp=unacode;
        uc_v[2]=temp  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        temp=unacode>>6;
        uc_v[1]=temp  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        temp=unacode>>12;
        uc_v[0]=temp&0x1f;
        uc_v[0]=uc_v[0]|0xc0;
    }  
    else if(unacode>=0x010000 && unacode<=0x1fffff) 
    {
        // uc_v.reserve(4);
        resize(uc_v,4);
        
        uc_v[3]=unacode;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unacode>>6;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unacode>>12;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unacode>>18;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if(unacode>=0x200000 && unacode<=0x03ffffff) 
    {
        // uc_v.reserve(5);
        resize(uc_v,5);
        
        uc_v[4]=unacode;//   &   0x3f;
        uc_v[4]=uc_v[4]  &   0x3f;
        uc_v[4]=uc_v[4]|0x80;
        
        uc_v[3]=unacode>>6;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unacode>>12;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unacode>>18;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unacode>>24;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if(unacode>=0x04000000 && unacode<=0x7fffffff) 
    {
        //  uc_v.reserve(6);
        resize(uc_v,6);
        
        uc_v[5]=unacode;//   &   0x3f;
        uc_v[5]=uc_v[5]  &   0x3f;
        uc_v[5]=uc_v[5]|0x80;
        
        uc_v[4]=unacode>>6;//   &   0x3f;
        uc_v[4]=uc_v[4]  &   0x3f;
        uc_v[4]=uc_v[4]|0x80;
        
        uc_v[3]=unacode>>12;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unacode>>18;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unacode>>24;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unacode>>30;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else    uc_v[0]='\x0000';
    
};

extern inline const char* c_str(std::vector<unsigned char>& data)  
{
    if (data.size()==0) 
    {
        return 0x00;
    }
    
    size_t sz=data.size();
    char result[sz+1];
    
    for (size_t i=0;i<sz; ++i) 
    {
        result[i]= char(data[i]);
    }
    
    result[sz]  = endc;
    
    return (const char*)*result;
};

extern inline void resize(std::vector<unsigned char>& uc_v,size_t x)
{
    if (uc_v.size()!=x) 
    {   
        if (uc_v.max_size()<x){  }//throw out of memory
        else {  uc_v.resize(x); }   
    }
    
};   

struct  Uchar//UTF-8    container
{
    std::vector <unsigned char>  uc_v;
    Uchar():uc_v(0){uc_v.reserve(6)};//uc_v[0]='\x0000';};
    Uchar(std::vector<unsigned char>& v):uc_v(v.size())
    {
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=v[i];   }
    };
    ~Uchar(){uc_v={};};//if(uc_v.size())uc_v.clear();};
    //    Uchar(Uchar& c):uc_v(c.uc_v){};
    
    Uchar(unsigned int unicode):uc_v(1)
    {    SetUnacode(uc_v,unicode); };
    
    void resize(size_t x)
    {  resize(uc_v,size_t x);   };       
    
    Uchar& operator=(const Uchar& x)
    {
        if (uc_v.size()!=x.uc_v.size()) 
        {   if (uc_v.size()<x.uc_v.size()) 
        {   if (uc_v.max_size()<x.uc_v.size()) 
        {   return *this;};//throw out of memory
        }
            uc_v.resize(x.uc_v.size());    
        }
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=x.uc_v[i];   }
        return *this;
    };
    const  char* c_str()  
    {   return c_str(uc_v);   }
    
};

struct  Ustr//UTF-8    container
{
    std::vector <unsigned char>  str_v;
    
    Ustr():str_v(0){str_v.reserve(6)};
    Ustr(std::vector<unsigned char>& v):str_v(v.size())
    {
        for (size_t i=0; i<str_v.size(); ++i) 
        {   str_v[i]=v[i];   }
    };
    ~Ustr(){str_v={};};    
    Ustr(unsigned int unacode):str_v(1)
    {    SetUnacode(str_v,unacode);};
    
    void resize(size_t x)
    {   resize(str_v,x)   };       
    
    Ustr& operator=(const Ustr& x)
    {
        if (str_v.size()!=x.str_v.size()) 
        {   if (str_v.size()<x.str_v.size()) 
        {   if (str_v.max_size()<x.str_v.size()) 
        {   return *this;};//throw out of memory
        }
            str_v.resize(x.str_v.size());    
        }
        for (size_t i=0; i<str_v.size(); ++i) 
        {   str_v[i]=x.str_v[i];   }
        return *this;
    };
    
    const  char* c_str()  
    {   return c_str(str_v);   }
    
};


#endif // iBS_Uchar_h
