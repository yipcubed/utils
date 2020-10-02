//
// Created by Yip on 7/7/19.
//

#ifndef SAMPLE_HEAPUTILS_H
#define SAMPLE_HEAPUTILS_H

class Heap {
public:
    vector<int> arr;
    function<bool(int, int)> comp;

    explicit Heap(vector<int> arr, function<bool(int, int)> comp = greater<int>()) :
            arr{arr}, comp{comp} {
        build();
    }

    int getRoot() {
        return arr[0];
    }

    int getDeleteRoot() {
        int top = arr[0];
        deleteRoot();
        return top;
    }

private:
    // Time complexity for Building a Binary Heap is O(n).
    void heapify(int i) {
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < arr.size() && comp(arr[l],arr[largest]))
            largest = l;

        // If right child is larger than largest so far
        if (r < arr.size() && comp(arr[r],arr[largest]))
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(largest);
        }
    }


    void deleteRoot() {
        // Get the last element
        int lastElement = arr[arr.size() - 1];

        // Replace root with first element
        arr[0] = lastElement;

        // Decrease size of heap by 1
        arr.pop_back();

        // heapify the root node
        heapify(0);
    }


    void build() {
        for (int i = arr.size() / 2; i >= 0; --i) {
            heapify(i);
        }
    }

};

#endif //SAMPLE_HEAPUTILS_H
