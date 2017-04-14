
// Matrix.cpp
// implementation of class

// Programmer : Wajdy Essam (romansy)
// Feedback : www.sudancs.com , sudangeek@hotmail.com
// date : 17-11-2008

//#include "Matrix.h"
#include <cmath>
#include <iomanip>

// 2-arg ctor
template <typename T>
Matrix<T> :: Matrix (int row, int col) : rows(row),cols(col) {
	array = new T*[row];
	for (int i=0 ; i<row ; i++)
		array[i] = new T[col];

	// initializing to zero
	toZero();
}

// 3-arg ctor
template <typename T>
Matrix<T> :: Matrix(T** arr,int row,int col) : rows(row),cols(col) {

	array = new T*[row];
	for (int i=0 ; i<row ; i++)
		array[i] = new T[col];

	for (int i=0 ; i<row ; i++) {
		for (int j=0 ; j<col ; j++) {
			array[i][j] = arr[i][j] ;
		}
	}
}

// copt ctor
template <typename T>
Matrix<T> :: Matrix (const Matrix<T>& matrix) {
	copyTo(matrix);
}

// dtor
template <typename T>
Matrix<T> :: ~Matrix () {
	for (int i=0 ; i<rows ; i++)
		delete [] array[i] ;

	delete [] array ;
}

// assignment operator
template <typename T>
Matrix<T>& Matrix<T> :: operator= (const Matrix<T>& matrix ) {
	if ( this == &matrix)
		return (*this);

	// free array
	for (int i=0 ; i<rows ; i++)
		delete [] array[i];
	delete [] array ;

	copyTo(matrix);

	return (*this);
}

// overload () operator
template <typename T>
T& Matrix<T> :: operator () (int row, int col)  throw(out_of_range){
	if ( ! inRange(row,col) )
		throw out_of_range("Invalid row or col number");

	return array[row][col];
}

template <typename T>
const T& Matrix<T> :: operator () (int row, int col) const throw(out_of_range) {
	if ( ! inRange(row,col) )
			throw out_of_range("Invalid row or col number");

	return array[row][col];
}

// helper function
template <typename T>
void Matrix<T> :: copyTo (const Matrix<T>& matrix ) {
	// get rows and columns  number
	rows = matrix.getRows();
	cols = matrix.getCols();

	// make new space for array
	array = new T*[rows];
	for (int i=0 ; i<rows;  i++)
		array[i] = new T[cols] ;

	// copy value
	for (int i=0 ; i<rows ; i++) {
		for (int j=0 ; j<cols ; j++)
			array[i][j] = matrix.getValue(i,j) ;
	}
}

// helper function
template <typename T>
bool Matrix<T> :: inRange (int row , int col ) {
	if ( ( row < 0 || row > rows) || ( col < 0 || col > cols) )
		return false ;

	return true ;
}

template <typename T>
const bool Matrix<T> :: inRange (int row , int col ) const {
	if ( ( row < 0 || row > rows) || ( col < 0 || col > cols) )
		return false ;

	return true ;
}

// insert value
template <typename T>
void Matrix<T> ::  insert(int row,int col, T value) throw(out_of_range) {
	if ( ! inRange(row,col) )
		throw out_of_range("Invalid row or col number");
	array[row][col] = value ;
}

template <typename T>
T Matrix<T> :: getValue (int row, int col) const {
	return array[row][col];
}

template <typename T>
void Matrix<T> :: toZero () const {
	for (int i=0 ; i<rows ; i++) {
		for (int j=0 ; j<cols ; j++) {
			array[i][j] = 0 ;
		}
	}
}

template <typename T>
int Matrix<T> :: getRows() const {
	return rows ;
}

template <typename T>
int Matrix<T> :: getCols() const {
	return cols ;
}

template <typename T>
const bool Matrix<T> :: compatibleDimension (const Matrix<T>& m2 ) const {
	if ( cols == m2.rows )
		return true ;

	return false ;
}

template <typename T>
const bool Matrix<T> :: operator == (const Matrix<T>& m1 ) const {
	if ( rows != m1.rows)
		return false ;

	if ( cols != m1.cols)
		return false ;

	return true ;
}

template <typename T>
const Matrix<T> operator + (const Matrix<T>& m1 , const Matrix<T>& m2) {
	if ( m1 == m2 ) {
		Matrix<T> m3(m1.getRows(),m1.getCols());

		for (int i=0 ; i<m3.rows ; i++)
			for (int j=0 ; j<m3.cols ; j++)
				m3(i,j) = m1(i,j) + m2(i,j) ;

		return m3 ;
	}
	else
		throw out_of_range("two matrix is not equals !");
}

template <typename T>
const Matrix<T> operator - (const Matrix<T>& m1 , const Matrix<T>& m2) {
	if ( m1 == m2 ) {
		Matrix<T> m3(m1.getRows(),m1.getCols());

		for (int i=0 ; i<m3.rows ; i++)
			for (int j=0 ; j<m3.cols ; j++)
				m3(i,j) = m1(i,j) - m2(i,j) ;
		return m3 ;
	}
	else
		throw out_of_range("two matrix is not equals !");
}

