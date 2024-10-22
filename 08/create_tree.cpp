#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct Node 
{
    int key;
    Node* left;
    Node* right;
    
    Node(int value) : key(value), right(nullptr), left(nullptr) {}
};

Node* insert(Node* root, int key);
void preOrder(Node* root, ofstream &output);

int main() 
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    Node* root = nullptr;
    int key;

    while (input >> key) 
    {
        root = insert(root, key);
    }

    preOrder(root, output);

    input.close();
    output.close();

    return 0;
}

Node* insert(Node* root, int key) 
{
    if (root == nullptr) 
    {
        return new Node(key);
    }
    else if (key < root->key) 
    {
        root->left = insert(root->left, key);
    } 
    else if (key > root->key) 
    {
        root->right = insert(root->right, key);
    }
    return root;
}

void preOrder(Node* root, ofstream &output) 
{
    if (root != nullptr) 
    {
        output << root->key << "\n";
        preOrder(root->left, output);
        preOrder(root->right, output);
    }
}

