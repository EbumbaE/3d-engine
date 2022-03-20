class counter {

public:

	counter() : count(1) {}

	inline int get_c(){ 
	
		return count; 
	
	}

	inline void add_c(){
	
		count++; 
	
	}
	
	inline bool remove_c(){
	
		count--; 
		return count == 0; 
	
	}

private:

	int count;

};
