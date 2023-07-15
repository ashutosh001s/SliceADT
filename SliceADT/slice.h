#pragma once
#include "initializer_list"
#include "iostream"

#define DEFAULT_ARRAY_SIZE 2  // NOLINT(modernize-macro-to-enum)



namespace ds
{
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

	struct SearchResult
	{
		const bool status;
		const int index;
		const int element;
		const std::string error;
	};

	template <typename Type>
	class slice
	{
	private:
		//properties
		Type* m_arr_;
		int m_len_;
		int m_size_;
		bool m_b_debug_ = false;

		//helper properties
		array_status m_status_ = array_status::null;

		//helper methods
		bool is_index_valid(int index) const;
		bool is_index_between_length(int index) const;
		int resize(int size);
		void copy(Type* to);
		void swap(Type& x, Type& y) noexcept(true);

	public:
		//constructor
		slice(int size = 0,const bool b_debug = false);
		slice(std::initializer_list<Type> args);
		slice(slice<Type>& s);
		~slice();
		static int ceil(const double x);

		//PUBLIC helper
		debug_info get_debug_info() const;

		//public methods
		void append(Type x);
		void display();
		void print();
		void insert(int index, Type x);
		void remove(int index);

		/**
		 * \brief search the element in slice, and returns index if found else -1
		 * \param x element to search
		 * \param s_type use binary search if slice is sorted
		 * \param s_mode only works with linear search, transposition is recommended search mode, change it to move_to_head if a elements is repeatedly needed, if you don't want to change the position of elements in slice switch to search_mode::none
		 * \param b_sort Allow sorting ,if not already sorted
		 * \return returns index if element found , -1 if not found and -2 if something went wrong
		 */
		SearchResult search(const Type x, const search_type s_type = search_type::linear_search, const search_mode s_mode = search_mode::transposition, const bool b_sort = false);

		Type get(const int index) noexcept(false);
		bool set(const Type x, int index = 0);
		Type max();
		Type min();
		void reverse();
		bool is_sorted();
		void sudo_sort();
		void sort();

		void show_debug_info();
		/**
		 *shift	()
		 *rotate()
		 ***/


	};

	template <typename Type>
	bool slice<Type>::is_index_valid(int index) const
	{
		if (index < 0 || index > m_size_ - 1)
		{
			return false;
		}
		return true;
	}

	template <typename Type>
	bool slice<Type>::is_index_between_length(const int index) const
	{
		if (is_index_valid(index) && index <= m_len_)
		{
			return true;
		}
		return false;
	}

