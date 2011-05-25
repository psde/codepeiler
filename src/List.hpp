#ifndef LIST_HPP
#define LIST_HPP

template <class type>
class List {
	type* values;
	int   size, internalSize;

public:
	List() {
		this->size = 0;
		this->internalSize = 10;
		this->values = new type[ internalSize ];
	}

	~List() {
		delete[] this->values;
	}

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

	void append(type value)
	{
		this->resize(size+1);
		this->values[size-1] = value;
	}

	/*void setValue(int index, type value) {
		this->values[ index ] = value;
	}*/

	type& operator[](int index) {
		return this->values[index];
	}

	int getSize() {
		return this->size;
	}

	int getFreeSize() {
		return this->internalSize - this->size;
	}
	
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
