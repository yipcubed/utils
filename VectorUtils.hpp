

#ifndef LEETPRACTICE_VECTORUTILS_H
#define LEETPRACTICE_VECTORUTILS_H

#include <ostream>
#include <tuple>
#include <vector>

using namespace std;

template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  if (v.empty())
    return os << "[]";
  auto it = v.cbegin();
  os << "[" << *it++;
  while (it != v.cend())
    os << "," << *it++;
  os << "]";
  return os;
}

template <class T>
ostream &operator<<(ostream &os, const unordered_set<T> &mp) {
  if (mp.empty())
    return os << "[]";
  auto it = mp.cbegin();
  os << "[" << *it;
  ++it;
  while (it != mp.cend()) {
    os << "," << *it;
    ++it;
  }
  os << "]";
  return os;
}

template <class K, class L>
ostream &operator<<(ostream &os, const map<K, L> &mp) {
  if (mp.empty())
    return os << "[]";
  auto it = mp.cbegin();
  os << "[";
  os << "[" << it->first << "," << it->second << "]";
  ++it;
  while (it != mp.cend()) {
    os << ",[" << it->first << "," << it->second << "]";
    ++it;
  }
  os << "]";
  return os;
}

template <class K, class L>
ostream &operator<<(ostream &os, const unordered_map<K, L> &mp) {
  if (mp.empty())
    return os << "[]";
  auto it = mp.cbegin();
  os << "[";
  os << "[" << it->first << "," << it->second << "]";
  ++it;
  while (it != mp.cend()) {
    os << ",[" << it->first << "," << it->second << "]";
    ++it;
  }
  os << "]";
  return os;
}

template <class K, class L>
ostream &operator<<(ostream &os, const pair<K, L> &p) {
  return os << "[" << p.first << "," << p.second << "]";
}

template <class K, class L, class M>
ostream &operator<<(ostream &os, const tuple<K, L, M> &v) {
  return os << "[" << get<0>(v) << "," << get<1>(v) << "," << get<2>(v) << "]";
}

template <class K, class L, class M, class O>
ostream &operator<<(ostream &os, const tuple<K, L, M, O> &v) {
  return os << "[" << get<0>(v) << "," << get<1>(v) << "," << get<2>(v) << ","
            << get<3>(v) << "]";
}

#endif // LEETPRACTICE_VECTORUTILS_H
