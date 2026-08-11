#include "compare.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


bool compareFiles(const string &expectedFile,
                  const string &generatedFile)
{
    ifstream expected(expectedFile);
    ifstream generated(generatedFile);

    if (!expected.is_open())
    {
        cout << "Cannot open: "
                  << expectedFile
                  << endl;

        return false;
    }

    if (!generated.is_open())
    {
        cout << "Cannot open: "
                  << generatedFile
                  << endl;

        return false;
    }

    string line1;
    string line2;

    int lineNo = 1;

    while (true)
    {
        bool ok1 = static_cast<bool>(getline(expected, line1));
        bool ok2 = static_cast<bool>(getline(generated, line2));

        if (!ok1 && !ok2)
            return true;

        if (ok1 != ok2)
        {
            cout << "\nDifferent number of lines.\n";
            return false;
        }

        if (line1 != line2)
        {
            cout << "\nDifference at line "
                      << lineNo
                      << endl;

            cout << "Expected : "
                      << line1
                      << endl;

            cout << "Generated: "
                      << line2
                      << endl;

            return false;
        }

        lineNo++;
    }
}