template <typename T>
const Matrix<T> operator * (const Matrix<T>& m1 , const Matrix<T>& m2) {
	if ( m1.compatibleDimension(m2)) {
		Matrix<T> m3(m1.getRows(),m2.getCols());

		for (int i=0 ; i<m1.rows ; i++) {
			for (int j=0 ; j<m2.cols ; j++) {
				T sum = 0 ;

				for (int k=0 ; k<m2.rows ; k++) {
					sum += m1(i,k) * m2(k,j);
				}
				m3(i,j) = sum ;
			}
		}
		return m3 ;
	}
	else
		throw out_of_range("two matrix isn't compatible dimension !");
}

template <typename T>
const Matrix<T> operator / (const Matrix<T>& m1 , const int number ) {
	Matrix<T> tmp(m1.getRows(),m1.getCols());

	if ( number != 0 ) {
		for (int i=0 ; i<tmp.rows ; i++)
			for (int j=0 ; j<tmp.cols ; j++)
				tmp(i,j) = m1(i,j) / number ;
	}
	else
		throw out_of_range("illegal operation , cannt divide by zero !");

	return tmp ;
}

template <typename T>
const Matrix<T> operator * (const Matrix<T>& m1 , const int number ) {
	Matrix<T> tmp(m1.getRows(),m1.getCols());

	for (int i=0 ; i<tmp.rows ; i++)
		for (int j=0 ; j<tmp.cols ; j++)
			tmp(i,j) = m1(i,j) * number ;

	return tmp ;
}

template <typename T>
ostream&  operator << (ostream& out , const Matrix<T>& mt ) {
	for (int i=0 ; i<mt.rows ; i++) {
		for (int j=0 ; j<mt.cols ; j++)
			out << std::setw(4) << std::setfill(' ') << mt.array[i][j]  ;
		out << "\n" ;
	}
	return out ;
}

template <typename T>
const Matrix<T> Matrix<T> :: identity  (const int size) {
	Matrix<T> tmp(size,size);

	for (int i=0 ; i<size ; i++)
		tmp(i,i)= 1 ;

	return tmp ;
}

template <typename T>
const Matrix<T> Matrix<T> :: transpose (const Matrix<T>& lhs) {
	Matrix<T> tmp(lhs.getCols(),lhs.getRows());

	for (int i=0 ; i<lhs.rows ; i++)
		for (int j=0 ; j<lhs.cols ; j++)
			tmp(j,i) = lhs(i,j);

	return tmp ;
}

template <typename T>
const T Matrix<T> :: dotProduct   (const Matrix<T>& lhs , const Matrix<T>& rhs) {
	if ( (isVector(lhs)) && (isVector(rhs))) {
		T* a = toArray(lhs);
		T* b = toArray(rhs);

		T sum = 0 ;
		int length =  max(max(rhs.rows,lhs.cols) , max(rhs.cols,lhs.rows));

		for (int i=0 ; i<length ; i++)
			sum += a[i]*b[i] ;

		return sum ;
	}
	else
		throw out_of_range("one of two matrix is not vector !");
}

template <typename T>
const T Matrix<T> :: vectorLength (const Matrix<T>& rhs) {
	if ( isVector(rhs) ) {
		T* a = toArray(rhs);
		int length =  max(rhs.rows,rhs.cols);
		T sum = 0 ;

		for (int i=0 ; i<length ; i++)
			sum += (a[i]*a[i]) ;

		return (T)sqrt(sum) ;
	}
	else
		throw out_of_range("matrix is not vector !");
}

template <typename T>
T Matrix<T> :: max (T a, T b) {
	if ( a >= b )
		return a ;
	else
		return b ;
}

template <typename T>
T* Matrix<T> :: toArray (const Matrix<T>& m) {
	int length = m.rows * m.cols ;

	T* vector = new int[length] ;
	int k=0 ;
	for (int i=0 ; i<m.rows ; i++)
		for (int j=0 ; j<m.cols ; j++,k++)
			vector[k] = m(i,j) ;

	return vector ;
}

template <typename T>
const bool Matrix<T> :: isVector (const Matrix<T>& m1 )  {
	if ( (  m1.cols == 1 ) || ( m1.rows ==1  ) )
		return true ;
	else
		return false ;
}

template <typename T>
const Matrix<T> Matrix<T> :: getRowAt (int row)   {
	if ( row >= getRows() || row < 0 )
		throw out_of_range("Invalid row number");

	Matrix<T> matrix(1,getCols());

	for (int i=0 ; i<getCols() ; i++)
		matrix(0,i) = array[row][i];

	return matrix ;
}

template <typename T>
const Matrix<T> Matrix<T> :: getColAt (int col)   {
	if ( col >= getCols() || col < 0 )
		throw out_of_range("Invalid col number");

	Matrix<T> matrix(getRows(),1);

	for (int i=0 ; i<getRows() ; i++)
		matrix(i,0) = array[i][col];

	return matrix ;
}

template <typename T>
Matrix<T> Matrix<T> :: createRowMatrix (T* data, int size) {
	Matrix<T> m(1,size);

	for (int i=0 ; i<size ; i++)
		m(0,i) = data[i] ;

	return m ;
}

template <typename T>
Matrix<T> Matrix<T> :: createColMatrix (T* data, int size) {
	Matrix<T> m(size,1);

	for (int i=0 ; i<size ; i++)
		m(i,0) = data[i] ;

	return m ;
}
