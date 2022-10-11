#include "48_rotate.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include <vector>

using namespace std;
//https://leetcode.cn/problems/rotate-image/
//旋转图像
//给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
//你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
void rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    if(n == 0) return;
    int colhalf = n / 2 + 1;
    int rowhalf = n / 2;
    n--;
    for (int startRow = 0; startRow < rowhalf; startRow++)
    {
        for(int startCol = startRow; startCol < colhalf - startRow; startCol++)
        {
            int i = startRow;
            int j = startCol;
            do
            {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n - j][i];
                matrix[n - j][i] = tmp;
                tmp = i;
                i = n - j;
                j = tmp;
            } while (!(n - j == startRow && i == startCol));
        }
    }
}

Rotate::Rotate(/* args */) 
{
    vector<vector<int>> matrix={{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    rotate(matrix);
    for(auto ma : matrix)
        COUTI(ma);
}

CUSTOMEGISTER(Rotate,Rotate)