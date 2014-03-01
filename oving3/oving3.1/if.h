#ifndef   	IF_H_
# define   	IF_H_

#include<systemc.h>

//#define N 3		//think we can define the dim of the table here..

class processor_if : public sc_interface {

	public:
		virtual bool test(int) = 0;
		virtual bool free() = 0;		
};

#endif
