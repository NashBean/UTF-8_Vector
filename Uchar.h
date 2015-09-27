//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright 2015+ iBean Software.
//  https://www.facebook.com/iBeanSowtware
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
#include <string>

#include "Udata.h"

const int Uchar_MAJOR_VERSION = 0;
const int Uchar_MINOR_VERSION = 12;

//Uchar keeps data in a UTF-8 format.
//
struct  Uchar
{
    std::vector <BitBull>  uc_v;
    Uchar():uc_v(0){uc_v.reserve(6);};//uc_v[0]='\x0000';};
    Uchar(std::vector<BitBull>& c):uc_v(c.size())
    {   
        if(c.size()>6)    resize(6);//making 6 max size
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=c[i];   }
    };
    ~Uchar(){if(uc_v.size())uc_v.clear();};
    Uchar(unsigned int unicode):uc_v(1)
    {   
        setUnicode(unicode); 
    };
    Uchar& operator=(const Uchar& x)
    {
        resize(x.uc_v.size());   
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=x.uc_v[i];   }
        return *this;
    };
    Uchar& operator=(unsigned int unicode)
    {
        setUnicode(unicode); 
        return *this;
    };
    size_t size() const  { return uc_v.size(); };
    void   encode(unsigned int& unicode){setUnicode(unicode);}; 
    inline void setUnicode(unsigned int& unicode)
    {   //std::isxdigit(ChatT, const std::local&)??
        if (unicode<=0x7f) 
        {
            resize(1);    
            uc_v[0]=  unicode;
        }  
        else if (unicode>=0x80 && unicode<=0x07ff) 
        {
            resize(2);    
            unsigned char temp;     
            temp=unicode;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unicode>>6;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else if (unicode>=0x0800 && unicode<=0xffff) 
        {
            resize(3);    
            unsigned char temp;     
            temp=unicode;
            uc_v[2]=temp&0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unicode>>6;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unicode>>12;
            uc_v[0]=temp&0x0f;//was 1f
            uc_v[0]=uc_v[0]|0xe0;//was c0 
        }  
        else if(unicode>=0x010000 && unicode<=0x1fffff) 
        {
            resize(4);
            unsigned char temp;     
            temp=unicode;
            uc_v[3]=temp&0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unicode>>6;
            uc_v[2]=temp&0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unicode>>12;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unicode>>18;
            uc_v[0]=temp&0x07;//was 1f
            uc_v[0]=uc_v[0]|0xf0;//was c0
        }  
        else if(unicode>=0x200000 && unicode<=0x03ffffff) 
        {
            resize(5);
            unsigned char temp;     
            temp=unicode;
            uc_v[4]=temp & 0x3f;
            uc_v[4]=uc_v[4]|0x80;
            temp=unicode>>6;
            uc_v[3]=temp & 0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unicode>>12;
            uc_v[2]=temp & 0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unicode>>18;
            uc_v[1]=temp & 0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unicode>>24;
            uc_v[0]=temp&0x03;//was 1f
            uc_v[0]=uc_v[0]|0xf8;//was c0
        }  
        else if(unicode>=0x04000000 && unicode<=0x7fffffff) 
        {
            resize(6);
            unsigned char temp;     
            temp=unicode;
            uc_v[5]=temp & 0x3f;
            uc_v[5]=uc_v[5]|0x80;
            temp=unicode>>6;
            uc_v[4]=temp & 0x3f;
            uc_v[4]=uc_v[4]|0x80;
            temp=unicode>>12;
            uc_v[3]=temp & 0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unicode>>18;
            uc_v[2]=temp & 0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unicode>>24;
            uc_v[1]=temp & 0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unicode>>30;
            uc_v[0]=temp&0x01;//was wrong
            uc_v[0]=uc_v[0]|0xfc;//was wrong
        }  
        else    uc_v[0]=0x00;
    };
    
    bool appendtostr(std::string& str)
    {
        try {
            for (size_t i=0; i<uc_v.size(); ++i) 
            {    str+= uc_v[i]; }
        } catch (...) {
            return false;
        }
         return true;
    };
    
    std::string str()
    {
        if (uc_v.size()==0) 
        { return 0x00; }
        std::string result="";
        for (size_t i=0; i<uc_v.size(); ++i) 
        {    result+= char(uc_v[i]); }
        return result;
    };
    
    //std::string ts="";
    //char jc2[3]="豆";       
    //std::cout<<jc;//dose Not work
    //ts+=jc2;//dose Not work
    //char* do not work printing most multi chars??
/*
    const char* c_str()  //still not working  
    {
        size_t sz=uc_v.size();
        if (sz==0)  { return 0x0000; }// '\x0000'
        char result[sz+1];
        //std::string result  ="";
        for (size_t i=0;i<sz; ++i) 
        {
            //result+= char(uc_v[i]);
            result[i]= char(uc_v[i]);
         //   result[i]= uc_v[i];
        }
      //  result[sz]='\n';
      //  const  char*    r=result;
     //   return r;
     return (const char*)*result; 
      //  return result.c_str();
    };
//*/
    
    private:
        void resize(size_t x)
    {
        if (uc_v.size()!=x) 
        {   
            if (uc_v.max_size()<x){  }//throw out of memory
            else {  uc_v.resize(x); }   
        }
    };       
};
#endif // iBS_Uchar_h
