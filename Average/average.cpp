#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(0) {}
};

Node* insert(Node* root, int key);
Node* deleteNode(Node* root, int key);
void preOrderTraversal(Node* node, FILE* output);
void collectRoots(Node* node, vector<int>& equalHeightKeys);

int main() {
    FILE* input = fopen("tst.in", "r");
    FILE* output = fopen("tst.out", "w");

    Node* root = nullptr;
    int key;
    while (fscanf(input, "%d", &key) != EOF) 
    {
        root = insert(root, key);
    }
    fclose(input);

    vector<int> equalHeightKeys;
    collectRoots(root, equalHeightKeys);

    sort(equalHeightKeys.begin(), equalHeightKeys.end());

    if (equalHeightKeys.size() % 2 == 1) 
    {
        int middleKey = equalHeightKeys[equalHeightKeys.size() / 2];
        root = deleteNode(root, middleKey);
    }

    preOrderTraversal(root, output);

    fclose(output);
    return 0;
}

Node* insert(Node* root, int key) 
{
    if (!root) return new Node(key);
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    root->height = max(root->left ? root->left->height : -1, root->right ? root->right->height : -1) + 1;
    return root;
}

Node* findMin(Node* node) 
{
    while (node && node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) 
{
    if (!root) return nullptr;
    
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) 
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        Node* minLargerNode = findMin(root->right);
        root->key = minLargerNode->key;
        root->right = deleteNode(root->right, minLargerNode->key);
    }
    root->height = max(root->left ? root->left->height : -1, root->right ? root->right->height : -1) + 1;
    return root;
}

void collectRoots(Node* node, vector<int>& equalHeightKeys) 
{
    if (!node) return;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    if (leftHeight == rightHeight) {
        equalHeightKeys.push_back(node->key);
    }

    collectRoots(node->left, equalHeightKeys);
    collectRoots(node->right, equalHeightKeys);
}

void preOrderTraversal(Node* node, FILE* output) 
{
    if (!node) return;
    fprintf(output, "%d\n", node->key);
    preOrderTraversal(node->left, output);
    preOrderTraversal(node->right, output);
}
