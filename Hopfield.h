
// Hopfield.h
// Reprenst The Hopfield Neural Networks
// cintain function to trainning and prenset input to network

// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 22-11-2008

#ifndef _Hopfield
#define _Hopfield

#include "Matrix.h"
#include "Utility.h"

class Hopfield {
	private :
		Matrix<int> matrix ;
		int size ;
		
	public :
		Hopfield (int size) ;
		Hopfield () ;
		
		const Matrix<int> getMatrix () const ;
		bool* present (bool input[],int size=4);
		void train (bool pattern[],int size=4) ;
		int getSize() const ;
};

#endif  //_Hopfield
