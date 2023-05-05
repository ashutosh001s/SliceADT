#include "slice.h"

typedef slice<int> slice_int;
typedef slice<char> slice_char;

int main()
{
	slice_int s(3);

	s.append(2);
	s.append(4);
	s.append(5);
	s.append(7);
	s.insert(4, 3);
	s.remove(2);


	s.display();

	slice_int s2 = s;
	s2.display();

	
	std::cout<< "len : " << s.get_debug_info().len << std::endl;
	std::cout << "size : " << s.get_debug_info().size << std::endl;
	std::cin.get();
	return 0;
}
