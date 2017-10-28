#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class stack
{
public:
	stack() noexcept;
	~stack() noexcept;
	stack(stack<T> const&)/*strong*/;
	stack& operator=(stack<T> const&)/*strong*/;
	size_t count()const noexcept;
	void push(T const&)/*strong*/;
	void pop()/*strong*/;
	T top()const /*strong*/;
	void print() const /*strong*/;
	void swap(stack<T>&)noexcept;
	bool empty()const noexcept;
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};

template <typename T> 
stack<T>::stack() noexcept : array_{ nullptr }, array_size_{ 0 }, count_{ 0 } {}
template <typename T>
stack<T>::~stack()noexcept
{
	delete[] array_;
}
template <typename T>
stack<T>::stack(stack<T> const& other)
{
	array_size_ = other.array_size_;
	count_ = other.count_;	
	try
	{
	        array_ = new T[array_size_];
	        std::copy(other.array_, other.array_ + count_, array_);
	}
	catch(std::bad_alloc)
	{
		std::cerr << "bad_alloc caught" << std::endl;
	}
}
template <typename T>
stack<T>& stack<T>::operator=(stack<T> const & other)
{
	if (&other != this)
		stack(other).swap(*this);
	return *this;
}
template <typename T>
size_t stack<T>::count()const noexcept
{
	return count_;
}
template <typename T>
void stack<T>::push(T const & value)
{
	if (empty())
	{
		array_size_ = 1;
		array_ = new T[array_size_]();
	}
	else if (array_size_ == count_)
	{
		try
		{
			
		array_size_ *= 2;
		T * new_array = new T[array_size_]();
		std::copy(array_, array_ + count_, new_array);
		delete[] array_;
		array_ = new_array;
		}
		catch(std::bad_alloc)
	        {
		        std::cerr << "bad_alloc caught" << std::endl;
	        }
	}
	array_[count_++] = value;
}
template <typename T>
void stack<T>::pop()
{
	if (empty())
		throw "Stack is empty";
	--count_;
}
template <typename T>
T stack<T>::top()const 
{
	if (empty())
		throw "Stack is empty";
	else return array_[count_ - 1];
}
template <typename T>
void stack<T>::print() const 
{
	if(!empty())
	{
	        for (unsigned int i = 0; i < count_; ++i)
		        std::cout << array_[i] << " ";
	        std::cout << std::endl;
	}
}
template <typename T>
void stack<T>::swap(stack<T>& other)noexcept
{
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
}
template <typename T>
bool stack<T>::empty()const noexcept
{
	return (count_ == 0);
}
