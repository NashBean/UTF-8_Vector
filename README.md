# UTF-8_Vector

Is a UTF-8 Char in C++

Creates a UTF-8 vector of <unsigned char> from a Unicode.

Note: Even though Bjarn Stroustrup was not a direct contributor.  His vector was used and his lectures were a big influence.

UTF-8_Vector Lib Consist:

Simply by putting this header in your C++ project you can have a 
container for a single UTF-8 char.

Uchar.h
    Defines iBS::UnicodeInt as uint32_t

    iBS::u8char struct v1.5 is ready and wider then a wchat_t

        - size_t size() const 

        - Encode from an UnicodeInt to UTF-8 formatted Uchar.
            iBS::Uchar uc = 0x03a9;//Ω  

        - bool appendtostr(std::string& str)


    iBS::u8str
        - void append(u8char uc);

        - size_t u8char_count();
            Idea to use for letter count

        - size_t unsignedchar_count()

        - void appendtostr(std::string& str)

        
    iBS::Global Functions

        - short iBS::ByteCount(unsigned char byte) 
            returns 0 if not lead byte or not UTF-8 formated 
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

    iBS::unicode_string

        - std::vector<UnicodeInt> ref;   
            a vector of UnicodeInt to store raw Unicodes

        - bool iBS::appendtostr(std::string& str)


l appendtostr(std::string& str)


Ufunc.h 
    bool iBS::isOn(unsigned char byte, short index)
    void iBS::display_bits(unsigned char uc)
    void iBS::display_bits(unsigned short us)
    void iBS::display_bits(unsigned int ui)
    void iBS::display_bits(int i)
    void iBS::display_bits(size_t i)

Unum.h      // under construction, new formate for a compact string number 
    
    struct  unum    //unaversal  number
        //hex = 0x0-0x9==0-9  a==A b==+ c==- d==. e==∞ f==Ω
        // a0 ff = 0
        // ac 3d 14 ff = -3.14
        // ae ff = ∞ 
        // start() = a+1 = Alfa+1
        // end() = ff = ΩΩ = Omega
        unum& operator=(const unum& x)
        size_t size() const 
        bool  is_signed()
        bool has_dec(){return dec_index;};   
        unum& operator=(int& x)

Udata.h  
    inop, still under construction.

