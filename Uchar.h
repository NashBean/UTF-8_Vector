//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
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
#include <string>
#include <sstream>
#include <fstream>

const int Uchar_MAJOR_VERSION = 1;
const int Uchar_MINOR_VERSION = 5;

namespace iBS 
{
#define UnicodeInt uint32_t
      //-------
struct  u8char  //Changed struct name to match C++ standerds
{     //-------
    std::vector <unsigned char>  ref;//always keeps data in a UTF-8 format.
    
    u8char():ref(0){ref.reserve(6);};//ref[0]='\x0000';};
    u8char(std::vector<unsigned char>& c):ref(c.size())
    {   // should I just allacate here?
        if(c.size()>6)    resize(6);//making 6 max size
        for (size_t i=0; i<ref.size(); ++i) 
        {   ref[i]=c[i];   }
    };
    ~u8char(){if(ref.size())ref.clear();};
    u8char(UnicodeInt unicode):ref(1)
    {   
        setUnicode(unicode); 
    };
    u8char& operator=(const u8char& x)
    {
        resize(x.ref.size());   
        for (size_t i=0; i<ref.size(); ++i) 
        {   ref[i]=x.ref[i];   }
        return *this;
    };
    u8char& operator=(UnicodeInt unicode)
    {
        setUnicode(unicode); 
        return *this;
    };
    u8char& operator=(wchar_t& wc)
    {
        
        //setUnicode(unicode); 
        return *this;
    };
    size_t size() const  { return ref.size(); };
    void   encode(unsigned int& unicode){setUnicode(unicode);}; 
    
    bool appendtostr(std::string& str)
    {
        try { for(size_t i=0; i<ref.size(); ++i) 
                { str+= ref[i]; } } 
        catch (...) { return false; }
        return true;
    };
    inline void setUnicode(UnicodeInt unicode)
    { //converts unicode into UTF-8 formatted u8char  
        if (unicode<=0x7f) 
        {
            resize(1);    
            ref[0]=  unicode;
        }  
        else if (unicode>=0x80 && unicode<=0x07ff) 
        {
            resize(2);    
            unsigned char temp;     
            temp=unicode;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>6;
            ref[0]=temp&0x1f;
            ref[0]=ref[0]|0xc0;
        }  
        else if (unicode>=0x0800 && unicode<=0xffff) 
        {
            resize(3);    
            unsigned char temp;     
            temp=unicode;
            ref[2]=temp&0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>6;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>12;
            ref[0]=temp&0x0f;
            ref[0]=ref[0]|0xe0;
        }  
        else if(unicode>=0x010000 && unicode<=0x1fffff) 
        {
            resize(4);
            unsigned char temp;     
            temp=unicode;
            ref[3]=temp&0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>6;
            ref[2]=temp&0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>12;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>18;
            ref[0]=temp&0x07;
            ref[0]=ref[0]|0xf0;
        }  
        else if(unicode>=0x200000 && unicode<=0x03ffffff) 
        {
            resize(5);
            unsigned char temp;     
            temp=unicode;
            ref[4]=temp & 0x3f;
            ref[4]=ref[4]|0x80;
            temp=unicode>>6;
            ref[3]=temp & 0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>12;
            ref[2]=temp & 0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>18;
            ref[1]=temp & 0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>24;
            ref[0]=temp&0x03;
            ref[0]=ref[0]|0xf8;
        }  
        else if(unicode>=0x04000000 && unicode<=0x7fffffff) 
        {
            resize(6);
            unsigned char temp;     
            temp=unicode;
            ref[5]=temp & 0x3f;
            ref[5]=ref[5]|0x80;
            temp=unicode>>6;
            ref[4]=temp & 0x3f;
            ref[4]=ref[4]|0x80;
            temp=unicode>>12;
            ref[3]=temp & 0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>18;
            ref[2]=temp & 0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>24;
            ref[1]=temp & 0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>30;
            ref[0]=temp&0x01;
            ref[0]=ref[0]|0xfc;
        }  
        else    ref[0]=0x00;
    };
    
    std::string str()
    {
        if (ref.size()==0) 
        { return ""; }
        std::stringstream result;
        try { for (size_t i=0; i<ref.size(); ++i) 
                { result<< char(ref[i]); } } 
        catch (...) { return "str:error"; }
        return result.str();
    };
    
