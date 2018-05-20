//
//  Uchar.h
//  Get cureent version off Github:
//  https://github.com/NashBean/UTF-8_Vector/blob/master/Uchar.h
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
#include <cwchar>

const int Uchar_MAJOR_VERSION = 2;
const int Uchar_MINOR_VERSION = 4;

namespace iBS 
{
#define UnicodeInt uint64_t
      //-------
struct  u8char  //Changed struct name to match C++ standerds
{     //-------
    std::vector <unsigned char>  ref;//always keeps data in a UTF-8 format.
    
    u8char():ref(0){ref.reserve(1);};//ref[0]='\x0000';};
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
    u8char(char ch):ref(1)
    {   
        setUnicode((UnicodeInt)ch); 
    };
    u8char(wchar_t ch):ref(1)
    {   
        char temp[6];
        std::mbstate_t state ;
        int ret = std::wcrtomb((&temp[0]), ch, &state);
        ref.resize(ret);
        for (short i=0; i<ret; ++i) 
            ref[i]=temp[i];
    };
    u8char& operator=( u8char const& x)
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
    u8char& operator=(char ch)
    {
        setUnicode((UnicodeInt)ch); 
        return *this;
    };
    u8char& operator=(wchar_t& wc)
    {
        char temp[6];
        std::mbstate_t state ;
        int ret = std::wcrtomb((&temp[0]), wc, &state);
        ref.resize(ret);
        for (short i=0; i<ret; ++i) 
            ref[i]=temp[i];
        return *this;
    };
    size_t size() const  { return ref.size(); };
    void   encode(unsigned int& unicode){setUnicode(unicode);}; 
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
    bool appendtostr(std::string& str)
    {
        try { for(size_t i=0; i<ref.size(); ++i) 
        { str+= ref[i]; } } 
        catch (...) { return false; }
        return true;
    };
    bool appendtostr(std::stringstream& str)
    {
        try { for(size_t i=0; i<ref.size(); ++i) 
        {  str<< char(ref[i]); } } 
        catch (...) { return false; }
        return true;
    };
    std::string str()
    {
        if (ref.size()==0) 
        { return ""; }
        std::stringstream result;
        try { for (size_t i=0; i<ref.size(); ++i) 
                { result<< char(ref[i]); } } 
        catch (...) { return "u8error"; }
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
//----------------------------------------------------------    
//
//----------------------------------------------------------    

    
typedef struct u8str
{
    std::vector<u8char> ref;
    
    void append(u8char uc){ref.push_back(uc);};
    void append(char ch){ref.push_back(u8char(ch));};
    
    size_t u8char_count(){return ref.size();};
    size_t size()// returns total count of unsigned char
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

    std::string str()
    {
        if (ref.size()==0) 
        { return ""; }
        std::stringstream result;
        for (size_t i=0; i<ref.size(); ++i) 
            ref[i].appendtostr(result);
        
        return result.str();
    };
 
};
    
    
//-------------------------------
//      Useful UTF-8 Functions
//-------------------------------
    //bool isLeadByte(unsigned char byte); //use ByteCount 
    
    bool isTrailByte(unsigned char byte)
    { return (byte & 0x80)&&((byte & 0x40)==0); };
    //-------------------------------
    
    short ByteCount(unsigned char byte) 
    {//  returns 0 if not lead byte or -1 if not UTF-8 formated 
        if ((byte & 0x80)==0) { return 1; }
        short result=0;
        if (byte & 0x80) result++;
        if (byte & 0x40) result++;
        if (result != 2) 
        {   if(isTrailByte(byte)) return 0;//this was not lead byte
            else return -1;//this was not UTF-8 format 
        }
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
    
    void readu8file(std::string filename,u8str& u8_v)
    {
        std::ifstream    fin  ;  
        fin.open(filename.c_str());
        if (fin.fail()) {return;} 

        unsigned char  temp=0;   
        u8char   u8temp=u8char();
        unsigned short sz=0;  
        std::vector<unsigned char> ref; 
        ref.reserve(1);
  
        
        if (u8_v.ref.size())u8_v.ref.clear();
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
        UnicodeInt result=0;
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
    
    
    
    
    //---------------------------------------------------------------
    // next group keeps a Unicode as a single 32 bit Unsigned Integer
    //---------------------------------------------------------------
/*    
    struct uint 
    {
        uint():value(0){}; 
        uint(int v):value((uint32_t)v){}; 
        uint(long v):value((uint32_t)v){}; 
        uint(char v):value((uint32_t)v){}; 
        uint(uint const &v):value(v.value){}; 
        uint(uint32_t v):value(v){}; 
        
        uint& operator=(uint unicode) { set(unicode.value); return *this; };
        uint& operator=(uint32_t unicode){ set(unicode); return *this; };
        uint& operator=(char ch) { set((uint32_t)ch); return *this; };
        
        uint& operator+(uint32_t unicode){ set(value+unicode); return *this; };
        uint& operator-(uint32_t unicode){ set(value-unicode); return *this; };
        
        bool operator==(char c) { std::string str; return (value == (uint32_t)c); };
        bool operator==(int i) { return (value == (uint32_t)i); };
        bool operator==(uint32_t unicode) { return (value == unicode); };
        bool operator==(uint unicode) { return (value == unicode.get()); };
        bool operator<(uint32_t unicode) { return (value < unicode); };
        bool operator>(uint32_t unicode) { return (value > unicode); };
        bool operator<=(uint32_t unicode) { return (value <= unicode); };
        bool operator>=(uint32_t unicode) { return (value >= unicode); };
        
        uint32_t get() { return value; };
        void set(uint32_t v) { value = v; };
        void set(uint v) { value = v.value; };
        
        
    private:    
        uint32_t value;
        
    };
 //*/   
    //-----------------------------------------------
    //inline function for uint 
    //-----------------------------------------------
    inline UnicodeInt decode(std::vector<char>& c)
    {
        uint32_t result = uint32_t(0);
        
        //UnicodeInt result=0;
        if (c.size()==0) { return UnicodeInt(result);}
        if (c.size()==1) { return UnicodeInt(c[0]); }
        if (c.size()==2) { result=c[0] & 0x1f; }
        else if (c.size()==3) { result=c[0] & 0x0f; }
        else if (c.size()==4) { result=c[0] & 0x07; }
        else if (c.size()==5) { result=c[0] & 0x03; }
        else if (c.size()==6) { result=c[0] & 0x01; }
        for (size_t i=1; i<c.size(); ++i) 
        { result=result<<6; result+=c[i] & 0x3f; }
        
        
        return UnicodeInt(result);
    };
    
    inline UnicodeInt decode(wchar_t& wch)
    {
        //  uint result = uint();
        
        
        //*  test more
        char temp[6];
        std::vector<char> ref;
        std::mbstate_t state ;
        int ret = std::wcrtomb((&temp[0]), wch, &state);
        
        ref.resize(ret);
        for (short i=0; i<ret; ++i) 
            ref[i]=temp[i];
        //*/
        return decode(ref);
    };
    
    struct raw_u8str 
    {
        std::vector <unsigned char> ref;
    };
    
    //-----------------------------------------------
    //uchar = uint made to hold any char of the world
    //-----------------------------------------------
    
    struct uchar
    {
    private:    
        UnicodeInt value;

    public:
        uchar():value(0){}; 
        uchar(int v):value(v){}; 
        uchar(long v):value(v){}; 
        uchar(UnicodeInt v):value(v){}; 
        //uchar(uint v):value(v.get()){}; 
        uchar(char v):value((uint32_t)v){}; 
        uchar(uchar const &v):value(v.value){}; 
        uchar(wchar_t wch):value(decode(wch)){}; 
        
        UnicodeInt get() { return value; };
        void set(UnicodeInt v) { value = v; };
        //uint get() { return value; };
        //void set(uint v) { value = v; };
        void set(uchar uch) { value = uch.value; };
        void set(wchar_t wch) { value = decode(wch); };
        void set(int64_t i64) { set((UnicodeInt)i64); };
        
        uchar& operator=(int unicode){ set((UnicodeInt)unicode); return *this; };
        uchar& operator=(UnicodeInt unicode){ set(unicode); return *this; };
        //uchar& operator=(uint unicode) { set(unicode); return *this; };
        uchar& operator=(char ch) { set((UnicodeInt)ch); return *this; };
        uchar& operator=(uchar const& uch) { set(uch); return *this; };
        uchar& operator=(wchar_t wch) { set(wch); return *this; };
        uchar& operator=(int64_t i64) { set((UnicodeInt)i64); return *this; };
        
        bool operator==(int i) { return (value == i); };
        bool operator==(UnicodeInt unicode) { return (value == unicode); };
        //bool operator==(uint unicode) { return (value == unicode); };
        bool operator==(char c) { return (value == c); };
        bool operator==(uchar uch) { return (value == uch.value); };
        
        bool operator<(UnicodeInt unicode) { return (value < unicode); };
        bool operator>(UnicodeInt unicode) { return (value > unicode); };
        bool operator<=(UnicodeInt unicode) { return (value <= unicode); };
        bool operator>=(UnicodeInt unicode) { return (value >= unicode); };

        UnicodeInt lower_case() { if(value>=65 && value<=90) return (value+32); else return value;};
        UnicodeInt upper_case() { if(value>=97 && value<=122) return (value-32); else return value;};
        
    };
    
    //------------------------------------------------------------------
    // ustr = the last string container you will ever need!!!
    //------------------------------------------------------------------
    
    struct ustr
    {
        ustr():ref(0){ref.reserve(1);};//ref[0]='\x0000';};
        // ustr(std::vector<unsigned char>& c):ref(c.size())
        // {   // should I just allacate here?
        //     for (size_t i=0; i<ref.size(); ++i) 
        //     {   ref[i]=c[i];   }
        // };
        ~ustr(){if(ref.size())ref.clear();};
        ustr(UnicodeInt unicode):ref(1) { ref[0] = unicode; };
        ustr(char ch):ref(1) { ref[0] = ch; };
        ustr(wchar_t wch):ref(1) { ref[0] = wch; };
        ustr(std::vector<unsigned char>& raw_utf8):ref(0) 
        { 
            //todo
        };
        ustr(unsigned char* raw_utf8):ref(0) 
        { 
            //todo
        };
        ustr(std::string str):ref(str.size()) 
        { 
            //todo
        };
        
        ustr& operator=(ustr const& x)// required by C++ for vector
        {
            ref.resize(x.ref.size());   
            for (size_t i=0; i<ref.size(); ++i) 
            {   ref[i]=x.ref[i];   }
            return *this;
        };
        ustr& operator=(char ch)
        {
            ref.resize(1);
            ref[0] = ch;
            return *this;
        };
        ustr& operator=(wchar_t& wc)
        {
            ref.resize(1);
            ref[0] = wc;
            return *this;
        };
        size_t size() const  { return ref.size(); };    
        
        std::string str()
        {
            if (ref.size()==0) 
            { return ""; }
            std::stringstream result;
            uchar temp = uchar();
            for (size_t i=0; i<ref.size(); ++i) 
            {
                temp = ref[i];
      //todo!          temp.appendtostr(result);// todo uchar.appendtostr(std::stringstream& result)
            }
            return result.str();
        };
        
        
    private:    
        std::vector<uchar> ref;
    };
    
    //-----------------------------------------------------------------------------
    // utext = string list container saved as a uint32_t multi leangth col sized grid
    //-----------------------------------------------------------------------------
    struct utext
    {
        utext():ref(0){ref.reserve(1);};
        // ustr(std::vector<unsigned char>& c):ref(c.size())
        // {   // should I just allacate here?
        //     for (size_t i=0; i<ref.size(); ++i) 
        //     {   ref[i]=c[i];   }
        // };
        ~utext(){if(ref.size())ref.clear();};
        utext(UnicodeInt unicode):ref(1) { ref[0] = unicode; };
        utext(char ch):ref(1) { ref[0] = ch; };
        utext(wchar_t wch):ref(1) { ref[0] = wch; };
        utext(std::vector<unsigned char>& raw_utf8):ref(0) 
        { 
            //todo
        };
        utext(unsigned char* raw_utf8):ref(0) 
        { 
            //todo
        };
        utext(std::string str):ref(1) 
        { 
            ref[0] = str;
        };
        
        utext& operator=(utext const& x)// required by C++ for vector
        {
            ref.resize(x.ref.size());   
            for (size_t i=0; i<ref.size(); ++i) 
            {   ref[i]=x.ref[i];   }
            return *this;
        };
        utext& operator=(char ch)
        {
            ref.resize(1);
            ref[0] = ch;
            return *this;
        };
        utext& operator=(wchar_t& wc)
        {
            ref.resize(1);
            ref[0] = wc;
            return *this;
        };
        size_t size() const  { return ref.size(); };    
        
        std::string str(size_t index)
        {
             return ref[index].str();
        };
        
    private:    
        std::vector<ustr> ref;
    };

    
    
}//end of namespace iBS 

#endif // iBS_u8char_h
