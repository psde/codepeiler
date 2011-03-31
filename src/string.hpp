#ifndef STRING_HPP
#define STRING_HPP

#include <ostream>

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
        
        unsigned int length()
        {
            return stringLength(this.chars);
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

        /*
          Appends a char
        */
        void operator+=(char const& c)
        {
            char* newChars = new char[stringLength(s.chars) + 2];
            
            strcpy(newChars, this->chars);
            strcat(newChars, c);

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
          
        */
        friend std::ostream& operator<<(std::ostream& os, String const& str)
        {
            os << str.chars;
            return os;
        }
};

#endif