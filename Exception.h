#ifndef __EXCEPTION_H_
#define __EXCEPTION_H__
#include <iostream>
namespace myExceptions {
	class Exception {
	public:
		virtual void Print() { std::cout << "Exception occurred \n";};
	};
	
	/* Cusome Exception classes */
	class OverflowException : public Exception {
	public:
		void Print() {std::cout << "Overflow exception \n"; }
	};
};
#endif
