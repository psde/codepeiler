#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "List.hpp"
#include "String.hpp"
#include <exception>

//using namespace std;

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
		 * Konstruktor
		 * Nimmt einen Integer an, der die Größe der Tabelle festlegt.
		 */
		Hashtable(int size)
			: size(size)
		{
			this->table = new List<Pair<type> >[size];
		}

		/*
		 * Dekonstruktor zur Speicherfreigabe
		 */
		~Hashtable()
		{
			delete[] this->table;
		}

		/*
		 * Fügt ein Element in die Hashtabelle hinzu.
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
		 * Gibt ein Element anhand des Schlüssels zurück.
		 * Wirft eine KeyNotFoundException wenn der Schlüssel nicht enthalten ist.
		 */
		type get(String key)
		{
			return this->getPair(key)->value;
		}

		/*
		 * Entfernt einen Schlüssel aus der Hashtabelle
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
		 * Überprüft, ob ein Schlüssel in der Hahstabelle enthalten ist
		 */
		bool contains(String key)
		{
			try
			{
				Pair<type>* pair = this->getPair(key);
                pair->key = pair->key;
				return true;
			}
			catch(...)
			{
				return false;
			}
		}
}; 

#endif
