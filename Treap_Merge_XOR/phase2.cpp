// 400109638
#include <bits/stdc++.h>

using namespace std;

long long int m = (long long int)pow(2, 17);

struct item {
    int key, priority;
    int count, max;
    long long int XOR;
    item *left, *right;
    item(int key) : key(key), priority(rand()), count(1), left(nullptr), right(nullptr) { }
} *root ;


typedef item* pitem;


long long int hashKey(int key) {
    return ((34521 * key + 75328) % ((long long int)(1e7) + 9)) % m;
}

long long int calcXOR(pitem &trp) {
    return trp ? trp->XOR : 0;
}

void updateXOR(pitem &trp) {
    if (trp) {
        trp->XOR = (calcXOR(trp->left) ^ calcXOR(trp->right)) ^ hashKey(trp->key);
    }
}

int calcCnt (pitem trp) {
    return trp ? trp->count : 0;
}

void updateCnt (pitem &trp) {
    if (trp)
        trp->count = 1 + calcCnt(trp->left) + calcCnt(trp->right);
}

int calcMax(pitem &trp) {
    return trp ? trp->max : INT_MIN;
}

void updateMax(pitem &trp) {
    if (trp)
        trp->max = max(trp->key, max(calcMax(trp->right), calcMax(trp->left)));
}

void merge (pitem &trp, pitem rt, pitem lft) {
    if (!lft || !rt)
        trp = lft ? lft : rt;
    else if (lft->priority > rt->priority) {
        merge(lft->right, rt, lft->right);
        trp = lft;
    }
    else {
        merge(rt->left, rt->left, lft);
        trp = rt;
    }
    updateMax(trp);
    updateCnt(trp);
    updateXOR(trp);
}

void split (pitem trp, pitem &lft, pitem &rt, int key, int add = 0) {
    if (!trp)
        return void(rt = lft = nullptr);

    int thisKey = calcCnt(trp->left) + add;

    if (key <= thisKey) {
        split(trp->left, lft, trp->left, key, add);
        rt = trp;
    }
    else {
        split(trp->right, trp->right, rt, key, add + 1 + calcCnt(trp->left));
        lft = trp;
    }
    updateMax(trp);
    updateCnt(trp);
    updateXOR(trp);
}

void moveItems(item *&item, int x, int y, int z) {
    pitem left, right;
    pitem m1, m2, m3;

    if (x-1 == y-2)
        return;

    z %= y - x;
    split(item, left, right, x - 1);
    split(right, m1, right, y - x);
    split(m1, m2, m3, y - x - z);

    merge(m1, m2, m3);
    merge(right, right, m1);
    merge(item, right, left);
}


int findingMax(pitem &trp, int lft, int rt) {
    pitem item1, item2, item3;
    int maximum;
    split(trp, item1, item2, lft - 1);
    split(item2, item2, item3, rt - lft);
    maximum = calcMax(item2);
    merge(trp, item2, item1);
    merge(trp, item3, trp);
    return maximum;
}

int findingXOR(pitem &trp, int lft, int rt) {
    pitem item1, item2, item3;
    long long int XOR;
    split(trp, item1, item2, lft - 1);
    split(item2, item2, item3, rt - lft);
    XOR = calcXOR(item2);
    merge(trp, item2, item1);
    merge(trp, item3, trp);

    if (XOR == 0) {
        return 0;
    } else {
        return 1;
    }
}


int main() {
    int arrLen, newItem, numberOfCommands;
    char command[15];
    int counter = 0;
    int xLeft, yRight;
    cin >> arrLen;

    while (counter != arrLen) {
        cin >> newItem;
        merge(root, new item(newItem), root);
        counter++;
    }
    counter = 0;

    cin >> numberOfCommands;
    int x, y, z;
    while (counter != numberOfCommands) {
        cin >> command;
        if (command[0] == 's') {
            cin >> x;
            cin >> y;
            cin >> z;
            moveItems(root, x, y, z);
        }
        else if (command[0] == 'm') {
            cin >> x;
            cin >> y;
            z = findingMax(root, x, y);
            cout << z << endl;
        }
        else {
            cin >> xLeft;
            cin >> yRight;
            if (findingXOR(root, xLeft, yRight) ==  0) {
                cout << "No" << endl;
            }
            else {
                cout << "Yes" << endl;
            }
        }
        counter++;
    }
}
