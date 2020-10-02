

#ifndef LEETPRACTICE_TREEUTILS_H
#define LEETPRACTICE_TREEUTILS_H

#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <iterator>

#include "VectorUtils.hpp"

using namespace std;


// Definition for a Node for n-ary tree
class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    explicit Node(int val) : Val{val}, children{vector<Node *>()} {}

    Node(int val, vector<Node *> children) : Val{val}, children{children} {}
};

/**
 * print n-ary tree level by level
[0,1,2,3,4,5,6]
 */
ostream &printSquare(ostream &os, const Node *curr) {
    if (!curr) return os << "[]";
    queue<const Node *> q;
    bool startedPrinting = false;
    os << "[";
    q.push(curr);
    while (!q.empty()) {
        int nodesAtLevel = q.size();
        while (nodesAtLevel) {
            if (startedPrinting)
                os << ",";
            else
                startedPrinting = true;
            os << q.front()->Val;
            for (const auto &c : q.front()->children)
                q.push(c);
            q.pop();
            --nodesAtLevel;
        }
    }
    return os << "]";
}

// n-ary tree print
ostream &operator<<(ostream &os, const Node *curr) {
    return printSquare(os, curr);
}

// binary tree, not necessarily binary-search-tree
class TreeNode {
private:
    // converts simplified array representation to full array
    // full representiation: [0, 1, 2, 3, 4, 5, 6]
    // with nulls: [0, null, 2, null, null, 5, 6]
    // simplified version: [0, null, 2, 5, 6]
    void expandVectorToFull(vector<int> &v, int nullValue = INT_MIN);

    // given a vector representing a complete tree, construct the tree
    void vector2tree(const vector<int> &v);

    // given a comman separated string with "null"s convert it to a vector
    static vector<int> string2vector(string s);

    // can also use "template<typename T>" with T rather than "function<void (int)>"
    void inorder(TreeNode *r, function<void(int)> fptr);

    void preorder(TreeNode *r, function<void(int)> fptr);

    void postorder(TreeNode *r, function<void(int)> fptr);

    void inorder(TreeNode *r, function<void(TreeNode *)> fptr);

    void preorder(TreeNode *r, function<void(TreeNode *)> fptr);

