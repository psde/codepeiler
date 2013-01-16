#pragma once

#include "List.hpp"
#include "String.hpp"
#include <exception>

class KeyNotFoundException : std::exception
{
  virtual const char* what() const throw()
  {
    return "Key was not found in Hashtable";
  }
};


template <class type> 
class Pair { 
	public: 
		String key; 
		type value; 

		Pair()
			: key(), value()
		{ }

		Pair(String key, type value)
			: key(key), value(value)
		{ }
}; 


template <class type> 
class Hashtable { 
	private:
		List<Pair<type> >* table;
		int size;

		int hashcode(String key)
		{
			if(key.length() == 0) return 0;

			int hash = 0;

			for(unsigned int i = 0; i < key.length(); i++)
			{
				hash = hash + (key[i] * (i+1));
			}

			return hash;
		}

		Pair<type>* getPair(String key)
		{
			int index = hashcode(key) % size;
	
			for(int i = 0; i < table[index].getSize(); i++)
			{
				if(table[index][i].key == key)
				{
					return &table[index][i];
				}
			}

			throw new KeyNotFoundException();
		}

	public: 

		/*
		 * Constructor, builds the hashtable with a certain size.
		 */
		Hashtable(int size)
			: size(size)
		{
			this->table = new List<Pair<type> >[size];
		}

		/*
		 * Deconstructor
		 */
		~Hashtable()
		{
			delete[] this->table;
		}

		/*
		 * Adds and entry to the hashtable.
		 * Returns true if the key is new, false if this is not the first element with that key
		 */
		bool put(String key, type value)
		{
			try
			{
				this->getPair(key)->value = value;
				return true;
			}
			catch(...)
			{
				table[hashcode(key) % size].append(Pair<type>(key, value));
				return false;
			}
		}

		/*
		 * Returns element by key
		 * Throws KeyNotFoundException if the key is not found
		 */
		type get(String key)
		{
			return this->getPair(key)->value;
		}

		/*
		 * Removes the key
		 */
		bool remove(String key)
		{
			int index = hashcode(key) % size;

			for(int i = 0; i < table[index].getSize(); i++)
			{
				if(table[index][i].key == key)
				{
					table[index].erase(i);
					return true;
				}
			}

			return false;
		}

		/*
		 * Checks if key is inside
		 */
		bool contains(String key)
		{
			try
			{
				Pair<type>* pair = this->getPair(key);
                pair->value = pair->value; // ... this is bad
				return true;
			}
			catch(...)
			{
				return false;
			}
		}
}; 