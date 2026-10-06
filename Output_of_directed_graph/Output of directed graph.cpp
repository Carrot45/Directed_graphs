#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int** create_two_array(int rows, int columns);
void fill_two_array(int** array, int rows, int columns);
void print_two_array(int** array, int rows, int columns);
void delete_two_array(int** array_address, int rows);

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int rows{}, columns{};
    std::ifstream input_file{ "in.txt" };
    if (input_file.is_open())
    {
        input_file >> rows;
        columns = rows;
    }
    input_file.close();
    int** array{ create_two_array(rows, columns) };
    fill_two_array(array, rows, columns);
    print_two_array(array, rows, columns);
    std::cout << std::endl;
    std::cout << "Текстовый вид орграфа:" << std::endl;
    for (int row{}; row <= rows - 1; ++row)
    {
        bool exist{ false };
        std::cout << row << ": ";
        for (int column{}; column <= columns - 1; ++column)
        {
            
            if (array[row][column] == 1)
            {
                std::cout << column + 1 << " ";
                exist = true;
            }
        }

        if (exist == false)
        {
            std::cout << "нет" << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }

    delete_two_array(array, rows);

    return EXIT_SUCCESS;
}

int** create_two_array(int rows, int columns)
{
    int** integers{ new int* [rows] };
    for (int row{}; row < rows; ++row)
    {
        integers[row] = new int[columns] {};
    }
    return integers;
}

void fill_two_array(int** array_address, int rows, int columns)
{
    std::fstream input_file;
    input_file.open("in.txt", std::fstream::in);
    input_file.seekg(3, std::ios::beg);
    if (input_file.is_open())
    {
        for (int row{}; row < rows; ++row)
        {
            for (int column{ 0 }; column <= rows - 1; ++column)
            {
                int temp{};

                input_file >> temp;
                array_address[row][column] = temp;
            }
        }
    }
    input_file.close();
}

void print_two_array(int** array_address, int rows, int columns)
{
    std::cout << rows << std::endl;
    for (int row{}; row < rows; ++row)
    {
        for (int column{}; column < columns; ++column)
        {
            std::cout << array_address[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void delete_two_array(int** array_address, int rows)
{
    for (int current_row{}; current_row < rows; ++current_row)
    {
        delete[] array_address[current_row];
    }
    delete[] array_address;
}