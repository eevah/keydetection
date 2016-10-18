//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2016 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<std::vector<std::vector<double>>>> ReturnRectangularDoubleVector(int size1, int size2, int size3, int size4)
    {
        std::vector<std::vector<std::vector<std::vector<double>>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<std::vector<double>>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<std::vector<double>>(size3);
                    if (size4 > -1)
                    {
                        for (int vector3 = 0; vector3 < size3; vector3++)
                        {
                            newVector[vector1][vector2][vector3] = std::vector<double>(size4);
                        }
                    }
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<double>> ReturnRectangularDoubleVector(int size1, int size2)
    {
        std::vector<std::vector<double>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<double>(size2);
        }

        return newVector;
    }
};