#include <iostream>

using namespace std;

struct Node{
    int parent;
    int money;
};

struct Node* findParent(int x, struct Node nodes[]) {
    if(x == nodes[x].parent)
        return &nodes[x];
    return findParent(nodes[x].parent, nodes);
}

void mergeNodes(int num1, int num2, struct Node nodes[]) {
    struct Node* x = findParent(num1, nodes);
    struct Node* y = findParent(num2, nodes);
    if(x->money < y->money)
        x->parent = y->parent;
    else
        y->parent = x->parent;
}


int main() {
    int n, q;
    cin >> n;
    cin >> q;

    int moneys[n];
    struct Node nodes[n];
    for (int i = 0; i < n; ++i) {
        cin >> moneys[i];
        nodes[i].parent = i;
        nodes[i].money = moneys[i];
    }

    int command, first, second;
    for (int i = 0; i < q; ++i) {
        cin >> command;
        if (command == 2) {
            cin >> first;
            cin >> second;
            mergeNodes(first-1, second-1, nodes);
        } else {
            cin >> first;
            cout << findParent(first - 1, nodes)->money;
            cout << "\n";
        }
    }
    return 0;
}