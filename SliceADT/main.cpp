#include "dstypes.h"
#include "string"
#include "cstdio"

int main()
{
	ds::slice_int s(0);

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

	const ds::SearchResult& search_result = s.search(7, ds::binary_search, ds::none, true);
	if (search_result.status)
	{
		printf("Element %u found at index : %u\n", search_result.element, search_result.index);
	}
	else
	{
		printf("%s\n", search_result.error.c_str());
	}

	s.show_debug_info();

	return 0;
}
