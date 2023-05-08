#include "slice.h"
#include "string"

typedef slice<int> slice_int;
typedef slice<char> slice_char;
typedef slice<std::string> slice_str;

int main()
{
	slice_int s(3);

	s.append(2);
	s.append(4);
	s.append(5);
	s.append(7);


	//debug info
	std::cout << std::endl;
	std::cout<< "len : " << s.get_debug_info().len << std::endl;
	std::cout << "size : " << s.get_debug_info().size << std::endl;
	std::cin.get();
	return 0;
}
