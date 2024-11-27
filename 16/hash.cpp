#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class HashTable 
{
private:
    vector<int> table;
    int size;          
    int step;          

public:
    HashTable(int m, int c);
    void insert(int key);
    void print(ostream& out);

private:
    int hashFunction(int key);
    int nextIndex(int baseIndex, int j);
};

int main() 
{
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int m, c, n;
    inFile >> m >> c >> n;

    HashTable hashTable(m, c);

    for (int i = 0; i < n; ++i) 
    {
        int key;
        inFile >> key;
        hashTable.insert(key);
    }

    hashTable.print(outFile);

    return 0;
}


HashTable::HashTable(int m, int c) : size(m), step(c) 
{
    table.assign(size, -1);
}

int HashTable::hashFunction(int key) 
{
    return key % size;
}

int HashTable::nextIndex(int baseIndex, int j) 
{
    return (baseIndex + step * j) % size;
}

void HashTable::insert(int key) 
{
    int baseIndex = hashFunction(key);
    for (int j = 0; j < size; ++j) 
    {
        int idx = nextIndex(baseIndex, j);
        if (table[idx] == -1 || table[idx] == key) 
        {
            table[idx] = key;
            break;
        }
    }
}

void HashTable::print(ostream& out) 
{
    for (int i = 0; i < size; ++i) 
    {
        out << table[i] << " ";
    }
    out << "\n";
}
