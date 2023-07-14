#include "dstypes.h"
#include "string"

int main()
{
	ds::slice_int s(20);

	


	//{2, 3, -4, 5, 6, -3, 19, -7, -20,7};

	s.append(2);
	s.append(3);
	s.append(-4);
	s.append(5);
	s.append(6);
	s.append(-3);
	s.append(19);
	s.append(-7);
	s.append(-20);
	s.append(7);
	s.append(0);

	s.sudo_sort();
	//const std::string msg = s.is_sorted() == true ? "True" : "False";
	//std::cout << msg;

	s.display();

	//debug info
	std::cout << std::endl;
	std::cout<< "len : " << s.get_debug_info().len << std::endl;
	std::cout << "size : " << s.get_debug_info().size << std::endl;

	std::cin.get();

	return 0;
}
