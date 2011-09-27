#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <ostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>

class String
{
    private:
        char* chars;

        /*
          Returns the length of a char array
        */
        unsigned int stringLength(char const *string)
        {
            unsigned int length;

            for(length = 0; string[length] != '\0'; length++)
            { }

            return length;
        }

    public:
        /*
          Constructor with no arguments
        */
        String()
        {
            this->chars = new char[1];
            this->chars[0] = '\0';
        }

        /*
          Constructor with passed char array
        */
        String(char const *s)
        {
            this->chars = new char[stringLength(s) + 1];
            strcpy(this->chars, s);
        }

        /*
          Constructor with passed string object
        */
        String(String const &stringObj)
        {
            this->chars = new char[stringLength(stringObj.chars) + 1];
            strcpy(this->chars, stringObj.chars);
        }

        /*
          Deconstructor
        */
        ~String()
        {
            delete[] this->chars;
        }
        
        /*
          Returns interpreted long
        */
        long toLong()
        {
            return strtol(this->chars, NULL, 10);
        }
        
        /*
          Returns interpreted unsigned long
        */
        unsigned long toULong()
        {
            unsigned long l = strtoul(this->chars, NULL, 10);
            if(errno == ERANGE)
            {
                errno = 0;
                throw std::range_error("Could not convert to unsigned long");
            }
            return l;
        }

        /*
          Returns the string length
        */
        unsigned int length()
        {
            //return stringLength(this.chars);
            unsigned int length;

            for(length = 0; this->chars[length] != '\0'; length++)
            { }

            return length;

        }

        /*
          Returns the char at a passed index 
        */
        char& operator[](int index)
        {
            return this->chars[index];
        }

        /*
          Sets the string to a passed string object
        */
        void operator=(String const& s)
        {
            delete[] this->chars;
            this->chars = new char[stringLength(s.chars) + 1];
            strcpy(this->chars, s.chars);
        }

        String operator+(const char *c1)
        {
            String str(this->chars);
            String str2(c1);
            str += str2;
            return str;
        }

        String operator+(const String &s)
        {
            String str(this->chars);
            str += s;
            return str;
        }

        void operator+=(int const& l)
        {
            char buf[sizeof(int)*8+1];
            sprintf(buf, "%i", l);

            unsigned int length = stringLength(this->chars) + stringLength(buf) + 1;
            char* newChars = new char[length];
            
            strcpy(newChars, this->chars);
            newChars[length-1] = 0x00;

            for(unsigned int i=stringLength(this->chars); i<length-1; i++)
            {
                newChars[i] = buf[i-stringLength(this->chars)];
            }

            delete[] this->chars;
            this->chars = newChars;
        }

        /*
          Appends a long
        */
        void operator+=(long const& l)
        {
            char buf[sizeof(long)*8+1];
            sprintf(buf, "%ld", l);

            unsigned int length = stringLength(this->chars) + stringLength(buf) + 1;
            char* newChars = new char[length];
            
            strcpy(newChars, this->chars);
            newChars[length-1] = 0x00;

            for(unsigned int i=stringLength(this->chars); i<length-1; i++)
            {
                newChars[i] = buf[i-stringLength(this->chars)];
            }

            delete[] this->chars;
            this->chars = newChars;
        }


        /*
          Appends a char
        */
        void operator+=(char const& c)
        {
            unsigned int length = stringLength(this->chars) + 2;
            char* newChars = new char[length];
            
            strcpy(newChars, this->chars);
            newChars[length-2] = c;
            newChars[length-1] = 0x00;

            delete[] this->chars;
            this->chars = newChars;
        }
        
        /*
          Appends a string
        */
        void operator+=(String const& s)
        {
            char* newChars = new char[stringLength(s.chars) + stringLength(this->chars) + 1];
            
            strcpy(newChars, this->chars);
            strcat(newChars, s.chars);

            delete[] this->chars;
            this->chars = newChars;
        }

        /*
          Checks for equality
        */
        bool operator==(String const& s)
        {
            if(this->length() != stringLength(s.chars))
                return false;

            for(unsigned int i=0; i<=this->length(); i++)
            {
                if(this->chars[i] != s.chars[i])
                    return false;
            }
            return true;
        }

        /*
          << blah   
        */
        friend std::ostream& operator<<(std::ostream& os, String const& str)
        {
            os << str.chars;
            return os;
        }

        const char* getChars()
        {
            return this->chars;
        }
};

#endif
