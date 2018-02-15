#pragma once
#include "Matrix.h"
//2.1 jeste
//2.2 nije komutativna, nisu tipovi isti, iz definicije mnozenja matrica (matematika 1)
template <typename T, unsigned N>
class Vector : public Matrix<T, N, (unsigned)1>
{
public:
	Vector() noexcept(false);
	Vector(const Vector<T, N>&);
	Vector(Vector<T, N>&&) noexcept;

	//converting constructors

	template<unsigned Nd, unsigned Md>
	Vector(const Matrix<T, Nd, Md>&);
	template<unsigned Nd, unsigned Md>
	Vector(Matrix<T, Nd, Md>&&) noexcept;

	//assignment operators

	template<unsigned Nd>
	Vector<T, N>& operator=(const Vector<T, Nd>&) noexcept(false);
	template<unsigned Nd>
	Vector<T, N>& operator=(Vector<T, Nd>&&) noexcept;

	virtual ~Vector();

	//multiplication operators
	//I hope it's right, I was tired while doing this, if you encounter any problems, contact me
	//bajramovic.damir@hotmail.com or damir95b@gmail.com 
	template<unsigned Nd, unsigned Md>
	Matrix<T, N, Md>& operator*(const Matrix<T, Nd, Md>&) noexcept(false);

	template<typename T, unsigned N>
	template<unsigned Nd, unsigned Md>
	friend Vector<T, N>& operator*(const Matrix<T, Nd, Md>&, const Vector<T, N>&) noexcept(false)
};

//implicit cast operator, to enable this kind of things in your code:
/*
{
Vector<int, 3> v;
Matrix<int, 3, 1> m;
v = m;
}
*/
//google keyword "explicit" for c++

template<typename T, unsigned N>
inline Vector<T, N>::Vector() : Matrix<T, N, 1>() noexcept(false) {}

template<typename T, unsigned N>
inline Vector<T, N>::Vector(const Vector<T, N> & other) noexcept(false)
{
	copy(other);
}

template<typename T, unsigned N>
inline Vector<T, N>::Vector(Vector<T, N>&& other) noexcept
{
	move(std::move(other));
}

template<typename T, unsigned N>
template<unsigned Nd, unsigned Md>
inline Vector<T, N>::Vector(const Matrix<T, Nd, Md>& other) noexcept(false)
{
	static_assert((N == other.N && M == other.M), "The dimensions of matrices are not right!");
	copy(other);
}

template<typename T, unsigned N>
template<unsigned Nd, unsigned Md>
inline Vector<T, N>::Vector(Matrix<T, Nd, Md>&& other) noexcept
{
	static_assert((N == other.N && M == other.M), "The dimensions of matrices are not right!");
	move(std::move(other));
}

template<typename T, unsigned N>
template<unsigned Nd>
inline Vector<T, N>& Vector<T, N>::operator=(const Vector<T, Nd>& other) noexcept(false)
{
	static_assert((N == other.N), "The dimensions of vectors are not right!");
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}
template<typename T, unsigned N>
template<unsigned Nd>
inline Vector<T, N>& Vector<T, N>::operator=(Vector<T, Nd>&& other) noexcept
{
	static_assert((N == other.N), "The dimensions of vectors are not right!");
	if (this != &other)
	{
		destroy();
		move(other);
	}
	return *this;
}

template<typename T, unsigned N>
template<unsigned Nd, unsigned Md>
inline Matrix<T, N, Md>& Vector<T, N>::operator*(const Matrix<T, Nd, Md>& other) noexcept(false)
{
	static_assert((M == other.N), "The dimensions of operands are not right!");
	Matrix<T, N, Nd> result; //this could be protected, to avoid code duplication, but I'm lazy RN
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k; k < Md; ++k)
			{
				result[i][j] += this->matrix[i][k] * other[k][j];
			}
	return result;
}

template<typename T, unsigned N>
template<unsigned Nd, unsigned Md>
Vector<T, N>& operator*(const Matrix<T, Nd, Md>& matrix, const Vector<T, N>& vector) noexcept(false)
{
	static_assert((Md == other.N), "The dimensions of operands are not right!");
	Vector<T, Nd> result;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k; k < Md; ++k)
			{
				result[i][j] += this->matrix[i][k] * other[k][j];
			}
	return result;
}