    void postorder(TreeNode *r, function<void(TreeNode *)> fptr);


public:
    int val;
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};

    explicit TreeNode(int x);

    explicit TreeNode(const vector<int> &v, int nullValue = INT_MIN);

    explicit TreeNode(const string &s);

    ~TreeNode();

    int depth() const;

    bool isLeaf() const;

    // does not assume BST, target can be at left or right
    TreeNode *findItem(int target);

    // does not assume BST, target can be at left or right
    void deleteItem(int target);

    void inorder(function<void(int)> fptr);

    void preorder(function<void(int)> fptr);

    void postorder(function<void(int)> fptr);

    void inorder(function<void(TreeNode *)> fptr);

    void preorder(function<void(TreeNode *)> fptr);

    void postorder(function<void(TreeNode *)> fptr);

    // lambda decides to continue or not, terminate recursion as soon as possible
    void preorder(TreeNode *r, function<bool(TreeNode *)> fptr, bool &pleasurx);

    // forward declare the Iterator
    class LevelIterator;

    LevelIterator begin() { return LevelIterator(this); }

    // End of TreeNode wrapped in Iterator type
    LevelIterator end() {
        auto it = LevelIterator(this);
        it.loc = it.elements.size();
        return it;
    }

    class LevelIterator : public iterator<forward_iterator_tag, TreeNode> {
        friend TreeNode;
    private:
        vector<TreeNode *> elements;
        int loc{0};
    public:

        LevelIterator(TreeNode *root) {
            if (!root) return;
            queue<TreeNode *> q;
            q.push(root);
            while (!q.empty()) {
                TreeNode *tp = q.front();
                q.pop();
                elements.push_back(tp);
                if (tp->left) q.push(tp->left);
                if (tp->right) q.push(tp->right);
            }
        }

        LevelIterator &operator=(const LevelIterator &it) {
            loc = it.loc;
            elements = it.elements;
            return *this;
        }

        // Prefix ++ overload
        LevelIterator &operator++() {
            if (loc >= elements.size())
                throw out_of_range("iterator prefix ++ called and no more items left in tree");
            ++loc;
            return *this;
        }

        // Prefix -- overload
        LevelIterator &operator--() {
            if (loc < 0)
                throw out_of_range("iterator prefix -- called beyond first item in tree");
            --loc;
            return *this;
        }

        // Postfix ++ overload
        LevelIterator operator++(int) {
            if (loc >= elements.size())
                throw out_of_range("iterator postfix ++ called and no more items left in tree");
            LevelIterator iterator = *this;
            ++*this;
            return iterator;
        }

        // Postfix -- overload
        LevelIterator operator--(int) {
            if (loc >= elements.size())
                throw out_of_range("iterator postfix  -- called beyond first item in tree");
            LevelIterator iterator = *this;
            --*this;
            return iterator;
        }

        // does NOT do a full proper equality check,
        bool operator==(const LevelIterator &iterator) {
            if (loc != iterator.loc)
                return false;
            if (elements.size() != iterator.elements.size())
                return false;
            for (int i = 0; i < elements.size(); ++i) {
                if (elements[i] != iterator.elements[i])
                    return false;
            }
            return true;
        }

        bool operator!=(const LevelIterator &iterator) {
            return !operator==(iterator);
        }

        TreeNode *operator*() {
            if (loc >= elements.size())
                throw out_of_range("iterator * called past end of tree");
            if (loc < 0)
                throw out_of_range("iterator * called before beginning  of tree");
            return elements[loc];
        }
    };
};

TreeNode::~TreeNode() {
    if (left)
        delete left;
    if (right)
        delete right;
}

TreeNode::TreeNode(int x) : val(x), left(NULL), right(NULL) {}

TreeNode::TreeNode(const vector<int> &v, int nullValue) {
    vector<int> v2(v);
    expandVectorToFull(v2, nullValue);
    vector2tree(v2);
    deleteItem(nullValue);
}

void TreeNode::expandVectorToFull(vector<int> &v, int nullValue) {
    if (v.empty()) return;
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] == nullValue) {
            // insert nullValue for children
            int left = i * 2 + 1;
            int right = i * 2 + 2;
            if (right < v.size()) {
                v.insert(v.begin() + left, nullValue);
                v.insert(v.begin() + right, nullValue);
            }
        }
    }
}

// assumes a complete tree, all levels full
// last level filled left to right
void TreeNode::vector2tree(const vector<int> &v) {
    if (v.empty()) return;
    queue<TreeNode *> parentQ;
    int counter = 1;
    left = right = nullptr;
    TreeNode *parent = this;
    parent->val = v[0];
    while (parent && counter < v.size()) {
        // left child and increase counter
        parent->left = new TreeNode(v[counter++]);
        // right child IFF still have items
        parent->right = counter < v.size() ? new TreeNode(v[counter++]) : nullptr;
        // left child is the next parent who will get children
        parentQ.push(parent->left);
        if (parent->right)
            parentQ.push(parent->right);
        parent = parentQ.front();
        parentQ.pop();
    }
}

vector<int> TreeNode::string2vector(string s) {
    const static string delimiter = ",";
    vector<int> v;
    int start = 0;
    // add an extra , to end
    string s2 = s + ",";
    cout << s2 << endl;
    int fin = s2.find(delimiter);
    while (fin != string::npos && fin > start) {
        string token = s2.substr(start, fin - start);
        if (token == "null")
            v.push_back(INT_MIN);
        else {
            v.push_back(stoi(token));
        }
        start = fin + 1;
        fin = s2.find(delimiter, start);
    }
    return v;
}

TreeNode::TreeNode(const string &s) : TreeNode(string2vector(s), INT_MIN) {

}

