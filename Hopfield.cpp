
// Hopfield.cpp
// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 22-11-2008

#include "Hopfield.h"

Hopfield :: Hopfield (int s): size(s),matrix(s,s) {
}

Hopfield :: Hopfield (): size(4),matrix(4,4) {
}

const Matrix<int> Hopfield :: getMatrix () const {
	return matrix ;
}

bool* Hopfield :: present (bool input[],int sz) {
	if ( size != sz )
		throw("this input is large than Matrix Size");
	
	bool* output = new bool[size];
	
	Matrix<int> in = Matrix<int> :: createRowMatrix( Utility :: convert(input,size) , size);
	
	for (int i=0 ; i<size ; i++) {
		Matrix<int> tmp = matrix.getColAt(i);
		tmp = Matrix<int>::transpose(tmp);
		int result = Matrix<int>:: dotProduct(in,tmp);
		
		if ( result > 0 )
			output[i] = true ;
		else
			output[i] = false ;
	}
	
	return output ;
}

void Hopfield :: train (bool pattern[],int sz) {
	if ( size != sz )
		throw("this input is large than Matrix Size");
		
	Matrix<int> in = Matrix<int> :: createRowMatrix( Utility :: convert(pattern,size),size);
	Matrix<int> transpose = Matrix<int> :: transpose(in);
	Matrix<int> product = transpose * in ;
	Matrix<int> identity = Matrix<int> :: identity(product.getRows());
	Matrix<int> result = product - identity ;
	
	matrix = matrix + result ;
}

int Hopfield :: getSize () const {
	return size ;
}