    private:
        void resize(size_t x)
    {
        if (ref.size()!=x) 
        {   
            if (ref.max_size()<x){  }//throw out of memory
            else {  ref.resize(x); }   
        }
    };       
};
      
struct u8str
{
    std::vector<u8char> ref;
    
    void append(u8char uc){ref.push_back(uc);};
    
    size_t u8char_count(){return ref.size();};
    size_t unsignedchar_count()
    {   size_t s=0;
        for (size_t rs=0;rs<ref.size(); ++rs) 
        {   s+=ref[rs].ref.size();  }
        return s;
    };
   
    void appendtostr(std::string& str)
    {
        if (ref.size()) 
        {
            for (size_t i=0; i<ref.size(); ++i) 
                ref[i].appendtostr(str);
        }
    };
 
};
    
    
//-------------------------------
//      UsefulFunctions
//-------------------------------
    //bool isLeadByte(unsigned char byte); //use ByteCount 
    short ByteCount(unsigned char byte) 
    {//  returns 0 if not lead byte or not UTF-8 formated 
        if ((byte & 0x80)==0) { return 1; }
        short result=0;
        if (byte & 0x80) result++;
        if (byte & 0x40) result++;
        if (result != 2) return 0;//this was not lead byte or not UTF-8 format 
      //  else return result;
        if (byte & 0x10) result++;
        else return result;
        if (byte & 0x08) result++;
        else return result;
        if (byte & 0x04) result++;  
        else return result;
        if (byte & 0x02) return -1;//this was not UTF-8 format  
        return result;
    };
    //-------------------------------
    
    bool isTrailByte(unsigned char byte)
    { return (byte & 0x80)&&((byte & 0x40)==0); };
    //-------------------------------
    
    
    //  not   working at moment
    void readu8file(std::string filename,u8str& u8_v)
    {
        std::ifstream    fin  ;  
        fin.open(filename.c_str());
        if (fin.fail()) {return;} 

        unsigned char  temp=0;   
        u8char   u8temp=u8char();
        unsigned short sz=0;  
        std::vector<unsigned char> ref; 
        ref.reserve(6);
  
        
        if (u8_v.ref.size())u8_v.ref.clear();
       // u8_v.ref.reserve(sizeof(fin));
        while(fin >> temp)
        {
            if (isTrailByte(temp)) {
                ref.push_back(temp);  
                --sz;
                //if(sz<0) // too many TrailBytes
            }
            else
            {
                sz = ByteCount(temp);  
                if (ref.size()) 
                {
                    u8_v.append(u8char(ref));
                    ref.clear();
                }
                //ref.resize(sz);
                ref.push_back(temp);
                --sz;
            }
        }
        if (ref.size()) 
        {
            u8_v.append(u8char(ref));
            ref.clear();
        }
        
        fin.close();
    };    
    //-------------------------------
    
    inline UnicodeInt decode(u8char& c)//returns a Unicode
    {
        unsigned int result=0;
        if (c.size()==0) { return result;}
        if (c.size()==1) { return (result +=c.ref[0]); }
        if (c.size()==2) { result=c.ref[0] & 0x1f; }
        else if (c.size()==3) { result=c.ref[0] & 0x0f; }
        else if (c.size()==4) { result=c.ref[0] & 0x07; }
        else if (c.size()==5) { result=c.ref[0] & 0x03; }
        else if (c.size()==6) { result=c.ref[0] & 0x01; }
        for (size_t i=1; i<c.size(); ++i) 
        { result=result<<6; result+=c.ref[i] & 0x3f; }
        return result;
    };   
    //-------------------------------
    
     struct unicode_string
    {
        std::vector<UnicodeInt> ref;   
        
        bool appendtostr(std::string& str)
        {
            try {u8char u8c=u8char();
                for(size_t i=0; i<ref.size(); ++i) 
                { u8c.encode(ref[i]); u8c.appendtostr(str);} } 
            catch (...) { return false; }
            return true;
        };
        
    };
    
    
}//end of namespace iBS 

#endif // iBS_u8char_h
