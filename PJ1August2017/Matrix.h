#pragma once
#include <algorithm>
#include <tuple>
#include <exception>
template <typename T, unsigned N, unsigned M>
class Matrix
{
	static_assert(std::is_arithmetic<T>::value, "Type T is not an arithmetic type!");
protected:
	T** matrix;

	virtual void move(Matrix<T, N, M>&&) noexcept;
	virtual void copy(const Matrix<T, N, M>&) noexcept(false);
	virtual void destroy() noexcept;
	virtual void allocate() noexcept(false);
public:
	Matrix() noexcept(false); // TODO: throws exceptions, make it actually throw exceptions
	Matrix(const Matrix<T, N, M>&);
	Matrix(Matrix<T, N, M>&&) noexcept;
	virtual ~Matrix() noexcept;

	template<unsigned Nd, unsigned Md>
	Matrix<T, N, M>& operator=(const Matrix<T, Nd, Md>&) noexcept(false);

	template<unsigned Nd, unsigned Md>
	Matrix<T, N, M>& operator=(Matrix<T, Nd, Md>&&) noexcept;

	T& operator[](std::tuple<unsigned, unsigned>) noexcept(false);

	constexpr std::tuple<unsigned, unsigned> getter() const noexcept;

	template<unsigned Nd, unsigned Md>
	Matrix<T, N, M> operator+(const Matrix<T, Nd, Md>&) const noexcept(false);
};

template<typename T, unsigned N, unsigned M>
constexpr std::tuple<unsigned, unsigned> Matrix<T, N, M>::getter() const noexcept
{
	return std::make_tuple<unsigned, unsigned>(N, M);
}

template<typename T, unsigned N, unsigned M>
inline void Matrix<T, N, M>::move(Matrix<T, N, M>&& other) noexcept
{
	matrix = other.matrix;
	other.matrix = nullptr;
}

template<typename T, unsigned N, unsigned M>
inline void Matrix<T, N, M>::copy(const Matrix<T, N, M>& other) noexcept(false)
{
	allocate();
	int i = 0;
	std::for_each(matrix, matrix + N, [](T*& thePointer)
	{
		std::copy(other.matrix[i], other.matrix[i++] + N, thePointer);
	});
}

template<typename T, unsigned N, unsigned M>
inline void Matrix<T, N, M>::destroy() noexcept
{
	std::for_each(matrix, matrix + N, [](T*& thePointer)
	{
		if (thePointer != nullptr)
			delete[] thePointer;
	});
	delete[] matrix;
}

template<typename T, unsigned N, unsigned M>
void Matrix<T, N, M>::allocate() noexcept(false) try
{
	matrix = new T*[N];
	std::for_each(matrix, matrix + N, [](T*& thePointer)) { thePointer = new T[M]; });
}
catch (std::bad_alloc& ex)
{
	std::cerr << ex.what();
	destroy();
	throw(new std::exception("The object was not alocated!"));
}

template<typename T, unsigned N, unsigned M>
inline Matrix<T, N, M>::Matrix() noexcept(false)
{
	allocate();
}

template<typename T, unsigned N, unsigned M>
inline Matrix<T, N, M>::Matrix(const Matrix<T, N, M>& other)
{
	copy(other);
}

template<typename T, unsigned N, unsigned M>
inline Matrix<T, N, M>::Matrix(Matrix<T, N, M>&& other) noexcept
{
	move(std::move(other));
}

template<typename T, unsigned N, unsigned M>
inline Matrix<T, N, M>::~Matrix() noexcept
{
	destroy();
}

template<typename T, unsigned N, unsigned M>
template<unsigned Nd, unsigned Md>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator=(const Matrix<T, Nd, Md>& other) noexcept(false)
{
	static_assert((N == other.N && M == other.M), "The dimensions of matrices are not right!");
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

template<typename T, unsigned N, unsigned M>
template<unsigned Nd, unsigned Md>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator=(Matrix<T, Nd, Md>&& other) noexcept
{
	static_assert((N == other.N && M == other.M), "The dimensions of matrices are not right!");
	destroy();
	move(std::move(other));
	return *this;
}

template<typename T, unsigned N, unsigned M>
inline T & Matrix<T, N, M>::operator[](std::tuple<unsigned, unsigned> coordinates) noexcept(false)
{
	return matrix[std::get<0>(coordinates)][std::get<1>(coordinates)];
}

template<typename T, unsigned N, unsigned M>
template<unsigned Nd, unsigned Md>
inline Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix<T, Nd, Md>& other) const noexcept(false)
{
	static_assert((N == other.N && M == other.M), "The dimensions of matrices are not right!");
	Matrix<T, N, M> tmp;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			tmp.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
		}
	return tmp;
}