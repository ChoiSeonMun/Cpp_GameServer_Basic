#include "stdafx.h"

int main()
{
	if (int v = INT_MAX; CheckOverflow(v, 10))
	{
		puts("Error");
	}
	return 0;
}