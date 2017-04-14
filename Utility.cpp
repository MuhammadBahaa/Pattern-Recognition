
// Utility.cpp
// Convert From Binary to Bipolar and from Bipolar to Binary
// and contain function to formate boolan in string [T,T,F,F]

// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 22-11-2008

#include "Utility.h"

int* Utility :: convert (bool* binary,int size){
	int* tmp = new int[size];

	for (int i=0 ; i<size; i++) {
		tmp[i] = convert(binary[i]) ;
	}

	return tmp ;
}

bool* Utility :: convert (int* bipolar,int size){
	bool* tmp = new bool[size];

	for (int i = 0 ; i < size ; i++)
		tmp[i] = convert(bipolar[i]);

	return tmp ;
}

int Utility :: convert (bool binary){
	return 2*binary - 1 ;
}

bool Utility :: convert (int bipolar){
	return (bipolar+1)/2 ;
}

string Utility ::print(bool* binary, int size){
	string str = "[" ;
	for (int i=0 ; i<size ; i++) {
		if (binary[i])
			str += "T" ;
		else
			str += "F" ;

		if ( i != size-1)
			str += "," ;
	}

	str += "]" ;

	return str ;
}