int TreeNode::depth() const {
    return 1 + max(left ? left->depth() : 0,
                   right ? right->depth() : 0);
}

bool TreeNode::isLeaf() const {
    return !left && !right;
}

// does not assume BST, target can be at left or right
TreeNode *TreeNode::findItem(int target) {
    if (val == target)
        return this;
    TreeNode *found = left ? left->findItem(target) : nullptr;
    if (found) return found;
    return right ? right->findItem(target) : nullptr;
}

// does not assume BST, target can be at left or right
void TreeNode::deleteItem(int target) {
    // cannot delete root node
    assert(target != val);
    queue<TreeNode *> todel;
    queue<TreeNode *> process;
    process.push(this);
    while (!process.empty()) {
        TreeNode *tp = process.front();
        process.pop();
        if (tp->left) {
            process.push(tp->left);
            if (tp->left->val == target) {
                todel.push(tp->left);
                tp->left = nullptr;
            }
        }
        if (tp->right) {
            process.push(tp->right);
            if (tp->right->val == target) {
                todel.push(tp->right);
                tp->right = nullptr;
            }
        }
    }
    while (!todel.empty()) {
        TreeNode *tp = todel.front();
        todel.pop();
        delete tp;
    }
}

void TreeNode::inorder(TreeNode *r, function<void(int)> fptr) {
    auto lam = [&fptr](TreeNode *tp) {
        fptr(tp->val);
    };
    inorder(r, lam);
}


void TreeNode::preorder(TreeNode *r, function<void(int)> fptr) {
    auto lam = [&fptr](TreeNode *tp) {
        fptr(tp->val);
    };
    preorder(r, lam);
}


void TreeNode::postorder(TreeNode *r, function<void(int)> fptr) {
    auto lam = [&fptr](TreeNode *tp) {
        fptr(tp->val);
    };
    postorder(r, lam);
}


void TreeNode::inorder(TreeNode *r, function<void(TreeNode *)> fptr) {
    if (!r) return;
    inorder(r->left, fptr);
    fptr(r);
    inorder(r->right, fptr);
}


void TreeNode::preorder(TreeNode *r, function<void(TreeNode *)> fptr) {
    if (!r) return;
    fptr(r);
    preorder(r->left, fptr);
    preorder(r->right, fptr);
}

// lambda decides to continue or not, terminate recursion as soon as possible
// lambda has captured the variable can_continue by by reference and modifies it
void TreeNode::preorder(TreeNode *r, function<bool(TreeNode *)> fptr, bool &can_continue) {
    if (!r) return;
    if (can_continue)
        fptr(r);
    if (can_continue)
        preorder(r->left, fptr);
    if (can_continue)
        preorder(r->left, fptr);

}


void TreeNode::postorder(TreeNode *r, function<void(TreeNode *)> fptr) {
    if (!r) return;
    postorder(r->left, fptr);
    postorder(r->right, fptr);
    fptr(r);
}

void TreeNode::inorder(function<void(int)> fptr) {
    inorder(this, fptr);
}

void TreeNode::preorder(function<void(int)> fptr) {
    preorder(this, fptr);
}

void TreeNode::postorder(function<void(int)> fptr) {
    postorder(this, fptr);
}

void TreeNode::inorder(function<void(TreeNode *)> fptr) {
    inorder(this, fptr);
}

void TreeNode::preorder(function<void(TreeNode *)> fptr) {
    preorder(this, fptr);
}

void TreeNode::postorder(function<void(TreeNode *)> fptr) {
    postorder(this, fptr);
}


/**
 * print tree sideways with root on left
                6
            2
                5
        0
                4
            1
                3
 */
ostream &printSideways(ostream &os, const TreeNode *curr, int level = 0) {
    const static char sp = ' ';
    const static int readabilitySpaces = 4;
    if (!curr)
        return os;
    printSideways(os, curr->right, ++level);
    os << setfill(sp) << setw(level * readabilitySpaces) << sp;
    os << curr->val << endl;
    printSideways(os, curr->left, level);
    return os;
}

