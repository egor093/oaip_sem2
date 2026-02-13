#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_DEPTH = 10;
const int MAX_NODES = 1024;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}

struct QueueNode {
    Node* node;
    int level;
};

struct SimpleQueue {
    QueueNode data[MAX_NODES];
    int front = 0;
    int back = 0;

    void push(Node* n, int lvl) {
        if (back < MAX_NODES) {
            data[back].node = n;
            data[back].level = lvl;
            back++;
        }
    }

    QueueNode pop() {
        return data[front++];
    }

    bool empty() const {
        return front == back;
    }
};

void printLevelSums(Node* root) {
    if (!root) return;

    int levelSums[MAX_DEPTH] = { 0 };

    SimpleQueue q;
    q.push(root, 0);

    while (!q.empty()) {
        QueueNode current = q.pop();
        Node* node = current.node;
        int level = current.level;

        levelSums[level] += node->value;

        if (node->left)
            q.push(node->left, level + 1);
        if (node->right)
            q.push(node->right, level + 1);
    }

    for (int i = 0; i < MAX_DEPTH; ++i) {
        if (levelSums[i] != 0 || i == 0)
            cout << "Сумма на уровне " << i << ": " << levelSums[i] << endl;
    }
}

void printTree(Node* root, int space = 0, int indent = 5) {
    if (root == nullptr) return;

    space += indent;

    printTree(root->right, space);

    cout << setw(space) << root->value << endl;

    printTree(root->left, space);
}

int main() {
    setlocale(LC_ALL, "rus");
    Node* root = nullptr;
    int values[] = { 10, 5, 15, 3, 7, 12, 18 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; ++i) {
        root = insert(root, values[i]);
    }

    cout << "Структура дерева:\n";
    printTree(root);

    cout << "\nСуммы по уровням:\n";
    printLevelSums(root);
    return 0;
}
