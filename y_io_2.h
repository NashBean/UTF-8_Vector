#ifndef Y_IO_2_GUARD//See Yager, R.J. "Reading, Writing, and Parsing Text
#define Y_IO_2_GUARD//Files Using C++ (Updated)" (2014)
#include <cstdio>//..fclose(),FILE,fopen(),fseek(),ftell(),printf(),SEEK_END,...
#include <cstdlib>//......................................................exit()
#include <cstring>//................memset(),strchr(),strlen(),strstr(),strtok()
#include <vector>//.......................................................vector
namespace yIo2
{

  inline char* ReadTextFile(const char*f)
{
    FILE*F=fopen(f,"rb");/*->*/if(!F)printf("\nCan't find \"%s\".\n",f),exit(1);
    unsigned n;/*<-*/fseek(F,0,SEEK_END),n=ftell(F),rewind(F);
    char*s=new char[n+1];/*<-*/fread(s,1,n,F),fclose(F),s[n]=0;
    return s;
}

inline unsigned WriteTextFile(const char*f, const char*s,const char*m="wb")
{//<---------------USE "wb" TO OVERWRITE, "ab" TO APPEND
  FILE*F=fopen(f,m);/*->*/if(!F)printf("\nCan't open \"%s\".\n",f),exit(1);
  unsigned n=fwrite(s,1,strlen(s),F);/*&*/fclose(F);
  return n;//.........................number of characters written to the file
}

inline char*RemoveLineComments(char*s, const char*c="#",char r=' ')
{
  for(char*t=s;t=strstr(t,c);memset(t,r,strcspn(t,"\n\f\r")));
  return s;
}

inline char*RemoveBlockComments(char*s,const char*c="/*", const char*e="*/", char r=' ')
{
  int m=strlen(c),n=strlen(e);
  for(char*t=s,*u;t=strstr(t,c);memset(t,r,u-t+n))if(!(u=strstr(t+m,e)))break;
  return s;
}
  
inline std::vector<char*>Parse(char*s,const char*d=" ,\t\n\f\r")
{
std::vector<char*>V;/*<-*/for(s=strtok(s,d);s;s=strtok(0,d))V.push_back(s);
return V;
}
  
inline std::vector<std::vector<char*> >Parse2D(char*s,const char*d=" ,\t",const char*e="\n\f\r")
{
  std::vector<std::vector<char*> >V;
  char*b,*c=new char[strlen(d)+strlen(e)+1];
  for(strcat(strcpy(c,d),e);*(b=s+strspn(s,c));V.push_back(Parse(b,d)))
  s=b+strcspn(b,e),!*s?s:(*s=0,++s);
  delete[]c;
  return V;//.........the number of columns per row may differ from row to row
}
  
inline char*PreParse(char*s,const char*b="\"",const char*e="\"",const char*d=" ,\t\n\f\r",char r='#')
{
  const char*u;
  for(char*t=s,c=0;*t;++t)
  {
    if(strchr(d,*t)&&!c)*t=r;
    else if(strchr(b,*t))u=b,b=e,e=u,c&1?++c:--c;
    else if(strchr(e,*t))u=b,b=e,e=u,c&1?--c:++c;
  }
  return s;
}
}
#endif
