#pragma once
#include "initializer_list"
#include "iostream"

#define DEFAULT_ARRAY_SIZE 2  // NOLINT(modernize-macro-to-enum)

enum array_status
{
	uninitialized,
	initialized,
	null
};

enum search_type
{
	linear_search,
	binary_search,
	
};

enum search_mode
{
	transposition,
	move_to_head,
	none
};

struct debug_info
{
	int len;
	int size;
};

template <typename Type>
class slice
{
private:
	//properties
	Type* m_arr_;
	int m_len_;
	int m_size_;

	//helper properties
	array_status m_status_ = array_status::null;

	//helper methods
	bool is_index_valid(int index) const;
	int resize(int size);
	void copy(Type* to);
	void swap(Type& x, Type& y);

public:
	//constructor
	slice(int size);
	slice(std::initializer_list<Type> args);
	slice(slice<Type>& s);
	static int ceil(const double x);

	//PUBLIC helper
	debug_info get_debug_info() const;

	//public methods
	void append(Type x);
	void display();
	void print();
	void insert(int index,Type x);
	void remove(int index);
	
	/**
	 * \brief search the element in slice, and returns index if found else -1
	 * \param x element to search
	 * \param s_type use binary search if slice is sorted
	 * \param s_mode only works with linear search, transposition is recommended search mode, change it to move_to_head if a elements is repeatedly needed, if you don't want to change the position of elements in slice switch to search_mode::none
	 * \return returns index if element found , -1 if not found and -2 if something went wrong
	 */
	int search(const Type x, const search_type s_type = search_type::linear_search, const search_mode s_mode = search_mode::transposition );


	/**
	 *copy constructor
	 *
	 *
	 *
	 *get(index)
	 *set(index, x)
	 *max()
	 *min()
	 *reverse()
	 *shift()
	 *rotate()
	 ***/

	
};

template <typename Type>
bool slice<Type>::is_index_valid(int index) const
{
	if (index < 0 || index > m_size_-1)
	{
		return false;
	}
	return true;
}

template <typename Type>
int slice<Type>::resize(int size)
{
	std::cout << "resizing, old size : " << m_size_ << " new size : " << size << std::endl;
	Type* temp = new Type[size];
	copy(temp);
	delete[]m_arr_;

	m_arr_ = temp;
	m_size_ = size;
	temp = nullptr;
	return  m_size_;
}

template <typename Type>
void slice<Type>::copy(Type* to)
{
	for (int i = 0; i < m_size_; i++)
	{
		to[i] = m_arr_[i];
	}
}

template <typename Type>
void slice<Type>::swap(Type& x, Type& y)
{
	Type temp = x;
	x = y;
	y = temp;
}

template <typename Type>
int slice<Type>::ceil(const double x)
{
	const int int_part = static_cast<int>(x);
	const double fraction_part = x - int_part;

	return fraction_part > 0 ? int_part + 1 :int_part; 
	
}


template <typename Type>
slice<Type>::slice(int size)
{
	if (m_status_ != array_status::null)
	{
		return;
	}
	m_arr_ = new Type[size];
	m_size_ = size;
	m_len_ = 0;
	m_status_ = array_status::uninitialized;
}

template <typename Type>
slice<Type>::slice(std::initializer_list<Type> args)
{
	if (m_status_ != array_status::null)
	{
		return;
	}
	m_size_ = args.size();
	m_arr_ = new Type[m_size_];

	for (auto arg : args)
	{
		m_arr_[m_len_] = arg;
		m_len_++;
	}
	m_status_ = array_status::initialized;
}

template <typename Type>
slice<Type>::slice(slice<Type>& s)
{
	m_arr_ = new Type[s.m_size_];
	m_size_ = s.m_size_;

	for (int i = 0; i < s.m_len_;i++)
	{
		m_arr_[i] = s.m_arr_[i];
	}

	m_len_ = s.m_len_;
	m_status_ = initialized;
}

template <typename Type>
void slice<Type>::append(Type x)
{
	if (m_len_ == m_size_)
	{
		const int temp_size = m_size_;
		if (temp_size >= resize(m_size_ + DEFAULT_ARRAY_SIZE))
		{
			std::cerr << "Attempt to resize slice failed" << std::endl;
			return;
		}
		
	}

	if (m_len_ < m_size_ )
	{
		m_arr_[m_len_] = x;
		m_len_++;
		if (m_status_ != array_status::initialized)
		{
			m_status_ = array_status::initialized;
		}
	}
}

template <typename Type>
void slice<Type>::display()
{
	for (int i = 0; i < m_len_; i++)
	{
		std::cout << m_arr_[i] << "\t";
	}
	std::cout << std::endl;
}

template <typename Type>
void slice<Type>::print()
{
	if(std::is_same_v<Type, char>)
	{
		for (int i = 0; i < m_len_; i++)
		{
			std::cout << m_arr_[i];
		}
		std::cout << std::endl;
	}
	else
	{
		std::cerr << "Cannot print contents of array for non-char types" << std::endl;
	}
}

//insert at give index, moves to elements right to make space for new element
template<typename Type>
void slice<Type>::insert(int index, Type x)
{
	if (is_index_valid(index) && index <= m_len_)
	{
		if (m_len_ == m_size_)
		{
			const int temp_size = m_size_;
			if(temp_size >= resize(m_size_ + DEFAULT_ARRAY_SIZE))
			{
				std::cerr << "Attempt to insert at index : " << index  <<" failed cant resize slice" << std::endl;
				return;
			}
		}

		for (int i = m_len_; i > index;i-- )
		{
			m_arr_[i] = m_arr_[i-1];
		}
		m_arr_[index] = x;
		m_len_++;
	}
	else
	{
		std::cout << "Invalid Index" << std::endl;
	}
}

template <typename Type>
void slice<Type>::remove(int index)
{
	if (is_index_valid(index) && index <= m_len_)
	{
		for (int i = index; i < m_len_-1; i++)
		{
			m_arr_[i] = m_arr_[i + 1];
		}
		m_len_--; 
	}
}

template <typename Type>
int slice<Type>::search(const Type x,const search_type s_type, const search_mode s_mode)
{
	if (s_type == linear_search)
	{
		for(int i = 0; i < m_len_; i++)
		{
			if (m_arr_[i]==x)
			{
				if (s_mode!=search_mode::none)
				{
					if (s_mode == transposition && i > 0)
					{
						swap(m_arr_[i], m_arr_[i - 1]);
					}
					else
					{
						swap(m_arr_[i], m_arr_[0]);
					}
				}
				return i;
			}
		}
		return -1;
	}
		
	if (s_type==binary_search)
	{
		 int begin = 0, end = m_len_-1, mid = ceil((begin + end) / 2.0);
		 while(begin <= end)
		 {
			 if (m_arr_[mid]==x)
			 {
				 return mid;
			 }

		 	 if (x < m_arr_[mid])
			 {
				 end = mid - 1;
				 mid = ceil((begin + end) / 2.0);
			 	continue;
			 }

		 	 if (x > m_arr_[mid])
			 {
				 begin = mid + 1;
				 mid = ceil((begin + end) / 2.0);
			 }
		 }
		return -1;
	}
	return -2;
}


template <typename Type>
debug_info slice<Type>::get_debug_info() const
{
	debug_info d = {};
	d.len = m_len_;
	d.size = m_size_;

	return d;
}
