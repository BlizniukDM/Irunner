#include <iostream>
#include <fstream>

using namespace std;

struct Node 
{
    int key;
    Node* right;
    Node* left;
    
    Node(int value) : key(value), right(nullptr), left(nullptr) {}
};

Node* insert(Node* root, int key);
Node* minValueNode(Node* node);
Node* deleteKey(Node* root, int key);
void preOrder(Node* root, ofstream& output);

int main() 
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int keyToDelete;
    input >> keyToDelete;

    Node* root = nullptr;
    int key;
    
    while (input >> key) 
    {
        root = insert(root, key);
    }

    root = deleteKey(root, keyToDelete);

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

Node* minValueNode(Node* node) 
{
    Node* current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

Node* deleteKey(Node* root, int key) 
{
    if (root == nullptr) 
    {
        return root;
    }

    if (key < root->key) 
    {
        root->left = deleteKey(root->left, key);
    } 
    else if (key > root->key) 
    {
        root->right = deleteKey(root->right, key);
    } 
    else 
    {
        if (root->left == nullptr) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) 
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteKey(root->right, temp->key);
    }
    return root;
}

void preOrder(Node* root, ofstream& output) 
{
    if (root != nullptr) 
    {
        output << root->key << "\n";
        preOrder(root->left, output);
        preOrder(root->right, output);
    }
}
