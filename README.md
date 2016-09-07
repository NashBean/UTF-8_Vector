# UTF-8_Vector
# Unicode API for C++

Is a UTF-8 Formatted cross-platform CharT, string, or text in C++.
Include 32 bit int formatted version of the above.

Creates a UTF-8 vector of unsigned char from a char, wchat_t, any unicode value, and std::string.

Simply by putting the Uchar.h header file in your C++ project you can have a 
iBS::u8char object for a unaversal char, c++ compliant container.
Strait from a file into memory in the same format. No converting back and forth.

Can do conversions if needed.
For example it can take in any Unicode
and stores it in UTF-8 format:
iBS::u8char uc = 0x03a9;//Ω 
std::cout << uc.str() ;

<***--- Main Header File Uchar.h ---***>

    Defines iBS::UnicodeInt as uint32_t a 32 bit integer,
    could be changed in one spot into uint64_t.

        - UnicodeInt represents any Unicode integer value.

            http://unicode.org/
            https://en.wikipedia.org/wiki/Unicode

*** iBS::u8char struct v2.2 is up and running. ***

        It is a UTF-8 formated container that holds a muti-byte unsigned char.
        It uses a std::vector to hold 0 - 6 unsigned char s that make up
        any UTF-8 formatted charT today and all the room Unicode has 
        reserved to ever use. 

        --- Constructors ---
        u8char()
        u8char(std::vector<unsigned char>& c)
        u8char(UnicodeInt unicode)
        u8char(wchar_t ch):ref(1)

        --- Operators ---
        u8char& operator=( u8char const& x) // copy operator
        u8char& operator=(UnicodeInt unicode)
        u8char& operator=(char ch)
        u8char& operator=(wchar_t& wc)

        --- Functions ---
        size_t size() const 
        void   encode(unsigned int& unicode) 
        inline void setUnicode(UnicodeInt unicode)
        bool appendtostr(std::string& str)
        bool appendtostr(std::stringstream& str) // faster then std::string
        std::string str()
        



    ***  iBS::u8str ***

        A simple container that holds any UTF-8 formatted string 

        --- Functions ---

        void append(u8char uc)
        size_t u8char_count()   //Idea to use for letter count
        size_t unsignedchar_count()
        void appendtostr(std::string& str)
        std::string str()

        
   *** iBS::Global Functions ***

        - short iBS::ByteCount(unsigned char byte) 
            returns 0 if not lead byte or -1 when not UTF-8 formated 
            else returns number of ,8 bit bytes, it takes to contain it. 

        -  bool iBS::isTrailByte(unsigned char byte) 
            returns true if it is a trailing byte in UTF-8 format   

        - void iBS::readu8file(std::string filename,u8str& u8_v)
            Fills u8str with the complete UTF-8 formatted file at filename
            Reads all of file filling each u8char one part at a time.
            Each u8char will represent one Unicode.
            Idea for finding problem in corrupted file. 
            
        - UnicodeInt iBS::Decode(u8char& u8c) 
            returning a Unicode as an uint32_t.
            unsigned int unicode = uc.Decode();   



        inline UnicodeInt decode(std::vector<char>& c)
        inline UnicodeInt decode(wchar_t& wch)


    *** iBS::uchar  ***
    Unlike u8char, uchar holds(in memory) the char value as a single byte unsigned 32 bit integer.
    It also is a standed c++ compliant container that can hold any Unicode.
    It is acts the same way as the traditional char struct, ecept it holds the larger uint32_t
    insted of the unsined 8 bit integer.

    --- Constructors ---
    uchar()
    uchar(int v) 
    uchar(long v)
    uchar(UnicodeInt v)
    uchar(char v)
    uchar(uchar const &v)
    uchar(wchar_t wch)

    --- Operators ---
    uchar& operator=(int unicode)
    uchar& operator=(UnicodeInt unicode)
    uchar& operator=(char ch) 
    uchar& operator=(uchar const& uch) 
    uchar& operator=(wchar_t wch)

    bool operator==(int i)
    bool operator==(UnicodeInt unicode) 
    bool operator==(char c)
    bool operator==(uchar uch) 

    bool operator<(UnicodeInt unicode)
    bool operator>(UnicodeInt unicode)
    bool operator<=(UnicodeInt unicode)
    bool operator>=(UnicodeInt unicode) 

    --- Functions ---
    UnicodeInt get()
    void set(UnicodeInt v) 
    void set(uchar uch)
    void set(wchar_t wch)
    UnicodeInt lower_case()
    UnicodeInt upper_case()


   ******* iBS::ustr *******
        A container that holds a vector of UnicodeInt to store raw Unicodes

        Raw Unicodes makes for a good string or file format,
        UTF-8 if based on Unicode Int,
        converts easer then UTF-16, no Big and Little Idian,
        more compact then UTF-32,
        backwards compadable with ANSII and more.


    --- Constructors ---
    ustr()
    ustr(UnicodeInt unicode):ref(1) { ref[0] = unicode; };
    ustr(char ch):ref(1) { ref[0] = ch; };
    ustr(wchar_t wch):ref(1) { ref[0] = wch; };
    working on ustr(std::vector<unsigned char>& raw_utf8) 
    working on ustr(unsigned char* raw_utf8) 
    working on ustr(std::string str):ref(str.size()) 

    --- Operators ---
    ustr& operator=(ustr const& x)
    ustr& operator=(char ch)
    ustr& operator=(wchar_t& wc)


        --- Functions ---
    size_t size() const    
    std::string str()
    todo    size_t u8char_count()
    todo ...


Ufunc.h 
    bool iBS::isOn(unsigned char byte, short index)
    void iBS::display_bits(unsigned char uc)
    void iBS::display_bits(unsigned short us)
    void iBS::display_bits(unsigned int ui)
    void iBS::display_bits(int i)
    void iBS::display_bits(size_t i)

Unum.h     removed in v2.0    
Udata.h    removed in v2.0
    

---------------------------------------------------------------------------------------------

Note: Even though Bjarn Stroustrup was not a direct contributor.  His vector was used and his lectures were a big influence.
