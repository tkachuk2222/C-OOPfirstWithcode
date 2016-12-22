#pragma once
template<typename T>
class Matrix
{
public:
	Matrix();
	Matrix(int, int);
	Matrix(int**, int, int);
	Matrix(const Matrix&ob);
	Matrix(Matrix&&ob);
	~Matrix();

	template<typename D>
	Matrix<T>operator=(const Matrix<D>&ob);

	template<typename D>
	Matrix<T>operator=(Matrix<D>&&ob);

	template<typename D>
	Matrix<T>operator+(const Matrix<D>&ob)const;

	void setMem();
	template<typename D>
	friend ostream &operator << (ostream&os, const Matrix<D>&ob);

	template<typename D>
	friend istream &operator >> (istream&os, Matrix<D>&ob);
private:
	T **matrix_;
	int cols_;
	int rows_;
};
template<typename T>
Matrix<T>::Matrix() {
	matrix_ = nullptr;
	cols_ = 0;
	rows_ = 0;
}
template<typename T>
inline Matrix<T>::Matrix(int **arr, int row, int col)
{
	rows_ = row;
	cols_ = col;
	setMem();
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < cols_; j++)
			matrix_[i][j] = arr[i][j];
}
template<typename T>
inline Matrix<T>::Matrix(const Matrix & ob)
{
	if (cols_ != ob.cols_ || rows_ != ob.rows_) {
		cols_ = ob.cols_;
		rows_ = ob.rows_;
		setMem();
		for (int i = 0; i < rows_; i++)
			for (int j = 0; j < cols_; j++)
				matrix_[i][j] = ob.matrix_[i][j];
	}
	else {
		for (int i = 0; i < rows_; i++)
			for (int j = 0; j < cols_; j++)
				matrix_[i][j] = ob.matrix_[i][j];
	}
}
template<typename T>
inline Matrix<T>::Matrix(Matrix && ob)
{
	cout << "\t\t~~Constructor MOVE~~" << endl;
	cols_ = ob.cols_;
	rows_ = ob.rows_;
	matrix_ = ob.matrix_;
	ob.cols_ = 0;
	ob.rows_ = 0;
	ob.matrix_ = nullptr;
}
template<typename T>
void Matrix<T>::setMem() {
	matrix_ = new int*[rows_];
	for (int i = 0; i < rows_; i++)
		matrix_[i] = new int[cols_];
}
template<typename T>
Matrix<T>::Matrix(int row, int col) {
	cols_ = col;
	rows_ = row;
	setMem();
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < cols_; j++)
			matrix_[i][j] = 0;
}
template<typename T>
Matrix<T>::~Matrix() {
	cout << "\t\t~~destructor matrix~~" << endl;
	if (matrix_) {
		for (int i = 0; i < rows_; i++)
		{
			delete[]matrix_[i];
		}
		delete[]matrix_;
		cols_ = 0;
		rows_ = 0;
	}
}

template<typename T>
template<typename D>
inline Matrix<T> Matrix<T>::operator=(const Matrix<D>& ob)
{
	cols_ = ob.cols_;
	rows_ = ob.rows_;
	setMem();
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < cols_; j++)
			matrix_[i][j] = ob.matrix_[i][j];
	return *this;
}

template<typename T>
template<typename D>
inline Matrix<T> Matrix<T>::operator=(Matrix<D>&& ob)
{
	if (matrix_)
		delete matrix_;
	cols_ = ob.cols_;
	rows_ = ob.rows_;
	setMem();
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < cols_; j++)
			matrix_[i][j] = ob.matrix_[i][j];
	ob.matrix_ = nullptr;
	return *this;
}

template<typename T>
template<typename D>
inline Matrix<T> Matrix<T>::operator+(const Matrix<D>& ob) const
{
	Matrix tmp;
	if (cols_ == ob.cols_&&rows_ == ob.rows_) {
		tmp.cols_ = cols_;
		tmp.rows_ = rows_;
	}
	else {
		if (cols_ > ob.cols_)
			tmp.cols_ = ob.cols_;
		else
			tmp.cols_ = cols_;
		if (rows_ > ob.rows_)
			tmp.rows_ = ob.rows_;
		else
			tmp.rows_ = rows_;
	}
	tmp.matrix_ = new int*[tmp.rows_];
	for (int i = 0; i < tmp.rows_; i++)
		tmp.matrix_[i] = new int[tmp.cols_];
	for (int i = 0; i < tmp.rows_; i++)
		for (int j = 0; j < tmp.cols_; j++)
			tmp.matrix_[i][j] = matrix_[i][j] + ob.matrix_[i][j];
	return tmp;
}

template<typename D>
inline ostream & operator<<(ostream & os, const Matrix<D>& ob)
{
	for (int i = 0; i < ob.rows_; i++){
		for (int j = 0; j < ob.cols_; j++) 
			os << ob.matrix_[i][j];
		os << endl;
	}

	return os;
}

template<typename D>
inline istream & operator >> (istream & os, Matrix<D>& ob)
{
	for (int i = 0; i < ob.rows_; i++)
		for (int j = 0; j < ob.cols_; j++) {
			is >> ob.matrix_[i][j];
		}
	return is;
}
