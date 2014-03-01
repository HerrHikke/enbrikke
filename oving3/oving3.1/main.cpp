#include<stdio.h>
#include<ctime>
#include<string>
#include<iostream>

#include"processor.h"
#include "if.h"

class Top : public sc_module {
	int length;
	int width ;
	Processor*** procs;

	int max;//= length*width -1;
	/*							//bad thing since we should be able to expand to n*n matrix...
	Processor* topLeft = new Processor("tl", NULL, NULL);
	Processor* topMid = new Processor("tm", topLeft, NULL);
	Processor* topRight = new Processor("tr", topMid, NULL);
	Processor* midLeft = new Processor("ml", NULL, topLeft);
	Processor* midMid = new Processor("mm", midLeft, topMid);
	Processor* midright = new Processor("mr", midMid, topRight);
	Processor* botLeft = new Processor("bl", NULL, midLeft);
	Processor* botMid = new Processor("bm", botLeft, midMid);
	Processor* botright = new Processor("br", borMid, midRight);
	*/
	public:
		void start(){
			srand(time(0));
			for (int i = 0; i < length; i++){
				for (int col = 0; col < width; col++){
					std::cout << "TOP: initializing processor " << procs[i][col]->getName() << endl;
					procs[i][col]->initialize(max);
				}
			}
		}

		Top (std::string name = "Top", int length = 3, int width = 3) : sc_module(name), width(width), 					length(length), max(length*width-1) {

			SC_HAS_PROCESS(Top);
			SC_THREAD(start);

			procs = new Processor**[length];
			for (int row = 0; row < length; row++){
				procs[row] = new Processor* [width];
				for (int col = 0; col < width; col++){
					//make some magic
					char* name;
					sprintf(name, "%i-%i", row, col);
					procs[row][col] = new Processor(name, NULL, NULL);
				}
			}
			for (int row = 0; row < length; row++){
				for (int col = 0; col < width; col++){
					//make some magic
					procs[row][col]->setNeighbour(UP, row == 0 ? NULL : procs[row-1][col]);
					procs[row][col]->setNeighbour(LEFT, col == 0 ? NULL : procs[row][col-1]);
				}
			}
		}//Top()			
};

int sc_main (int argc , char *argv[]){
	std::cout << "start!\n";						//why use std::???? not needed...
	cout<<"start2-----\n";
	Top top;				//	Top Top_inst("Top");		//this is how we have done it before
	sc_start ();
	std::cout << "stopp!\n";
	//top.start();
	return 0;		//think we need this at the end as previous
}

