

#ifndef LEETPRACTICE_LISTNODE_H
#define LEETPRACTICE_LISTNODE_H

#include <vector>

//#include "VectorUtils.hpp"
//#include "PrintUtils.hpp"

using namespace std;

class ListNode {
private:
    static vector<int> string2vector(string s);
public:
    int val;
    ListNode *next{nullptr};

    ListNode(int x);

    ListNode(vector<int> v);
    ListNode(string s);
};

ListNode::ListNode(int x) : val(x), next(nullptr) {}

ListNode::ListNode(vector<int> v) {
    assert(!v.empty());
    auto it = v.cbegin();
    val = *it++;
    next = nullptr;
    ListNode *curr = this;
    while (it != v.cend()) {
        curr->next = new ListNode(*it);
        curr = curr->next;
        it++;
    }
}

ListNode::ListNode(string s) : ListNode(string2vector(s)) {
}

vector<int> ListNode::string2vector(string s) {
    const static string delimiter = ",";
    vector<int> v;
    int start = 0;
    // add an extra , to end
    string s2 = s + ",";
    int fin = s2.find(delimiter);
    while (fin != string::npos && fin > start) {
        string token = s2.substr(start, fin - start);
        v.push_back(stoi(token));
        start = fin + 1;
        fin = s2.find(delimiter, start);
    }
    return v;
}

ostream &operator<<(ostream &os, const ListNode *tr) {
    os << "[";
    if (tr) {
        os << tr->val;
        tr = tr->next;
    }

    while (tr) {
        os << "->" << tr->val;
        tr = tr->next;
    }
    return os << "]";;
}

ostream &operator<<(ostream &os, const ListNode &tr) {
    return operator<<(os, &tr);
}

#endif //LEETPRACTICE_LISTNODE_H
