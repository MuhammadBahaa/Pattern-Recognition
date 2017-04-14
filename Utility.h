
// Utility.h
// Convert From Binary to Bipolar and from Bipolar to Binary
// and contain function to formate boolan in string [T,T,F,F]

// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 22-11-2008

#ifndef _Utility
#define _Utility

#include <iostream>
using std:: string ;

class Utility 
{
	public :
		static int*  convert (bool* binary,int size=4) ;  // from binary to bipolar 
		static bool* convert (int* bipolar,int size=4) ;  // from bipolar to binary
		
		static int   convert (bool binary) ;    // from binary to bipolar
		static bool  convert (int bipolar) ;    // from bipolar to binary
		
		static string print(bool* binary,int size=4) ;  // format string output
};

#endif  //_Utility
