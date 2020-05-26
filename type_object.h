#ifndef TYPE_OBJECT_GF_2020
#define TYPE_OBJECT_GF_2020

// Code:
//#define VT(_inst) ((VariadicTemplate){_inst})

typedef class Object {
	void* data;
	unsigned int size;

public:
	Object() {
		data = nullptr;
		size = 0;
	}

	template <class T> Object(T t_inst) {
		char * instanceData = (char*)&t_inst;
		size = sizeof(T);

		char * memory = new char[size];
		for(unsigned int i = 0; i < size; i++) {
			memory[i] = *instanceData;
			instanceData++;
		}

		data = (void*)memory;
	}

	~Object() {
		if(data) { 
			char * toDelete = (char*) data;
			delete[] toDelete;
		}
	}
	
	inline unsigned int Size() {
		return size;
	}

	template <class T> inline bool CompareSize() {
		return sizeof(T) == size;
	}

	bool Equals(const Object& obj) {
		char* this_data = (char*) data;
		char* obj_data = (char*) obj.data;

		if(obj.size != this->size) //we check if the amount of byte taken by each objects is the same.
			return false;

		for(unsigned int i = 0; i < size; i++) { // we iterate on each bytes to see if the two objects are the same.
			if(this_data[i] != obj_data[i])
				return false;
		}
		return true;
	}

	template<class T> inline Object operator=(T t_inst) {
		return Object(t_inst);
	}

	inline bool operator==(const Object& obj) {
		return Equals(obj);
	}

	template <class T> T To() {
		unsigned int T_size = sizeof(T);
		if(T_size == this->size)
			return *(T*)data;
		
		// creates a dummy instance
		char * T_data = new char[sizeof(T)]; 
		for(unsigned int i = 0; i < T_size; i++)
			T_data[i] = NULL;
		T inst = *(T*)(void*) T_data;
		delete[] T_data;
		return inst;
	}

	void Copy(const Object& obj) {
		char * memory = new char[obj.size];
		char * objMemory = (char*) obj.data;
		for(unsigned int i = 0; i < obj.size; i++) {
			memory[i] = *objMemory;
			objMemory++;
		}
		if(data)
			delete[] (char*) data;
		data = (void*) memory;
		size = obj.size;
	}
} var;

#endif
