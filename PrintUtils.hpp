//
// Created by Yip on 29/6/19.
//

#ifndef SAMPLE_PRINTUTILS_H
#define SAMPLE_PRINTUTILS_H

#include <iostream>

#include "VectorUtils.hpp"

using namespace std;

template <typename T> void printvar(const string &str, const T &t) {
  cout << str << " = " << t << " ";
}

#define PV(x)                                                                  \
  do {                                                                         \
    printvar(#x, (x));                                                         \
  } while (false)

#define PV1(x)                                                                 \
  do {                                                                         \
    PV(x);                                                                     \
    cout << endl;                                                              \
  } while (false)

#define PV2(x, y)                                                              \
  do {                                                                         \
    PV(x);                                                                     \
    PV(y);                                                                     \
    cout << endl;                                                              \
  } while (false)

#define PV3(x, y, z)                                                           \
  do {                                                                         \
    PV(x);                                                                     \
    PV(y);                                                                     \
    PV(z);                                                                     \
    cout << endl;                                                              \
  } while (false)

#define PV4(x, y, z, w)                                                        \
  do {                                                                         \
    PV(x);                                                                     \
    PV(y);                                                                     \
    PV(z);                                                                     \
    PV(w);                                                                     \
    cout << endl;                                                              \
  } while (false)

#endif // SAMPLE_PRINTUTILS_H
