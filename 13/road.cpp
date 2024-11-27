#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class UnionFind 
{
private:
    vector<int> parent, rank;
    int components;

public:
    UnionFind(int n) 
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        components = n;

        for (int i = 1; i <= n; ++i) 
        {
            parent[i] = i;
        }
    }

    int find(int x) 
    {
        if (parent[x] != x) 
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) 
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) 
            {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) 
            {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            components--;
        }
    }

    int getComponents() 
    {
        return components;
    }
};

int main() 
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, q;
    input >> n >> q;

    UnionFind uf(n);
    vector<int> results;

    for (int i = 0; i < q; ++i) 
    {
        int u, v;
        input >> u >> v;
        uf.unite(u, v);
        results.push_back(uf.getComponents());
    }

    for (int res : results) 
    {
        output << res << '\n';
    }

    return 0;
}
