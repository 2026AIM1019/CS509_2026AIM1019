#include <iostream>

#include "runner.h"

using namespace std;

int main()
{
    int choice;

    while (true)
    {
        cout << "\n";
        cout << "      Graph Algorithms Test Runner\n";
        cout << "1. Bellman-Ford\n";
        cout << "2. Floyd-Warshall\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                runBellmanFord();
                break;

            case 2:
                runFloydWarshall();
                break;

            case 0:
                cout << "\nExiting...\n";
                return 0;

            default:
                cout << "\nInvalid choice.\n";
        }
    }

    return 0;
}
