
// Matrix.h
// Perform Matrix Operation on 2D Array 

// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 17-11-2008

#ifndef _MATRIX
#define _MATRIX

#include <stdexcept>
#include <iostream>
using std :: out_of_range ;
using std :: ostream ;

// forward decleration 
template <typename T> class Matrix ;

// prototype for friend funciton
template <typename T> ostream& operator <<       (ostream& out , const Matrix<T>& rhs);
template <typename T> const Matrix<T> operator + (const Matrix<T>& lhs , const Matrix<T>& rhs) ;
template <typename T> const Matrix<T> operator * (const Matrix<T>& lhs , const Matrix<T>& rhs) ;
template <typename T> const Matrix<T> operator * (const Matrix<T>& lhs , const int number ) ;
template <typename T> const Matrix<T> operator - (const Matrix<T>& lhs , const Matrix<T>& rhs) ;
template <typename T> const Matrix<T> operator / (const Matrix<T>& lhs , const int number ) ;

template <typename T>
class Matrix
{
	public :
		// constructor
		Matrix(int row, int col);	// 2-argument ctor
		Matrix(T** arr, int row, int col);	// 3-arg ctor
		
		// copy constructor + assignment operation 
		Matrix(const Matrix<T>& matrix) ;
		Matrix<T>& operator=(const Matrix<T>& matrix);
		
		// destructor
		~Matrix();
		
		void insert(int row,int col, T value) throw(out_of_range); // insert value at location
		
		T getValue(int row, int col) const;	// get value at location
		int getRows() const ;	// get number of rows
		int getCols() const ;	// get number of columns
		void toZero () const ;	// make all element 0 
		static T* toArray (const Matrix& m) ;
		
		const Matrix<T> getRowAt(int index)  ;
		const Matrix<T> getColAt(int index)  ;
		
		// overload () operator 
		T& operator() (int row, int col) throw(out_of_range);
		const T& operator() (int row, int col) const throw(out_of_range);
		
		// overload == equal operator
		const bool operator == (const Matrix<T>& rhs) const;
		
		// overload operation [] , == , = , + , * , / , - , << , >>
		friend const Matrix<T> operator +  <T> (const Matrix& lhs , const Matrix& rhs) ;
		friend const Matrix<T> operator *  <T> (const Matrix& lhs , const Matrix& rhs) ;
		friend const Matrix<T> operator *  <T> (const Matrix& lhs , const int number ) ;
		friend const Matrix<T> operator -  <T> (const Matrix& lhs , const Matrix& rhs) ;
		friend const Matrix<T> operator /  <T> (const Matrix& lhs , const int number ) ;
		friend ostream&     operator <<    <T> (ostream& out , const Matrix& rhs);
		
		// Matrix Operation
		static const Matrix<T> transpose (const Matrix<T>& lhs);
		static const Matrix<T> identity  (const int size) ;
		static const T vectorLength   (const Matrix<T>& lhs);
		static const T dotProduct     (const Matrix<T>& lhs , const Matrix<T>& rhs);
		static const bool isVector    (const Matrix<T>& m1 ) ;
		
		static Matrix<T> createRowMatrix (T* data, int size=4);
		static Matrix<T> createColMatrix (T* data, int size=4);
		
	protected :
		T** array ;
		int rows,cols ;
		
		// helper function
		void copyTo (const Matrix<T>& matrix);	// copy element from matrix to array
		bool inRange(int row, int col); // check is vlaue in valid range
		const bool inRange(int value, int upper) const ; // check is vlaue in valid range
	    const bool compatibleDimension (const Matrix<T>& m2) const ; // check for Matrix Multilpications
		static T max (T a, T b) ;
};

#include "Matrix.cpp"

#endif // _MATRIX
