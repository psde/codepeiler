#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <list>
#include <exception>

using namespace std;

class KeyNotFoundException : exception
{
  virtual const char* what() const throw()
  {
    return "Key was not found in Hashtable";
  }
};

template <class type> 
class Pair { 
    public: 
        string key; 
        type value; 

        Pair(string key, type value)
            : key(key), value(value)
        { }
}; 


template <class type> 
class Hashtable { 
    private:
        list<Pair<type> >* table;
        int size;

        int hashcode(string key)
        {
            if(key.length() == 0) return 0;

            int hash = 0;

            for(unsigned int i = 0; i < key.length(); i++)
            {
                hash = hash + (key[i] * (i+1));
            }

            return hash;
        }

        Pair<type>* getPair(string key)
        {
            int index = hashcode(key) % size;

            for(list<Pair<type> >::iterator it = table[index].begin(); it != table[index].end(); ++it)
            {
                if((*it).key == key)
                {
                    return &(*it);
                }
            }
            throw new KeyNotFoundException();
        }

    public: 
        Hashtable(int size)
            : size(size)
        {
            this->table = new list<Pair<type>>[size];
        }

        ~Hashtable()
        {
            delete[] this->table;
        }

        bool put(string key, type value)
        {
            try
            {
                this->getPair(key)->value = value;
                return true;
            }
            catch(...)
            {
                table[hashcode(key) % size].push_back(Pair<type>(key, value));
                return false;
            }
        }

        type get(string key)
        {
            return this->getPair(key)->value;
        }

        bool remove(string key)
        {
            int index = hashcode(key) % size;

            for(list<Pair<type> >::iterator it = table[index].begin(); it != table[index].end(); ++it)
            {
                if((*it).key == key)
                {
                    table[index].erase(it);
                    return true;
                }
            }

            return false;
        }

        bool contains(string key)
        {
            try
            {
                Pair<type>* pair = this->getPair(key);
                return true;
            }
            catch(...)
            {
                return false;
            }
        }
}; 

#endif
