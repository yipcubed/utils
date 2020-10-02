//
// Created by Yip on 7/7/19.
//

#ifndef SAMPLE_BINARYSEARCH_H
#define SAMPLE_BINARYSEARCH_H

// lo and hi are indexes of the array numbers
int binarySearch(vector<int> &numbers, int target, int lo, int hi) {
    if (lo > hi || lo < 0 || hi >= numbers.size() ||
        target < numbers[lo] || target > numbers[hi])
        return -1;
    int mid = lo + (hi - lo) / 2;
    if (target == numbers[mid])
        return mid;
    else if (target < numbers[mid])
        return binarySearch(numbers, target, lo, mid - 1);
    else
        return binarySearch(numbers, target, mid + 1, hi);
}

#endif //SAMPLE_BINARYSEARCH_H
