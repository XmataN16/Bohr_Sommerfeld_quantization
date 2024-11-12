#pragma once
// Функция для сохранения значений массива в файл
void save_array_to_file(const double* array, int size, const std::string& filename) 
{
    std::ofstream file(filename);
    if (file.is_open()) 
    {
        for (int i = 0; i < size; ++i) 
        {
            file << array[i] << "\n";
        }
        file.close();
        std::cout << "Array saved to " << filename << "\n";
    }
    else 
    {
        std::cerr << "Unable to open file " << filename << "\n";
    }
}

// Функция для сохранения значений из std::list в файл
void save_list_to_file(const std::list<double>& list, const std::string& filename) 
{
    std::ofstream file(filename);
    if (file.is_open()) 
    {
        for (const double& value : list) 
        {
            file << value << "\n";
        }
        file.close();
        std::cout << "List saved to " << filename << "\n";
    }
    else 
    {
        std::cerr << "Unable to open file " << filename << "\n";
    }
}
