#include "../src/graph.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

string testFile(int t)
{
    return "tests/mst/test_0" + to_string(t) + ".txt";
}

long long expected(string a, int t)
{
    ifstream f("outputs/" + a + "/test_0" + to_string(t) + ".txt");
    string line;
    getline(f, line);
    getline(f, line);
    return stoll(line.substr(line.find(":") + 1));
}

void print(MSTResult r)
{
    sortMSTEdges(r.edges);
    cout << "MST edges:\n";
    for (auto e : r.edges)
        cout << e.u << " " << e.v << " " << e.weight << "\n";
    cout << "\nTotal MST weight: " << r.totalWeight << "\n";
}

void check(string a, int t, long long w)
{
    long long e = expected(a, t);
    cout << "Expected MST weight: " << e << "\n";
    cout << "Validation: " << (w == e ? "PASS" : "FAIL") << "\n";
}

int main()
{
    while (true)
    {
        int choice;
        cout << "\n1. Kruskal's MST\n2. Prim's MST\n3. Run both and compare\n0. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 0)
            break;
        if (choice < 1 || choice > 3)
        {
            cout << "Invalid choice.\n";
            continue;
        }
        int t;
        cout << "\n1. test_01.txt (V=10)\n2. test_02.txt (V=100)\n3. test_03.txt (V=10000)\n4. test_04.txt (V=50000)\n5. test_05.txt (V=100000)\nEnter test case: ";
        cin >> t;
        if (t < 1 || t > 5)
        {
            cout << "Invalid test case.\n";
            continue;
        }

        Graph g;
        if (!readGraph(testFile(t), g))
            continue;
        CSRGraph c = convertToCSR(g);

        if (choice == 1)
        {
            auto s = chrono::high_resolution_clock::now();
            auto r = kruskal(g);
            auto e = chrono::high_resolution_clock::now();
            print(r);
            cout << fixed << setprecision(6) << "Execution time: " << chrono::duration<double, milli>(e - s).count() << " ms\n";
            check("kruskals", t, r.totalWeight);
        }
        else if (choice == 2)
        {
            auto s = chrono::high_resolution_clock::now();
            auto r = prim(c);
            auto e = chrono::high_resolution_clock::now();
            print(r);
            cout << fixed << setprecision(6) << "Execution time: " << chrono::duration<double, milli>(e - s).count() << " ms\n";
            check("prims", t, r.totalWeight);
        }
        else
        {
            auto s1 = chrono::high_resolution_clock::now();
            auto k = kruskal(g);
            auto e1 = chrono::high_resolution_clock::now();
            auto s2 = chrono::high_resolution_clock::now();
            auto p = prim(c);
            auto e2 = chrono::high_resolution_clock::now();

            cout << "\nKruskal's MST\n";
            print(k);
            cout << "Execution time: " << chrono::duration<double, milli>(e1 - s1).count() << " ms\n";
            check("kruskals", t, k.totalWeight);
            cout << "\nPrim's MST\n";
            print(p);

            cout << "Execution time: " << chrono::duration<double, milli>(e2 - s2).count() << " ms\n";
            check("prims", t, p.totalWeight);
            cout << "\nKruskal vs Prim: " << (k.totalWeight == p.totalWeight ? "PASS" : "FAIL") << "\n";
        }
        
        cout << "\nTest finished. Returning to menu...\n";
    }
    return 0;
}
