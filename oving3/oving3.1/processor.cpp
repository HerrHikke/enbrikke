/*
// Constructor
Processor::Processor (sc_module_name name, int _id) : sc_module (name), proc_placement(_id){
	SC_HAS_PROCESS(Proc);
	SC_THREAD(initialize);			//might want a run function here?
	proc_value=-100;				//no value found yet
	busy=false;						//
}*/

#include"processor.h"

bool Processor::test(int n) {	//returns true if the test number is not used already
	busy = true;	
	
	bool result = true;

	//if (mynumber < 0) result =  false;	//test if my own number
	
	for(int i = 0; i < numbersFound && result; i++) 	//test if neighbours number
		if (n = found[i]) result = false;


	for (int i = LEFT; i <= UP && result; i++){		//test if neighbour contains number
		if(neighbours[i] != NULL && !neighbours[i]->test(n)) {
		 	result = false;
			found[numbersFound++] = n;
		}
	}
	busy = false;
	
	return result;		
}

bool Processor::free() {
	
	bool result = !(busy || mynumber < 0);	

	return result;
}

void Processor::initialize(int max){
	
	int num;
	bool ok = true;
	
	do{
		num = rand()%max;
		for (int i = LEFT; i <= UP; i++){
			if (neighbours[i] != NULL ){
				if( !neighbours[i]->free() ) 
					break; 
				ok = neighbours[i]->test(num);
			}
		}
	} while (!ok);
	found[numbersFound++] = num;
	mynumber = num;

}