	template <typename Type>
	int slice<Type>::resize(int size)
	{
		if (m_b_debug_)
		{
			std::cout << "resizing, old size : " << m_size_ << " new size : " << size << std::endl;
		}

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
	void slice<Type>::swap(Type& x, Type& y) noexcept(true)
	{
		Type temp = x;
		x = y;
		y = temp;
	}

	template <typename Type>
	slice<Type>::~slice()
	{
		delete[]m_arr_;
		
	}

	template <typename Type>
	int slice<Type>::ceil(const double x)
	{
		const int int_part = static_cast<int>(x);
		const double fraction_part = x - int_part;

		return fraction_part > 0 ? int_part + 1 : int_part;

	}


	template <typename Type>
	slice<Type>::slice(const int size,const bool b_debug)
		: m_b_debug_(b_debug)
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

		for (int i = 0; i < s.m_len_; i++)
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

		if (m_len_ < m_size_)
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
		if (std::is_same_v<Type, char>)
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
		if (is_index_between_length(index))
		{
			if (m_len_ == m_size_)
			{
				const int temp_size = m_size_;
				if (temp_size >= resize(m_size_ + DEFAULT_ARRAY_SIZE))
				{
					std::cerr << "Attempt to insert at index : " << index << " failed cant resize slice" << std::endl;
					return;
				}
			}

			for (int i = m_len_; i > index; i--)
			{
				m_arr_[i] = m_arr_[i - 1];
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
		if (is_index_between_length(index))
		{
			for (int i = index; i < m_len_ - 1; i++)
			{
				m_arr_[i] = m_arr_[i + 1];
			}
			m_len_--;
		}
	}

	template <typename Type>
	SearchResult slice<Type>::search(const Type x, const search_type s_type, const search_mode s_mode, const bool b_sort)
	{
		if (s_type == linear_search)
		{
			for (int i = 0; i < m_len_; i++)
			{
				if (m_arr_[i] == x)
				{
					if (s_mode != search_mode::none)
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
					return {true, i, x, "none"};
				}
			}
			return { false, -1, x, "Element not found" };
		}

		if (s_type == binary_search)
		{
			if (!is_sorted() && b_sort == false)
			{
				return { false, -1, x, "Cant perform binary search , Array is not sorted" };
			}

			if (b_sort)
			{
				sort();
			}

			int begin = 0, end = m_len_ - 1;
			while (begin <= end)
			{
				//im using ceil value for mid to demonstrate both floor or ceil value works with binary search in case mid point calculation [ begin + end/2 gives ] you a decimal number
				int mid = ceil((begin + end) / 2.0);
				if (m_arr_[mid] == x)
				{
					return { true, mid, x, "none" };
				}

				if (x < m_arr_[mid])
				{
					end = mid - 1;
					continue;
				}

				if (x > m_arr_[mid])
				{
					begin = mid + 1;
				}
			}
			return { false, -1, x, "Element not found" };
		}
		return { false, -2, x, "Unknown Error Occoured" };
	}

	template <typename Type>
	Type slice<Type>::get(const int index) noexcept(false)
	{
		try
		{
			if (is_index_between_length(index))
				return m_arr_[index];

			throw std::out_of_range("Index out of range");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
		return Type{};
	}

	template <typename Type>
	bool slice<Type>::set(const Type x, const int index)
	{
		if (is_index_between_length(index))
		{
			if (is_sorted())
			{
				if (m_len_ == m_size_)
				{
					resize(m_size_ + DEFAULT_ARRAY_SIZE);
				}

				int i = m_len_ - 1;
				while (m_arr_[i] > x)
				{

					m_arr_[i + 1] = m_arr_[i];
					i--;
				}
				m_arr_[i + 1] = x;
				m_len_++;
				return true;
			}

			if (index == -1)
				return false;
			m_arr_[index] = x;
			return m_arr_[index] == x;
		}
		return false;
	}

	template <typename Type>
	Type slice<Type>::max()
	{
		Type max = m_arr_[0];
		for (int i = 1; i < m_len_; i++)
		{
			if (m_arr_[i] > max)
			{
				max = m_arr_[i];
			}
		}
		return max;
	}

	template <typename Type>
	Type slice<Type>::min()
	{
		Type min = m_arr_[0];
		for (int i = 1; i < m_len_; i++)
		{
			if (m_arr_[i] < min)
			{
				min = m_arr_[i];
			}
		}
		return min;
	}

	template <typename Type>
	void slice<Type>::reverse()
	{
		for (std::size_t i = 0, j = m_len_ - 1; i < j; i++, j--)
		{
			swap(m_arr_[i], m_arr_[j]);
		}
	}

	template <typename Type>
	bool slice<Type>::is_sorted()
	{
		for (int i = 0; i < m_len_ -1; i++)
		{
			if (m_arr_[i] > m_arr_[i+1])
			{
				return false;
			}
		}
		return true;
	}

	template <typename Type>
	void slice<Type>::sudo_sort()
	{
		int i = 0;
		int j = m_len_ - 1;

		while (i < j)
		{
			while (m_arr_[i] < 0)
			{
				i++;
			}

			while (m_arr_[j] >= 0)
			{
				j--;
			}

			if (i < j)
			{
				swap(m_arr_[i], m_arr_[j]);

			}
		}
	}

	template <typename Type>
	void slice<Type>::sort()
	{
		while (!is_sorted())
		{
			for (int i = 0; i < m_len_-1; i++)
			{
				if (m_arr_[i] > m_arr_[i + 1])
				{
					swap(m_arr_[i], m_arr_[i + 1]);

				}
			}
		}
	}

	template <typename Type>
	void slice<Type>::show_debug_info()
	{
		std::cout << std::endl;
		this->display();
		std::cout << std::endl;

		const debug_info debug = this->get_debug_info();
		std::cout << "len : " << debug.len << std::endl;
		std::cout << "size : " << debug.size << std::endl;
	}


	template <typename Type>
	debug_info slice<Type>::get_debug_info() const
	{
		debug_info d = {};
		d.len = m_len_;
		d.size = m_size_;

		return d;
	}

}