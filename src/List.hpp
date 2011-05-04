#ifndef LIST_HPP
#define LIST_HPP

template <class type>
class list {
	type* values;
	int   size, internalSize;

public:
	/*
	 * Konstruktor, der die Liste mit Standardwerten initialisiert.
	 */
	list() {
		this->size = 0;
		this->internalSize = 10;
		this->values = new type[ internalSize ];
	}

	/*
	 * Destruktor: Wichtig zum Löschen der eigenen Daten
	 */
	~list() {
		delete[] this->values;
	}

	/*
	 * Ändert die größe der Liste
	 */
	void resize(int newSize)
	{
		if(newSize > this->internalSize)
		{
			int newInternalSize = newSize * 2;
			type* temp = new type[ newInternalSize ];

			int max = newInternalSize;
			if(newInternalSize > this->internalSize) max = this->internalSize;

			for(int i = 0; i < max; i++)
			{
				temp[i] = this->values[i];
			}

			delete[] this->values;
			this->values = temp;
			this->internalSize = newInternalSize;
		}
		this->size = newSize;
	}

	/*
	 * Hängt ein neues Element an die Liste
	 */
	void append(type value)
	{
		this->resize(size+1);
		this->values[size-1] = value;
	}

	/*
	 * Neuen Wert in die Liste eintragen.
	 */
	/*void setValue(int index, type value) {
		this->values[ index ] = value;
	}*/

	/*
	 * Wert aus der Liste auslesen.
	 */
	type& operator[](int index) {
		return this->values[index];
	}

	/**
	 * Größe der Liste ermitteln.
	 */
	int getSize() {
		return this->size;
	}

	/*
	 * Gibt die Anzahl der freien Plätze der Liste zurück
	 */
	int getFreeSize() {
		return this->internalSize - this->size;
	}
	
	/*
	 * Löscht ein Element aus der Liste, rückt nachfolgende Elemente auf
	 */
	void erase(int index) {
		if(this->size <= 1)
		{
			this->size = 0;
			return;
		}

		for(int i=index; i < this->size-1; i++)
		{
			this->values[i] = this->values[i+1];
		}
		this->size -= 1;
	}
};

#endif