/**
 * print tree level by level using "null" for any null values
[0,1,2,3,4,5,6]
 */
ostream &printSquare(ostream &os, const TreeNode *curr) {
    if (!curr)
        return os << "[]";
    queue<const TreeNode *> q;
    bool startedPrinting = false;
    os << "[";
    q.push(curr);
    int nodesAtLevel = 1;
    bool nodesAtNextLevel = true;
    while (!q.empty() && nodesAtNextLevel) {
        int nodes = 0;
        nodesAtNextLevel = false;
        while (nodes < nodesAtLevel) {
            const TreeNode *tp = q.front();
            q.pop();
            if (startedPrinting)
                os << ",";
            else
                startedPrinting = true;
            if (tp) {
                os << tp->val;
                nodesAtNextLevel = nodesAtNextLevel || tp->left || tp->right;
                q.push(tp->left);
                q.push(tp->right);
            } else {
                os << "null";
                q.push(nullptr);
                q.push(nullptr);
            }
            ++nodes;
        }
        nodesAtLevel *= 2;
    }
    os << "]";
    return os;
}

ostream &centeredPrint(ostream &os, int space,
                       const string &str, char fillchar = ' ') {
    auto strL = static_cast<int>(str.length());
    int extra = (space - strL) / 2;
    if (extra > 0) {
        os << setfill(fillchar) << setw(extra + strL) << str;
        os << setfill(fillchar) << setw(space - extra - strL) << fillchar;
    } else {
        os << setfill(fillchar) << setw(space) << str;
    }
    return os;
}

/**
 * print tree with the root at top
 *
      _____0______
   __1___      __2___
  3     4     5     6
 *
 */
ostream &printTreeLevel(ostream &os,
                        queue<const TreeNode *> &q,
                        int width,
                        int depth,
                        int maxDepth) {
    const static char sp = ' ';
    const static char und = '_';
    int nodes = 0;
    int maxN = pow(2, depth - 1);
    int spaceForEachItem = width * pow(2, maxDepth - 1) / maxN;
    string
            bigspace = string(static_cast<unsigned long>(spaceForEachItem / 4), sp);
    while (nodes++ < maxN) {
        const TreeNode *tp = q.front();
        TreeNode *tpL = nullptr;
        TreeNode *tpR = nullptr;
        q.pop();
        string label = "N";
        if (tp) {
            label = to_string(tp->val);
            tpL = tp->left;
            tpR = tp->right;
        }
        char filler = depth == maxDepth ? sp : und;
        if (depth == maxDepth) {
            centeredPrint(os, spaceForEachItem, label, filler);
        } else {
            os << bigspace;
            centeredPrint(os, spaceForEachItem / 2, label, filler);
            os << bigspace;
            q.push(tpL);
            q.push(tpR);
        }
    }
    os << endl;
    return os;
}

ostream &printVertical(ostream &os, const TreeNode *curr) {
    const static int width = 6;  // must be even
    if (!curr)
        return os << "[__]";
    // figure out the maximum depth which determines how wide the tree is
    int maxDepth = curr->depth();
    queue<const TreeNode *> q;
    q.push(curr);
    for (int depth = 1; depth <= maxDepth; ++depth) {
        printTreeLevel(os, q, width, depth, maxDepth);
    }
    return os;
}

ostream &printSingle(ostream &os, const TreeNode *curr) {
    if (!curr)
        return os << "<_>";
    return os << "<" << curr->val << ">";
}

ostream &operator<<(ostream &os, const TreeNode *tr) {
//    printSingle(os, tr);
//    printSquare(os, tr);
//    os << endl;
    printVertical(os, tr);
    os << endl;
//    printSideways(os, tr);
//    os << endl;
    return os;
}

ostream &operator<<(ostream &os, const TreeNode &tr) {
    return operator<<(os, &tr);
}

#endif //LEETPRACTICE_TREEUTILS_H
