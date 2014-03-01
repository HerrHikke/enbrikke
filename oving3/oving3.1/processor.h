#ifndef   	P_H_
# define   	P_H_

#include "if.h"
#include<systemc.h>
#include<string>


#define LEFT 	0
#define UP 		1
#define RIGHT 	2
#define DOWN	3

class Processor : public sc_module, public processor_if{

	public:
		sc_port <processor_if > processor_up;
		sc_port <processor_if > processor_left;		

//for task 3
//		sc_port <processor_if > processor_right;
//		sc_port <processor_if > processor_down;		

		Processor(std::string name, Processor* left, Processor* up) : sc_module(name), name(name), 			busy(false), 
				mynumber (-1), numbersFound(0){
			//todo: initialize neighbours
			neighbours[UP] = up;
			neighbours[LEFT] = left;
		}; 
		void setNeighbour(int position, Processor* proc){
			neighbours[position] = proc;
		}
		void initialize(int max);
		std::string getName() {return name;};

		//interface
		bool test(int);	//returns true if the processor sees the int as not taken
		bool free();	//returns true if this processor is not beeing tested by another processor

	private:
		int mynumber;		//the private number to the individual processor
		bool busy;
		Processor** neighbours;
		int found[9];				//might be able to use found[N]; contains the numbers already found
		int numbersFound;
		std::string name;


};
#endif
