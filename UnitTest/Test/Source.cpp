#include <iostream>
#include <Matrix2.h>
#include <Vector2.h>

int main()
{
	Matrix2 mat(1, 2, 3, 1);
	Matrix2 mat1(2, 2, 1, 1);
	Matrix2 res = mat * mat1;
	Vector2 vec(1, 2);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			std::cout << res.mm[i][j] << "\t";
		}
		std::cout << "\n";
	}

	Vector2 vRes = res * vec;
	std::cout << vRes.m_x << ", " << vRes.m_y;

	std::cin.get();

	return 0;
}