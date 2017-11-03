#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <mutex>

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
	auto pop() -> std::shared_ptr<T>/*strong*/;
	void print() const /*strong*/;
	bool empty()const noexcept;
private:
	void swap(stack<T>&)noexcept;
	T * array_;
	mutable std::mutex mutex_;
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
	std::lock_guard<std::mutex> lock(other.mutex_);
	T new_array = new T [other.array_size_];
	array_size_ = other.array_size_;
	count_ = other.count_;	
	array_ = new_array;
	try
	{
		std::copy(other.array_, other.array_ + count_, array_);	
	}
	catch( ... )
	{
		std::cerr << "ERROR!" << std::endl;
		delete[] array_;
	}				
}
template <typename T>
stack<T>& stack<T>::operator=(stack<T> const & other)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (&other != this)
		stack(other).swap(*this);
	return *this;
}
template <typename T>
size_t stack<T>::count()const noexcept
{
	std::lock_guard<std::mutex> lock(mutex_);
	return count_;
}
template <typename T>
void stack<T>::push(T const & value)
{
	std::lock_guard<std::mutex> lock(mutex_);
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
		catch(...) 
		{	
			std::cerr << "ERROR!";
		}
	}
	array_[count_] = value;
	count_++;
}
template <typename T>
void stack<T>::pop()
{
	std::lock_guard<std::mutex> lock(mutex_);
	auto top = std::make_shared<T>(array_[count_ - 1]);
	if (empty())
		throw "Stack is empty";
	--count_;
	return top;
}
template <typename T>
void stack<T>::print() const 
{
	mutex_.lock();
	if(!empty())
	{
	        for (unsigned int i = 0; i < count_; ++i)
		        std::cout << array_[i] << " ";
	        std::cout << std::endl;
	}
	mutex_.unlock();
}
template <typename T>
void stack<T>::swap(stack<T>& other)noexcept
{
	std::swap(array_, other.array_);
	std::swap(array_size_, other.array_size_);
	std::swap(count_, other.count_);
	mutex_.unlock();
	other.mutex_.unlock();
}
template <typename T>
bool stack<T>::empty()const noexcept
{
	std::lock_guard<std::mutex> lock(mutex_);
	return (count_ == 0);
}
