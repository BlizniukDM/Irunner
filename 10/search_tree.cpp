#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    long long key;
    int left;
    int right;
};

bool isBST(const vector<Node>& tree) {
    if (tree.empty()) {
        return true;
    }

    stack<tuple<int, long long, long long>> s;
    s.push({0, numeric_limits<long long>::min(), numeric_limits<long long>::max()});

    while (!s.empty()) {
        auto [nodeIndex, minVal, maxVal] = s.top();
        s.pop();

        const Node& node = tree[nodeIndex];

        if (node.key < minVal || node.key > maxVal) {
            return false;
        }

        if (node.right != -1) {
            s.push({node.right, node.key, maxVal});
        }

        if (node.left != -1) {
            s.push({node.left, minVal, node.key - 1});
        }
    }

    return true;
}

int main() {
    FILE *input = fopen("bst.in", "r");
    FILE *output = fopen("bst.out", "w");

    if (!input || !output) {
        cerr << "Failed to open input or output file." << endl;
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);

    if (n == 0) {
        fprintf(output, "YES\n");
        fclose(input);
        fclose(output);
        return 0;
    }

    vector<Node> tree(n);

    fscanf(input, "%lld", &tree[0].key);
    tree[0].left = tree[0].right = -1;

    for (int i = 1; i < n; ++i) {
        long long key;
        int parentIndex;
        char direction;

        fscanf(input, "%lld %d %c", &key, &parentIndex, &direction);

        tree[i].key = key;
        tree[i].left = tree[i].right = -1;

        if (parentIndex < 1 || parentIndex > n) {
            fprintf(output, "NO\n");
            fclose(input);
            fclose(output);
            return 0;
        }

        if (direction == 'L') {
            if (tree[parentIndex - 1].left != -1) {
                fprintf(output, "NO\n");
                fclose(input);
                fclose(output);
                return 0;
            }
            tree[parentIndex - 1].left = i;
        } else if (direction == 'R') {
            if (tree[parentIndex - 1].right != -1) {
                fprintf(output, "NO\n");
                fclose(input);
                fclose(output);
                return 0;
            }
            tree[parentIndex - 1].right = i;
        } else {
            fprintf(output, "NO\n");
            fclose(input);
            fclose(output);
            return 0;
        }
    }

    if (isBST(tree)) {
        fprintf(output, "YES\n");
    } else {
        fprintf(output, "NO\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}
