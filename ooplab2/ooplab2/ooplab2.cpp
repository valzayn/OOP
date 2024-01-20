#include <iostream>

int main()
{
    int rows;       
    int columns; 
    int s, k;
    std::cin >> rows >> columns;
    int** numbers = new int* [rows] {};
    int* arr_s = new int[columns] {};
    for (int i{}; i < rows; i++)
    {
        numbers[i] = new int[columns] {};
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cin >> numbers[i][j];
        }
    }
  
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << numbers[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; i++)
    {
        s = 0;
        for (int j = 0; j < columns; j++)
        {
            s += numbers[j][i];
        }
        arr_s[i] = s;
    }
    for (int i = 0; i < rows; i++) {
        std::cout << arr_s[i] << " ";
    }
    k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (arr_s[i] - numbers[i][j] < numbers[i][j]) {
                k++;
            }
        }
        std::cout << std::endl;
    }
    std::cout << k << "\n";
}