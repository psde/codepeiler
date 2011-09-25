#ifndef _VECTOR_INCLUDED_
#define _VECTOR_INCLUDED_

/*
 * Vektor beliebiger L�nge mit beliebigem Inhalt.
 */
template <class type>
class Vector {
	type* values;
	int   size, internalSize;

    /* Resizes the vector */
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
            
            if(this->values != NULL)
    			delete[] this->values;

			this->values = temp;
			this->internalSize = newInternalSize;
		}
		this->size = newSize;
	}

	/* Gets the free size */
	int getFreeSize() {
		return this->internalSize - this->size;
	}

public:
    Vector()
    {
        this->size = 0;
        this->internalSize = 0;
        this->values = NULL;
    }

	/* Sets size */
	Vector(int size) 
    {
		this->size = size;
		this->internalSize = size * 2;
		this->values = new type[ internalSize ];
	}

	/* Deletes all values */
	~Vector() 
    {
		delete[] this->values;
	}

	/* Appends an element */
	void append(type value)
	{
		this->resize(size+1);
		this->values[size-1] = value;
	}

	/* Set new value */
	void setValue(int index, type value) {
		this->values[ index ] = value;
	}

	/* Get value from index */
	type getValue(int index) {
		return this->values[ index ];
	}

    /* Get value from index */
    char& operator[](int index)
    {
        return this->chars[index];
    }

	/* Get size */
	int getSize() 
    {
		return this->size;
	}
};

#endif // _VECTOR_INCLUDED_
