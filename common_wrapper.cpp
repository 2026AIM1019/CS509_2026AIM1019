#include <cstdlib>
#include <iostream>

int main()
{
    int choice;

    std::cout << "\n========================================\n";
    std::cout << "       Assignment Runner\n";
    std::cout << "========================================\n";
    std::cout << "1. Assignment 01\n";
    std::cout << "2. Assignment 02\n";
    std::cout << "3. Assignment 03\n";
    std::cout << "0. Exit\n";
    std::cout << "========================================\n";

    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    const char* command = nullptr;

    switch (choice)
    {
        case 1:
            command = "cd assignment_01 && ./driver/driver";
            break;

        case 2:
            command = "cd assignment_02 && ./graph_runner";
            break;

        case 3:
            command = "cd assignment_03 && ./mst_driver";
            break;

        case 0:
            std::cout << "Exiting...\n";
            return 0;

        default:
            std::cerr << "Invalid choice. Please select 0, 1, 2, or 3.\n";
            return 1;
    }

    std::cout << "\nRunning Assignment " << choice << "...\n\n";

    int result = std::system(command);

    if (result != 0)
    {
        std::cerr << "\nAssignment " << choice
                  << " exited with an error.\n";
        return result;
    }

    return 0;
}
