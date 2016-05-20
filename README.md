# UTF-8_Vector

Is a UTF-8 Formatted Char in C++

Creates a UTF-8 vector of <unsigned char> from a Unicode.

UTF-8_Vector Lib Consist:

Simply by putting the Uchar.h header file in your C++ project you can have a 
iBS::u8char object for a UTF-8 formatted muti char, c++ compliant container.
Strait from a file into memory in the same format. No converting back and forth.

Can do conversions if needed for example it can take in any Unicode
and stores it in UTF-8 format using std::vector:
iBS::u8char uc = 0x03a9;//Ω 
std::cout << uc.str() ;

<***--- Main Header File Uchar.h ---***>

    Defines iBS::UnicodeInt as uint32_t a 32 bit integer

        - UnicodeInt represents any Unicode integer value.

            http://unicode.org/
            https://en.wikipedia.org/wiki/Unicode

*** iBS::u8char struct v2.0 is up and running. ***

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

   ******* iBS::unicode_string *******
        A container that holds a vector of UnicodeInt to store raw Unicodes

        Raw Unicodes makes for a good string or file format,
        UTF-8 if based of Unicode Int,
        converts easer then UTF-16, no Big and Little Idian,
        more compact then UTF-32,
        backwards compadable with ANSII and more.


        --- Functions ---
        void append(UnicodeInt uci)
        void append(char c)
        void append(u8char uc)
        size_t u8char_count()
        bool iBS::appendtostr(std::string& str)
        std::string str()
        std::vector<UnicodeInt>& vector()



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
