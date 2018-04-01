/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.3.31
 *  Last modified: 2018.3.31
 *
 *  Function:
 *      Sorting Algorithms
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>
#include <list>
#include <array>
#include <deque>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <forward_list>
#include <initializer_list>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
 * swap two elements in the array
 * param i: pos of the first element
 * param j: pos of the second element
 * param arr: reference of the vector
 * return: none
 */
void swap(int i, int j, vector<int> &arr) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/*
 * bubble sort(stable):
 *   optimize the algorithm by recording the last exchanged position
 *   elements above the last exchange position must be ordered
 *   time complexity: O(n^2)
 *   space complexity: O(1)
 * param arr: reference of the vector
 * return: none
 */
void bubble_sort(vector<int> &arr) {
    int sz = arr.size();   //use type int, if sz=0, sz-1>0 when using size_t
    for (int i = 0; i < sz - 1;) {
        int next = sz - 1; //record the last exchange position
        for (int j = sz - 1; j != i; --j) {
            if (arr[j] < arr[j - 1]) {
                swap(j - 1, j, arr);
                next = j;
            }
        }
        i = next;
    }
}

/*
 * quick sort(not stable):
 *  optimization_1: use insert sort when number of the elements is small
 *  optimization_2: choose median the three elements as pivot
 *  note: consider the situation that all elements were divided into a single part
 *  time complexity: average-O(nlogn), worst-O(n^2)
 *  space complexity: O(logn) - space for recursive operation
 * param i: pos of the left-most element
 * param j: pos of the right-most element
 * return: none
 */
void quick_sort_child(int i, int j, vector<int> &arr) {
    //maybe shoud replace this code block with inserting sort
    if (j - i < 2) {
        if (i < j && arr[i] > arr[j])
            swap(i, j, arr);
        return;
    }

    //find the pivot element from three elements
    int mid = (i + j) / 2;
    if (arr[mid] < arr[i])
        swap(i, mid, arr);
    if (arr[j] < arr[i])
        swap(i, j, arr);
    if (arr[j] < arr[mid])
        swap(mid, j, arr);
    int pivot = arr[mid];

    //partition elements
    int left = i, right = j;
    while (left < right) {
        while (arr[left] < pivot) left++;
        while (arr[right] >= pivot) right--;
        if (left < right)
            swap(left, right, arr);
    }

    if (i == left)
        quick_sort_child(left + 1, j, arr); //avoid endless loop
    else if (j == right)
        quick_sort_child(i, right - 1, arr);//avoid endless loop
    else {
        quick_sort_child(i, left - 1, arr);
        quick_sort_child(left, j, arr);
    }
}

void quick_sort(vector<int> &arr) {
    if (arr.size() < 2) return;
    quick_sort_child(0, arr.size() - 1, arr);
}

/*
 * insert sort(stable):
 *  optimize the algorithm by using binary search to find the position to insert element
 *  time complexity: average - O(nlogn) -- the original version is O(n^2), worst - O(n^2)
 *  space complexity: O(1)
 *  param arr: reference of the vector
 *  return: none
 */
void insert_sort(vector<int> &arr) {
    int sz = arr.size();
    for (int i = 1; i < sz; ++i)
        if (arr[i] < arr[i - 1]) {
            //binary search, pay attention to the detail!
            int tmp = arr[i];
            int low = 0, high = i - 1, mid;
            while (low <= high) //must be operator <=
            {
                mid = (low + high) / 2;
                if (tmp < arr[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }

            for (int j = i; j != low; --j)
                arr[j] = arr[j - 1];
            arr[low] = tmp;
        }
}

/*
 * shell_sort(not stable):
 *  time complexity: O(nlogn) - O(n^2)
 *  space complexity: O(1)
 *  param arr: reference of the vector
 *  return: none
 */
void shell_sort(vector<int> &arr) {
    int sz = arr.size();
    for (int d = sz / 2; d >= 1; d /= 2) // gap /= 2
    {
        for (int i = d; i != sz; ++i) {
            int j = i, tmp = arr[i];
            for (; j >= d && tmp < arr[j - d]; j -= d)
                arr[j] = arr[j - d];
            arr[j] = tmp;
        }
    }
}

/*
 * selection sort:
 *  time complexity: O(n^2)
 *  space complexity: O(1)
 *  param arr: reference of the vector
 *  return: none
 */
void selection_sort(vector<int> &arr) {
    int sz = arr.size();
    for (int i = 0; i != sz; ++i) {
        int min_pos = i;
        int min_value = arr[i];
        for (int j = i + 1; j != sz; ++j)
            if (arr[j] < min_value) {
                min_pos = j;
                min_value = arr[j];
            }
        if (min_pos != i) {
            arr[min_pos] = arr[i];
            arr[i] = min_value;
        }
    }
}

/*
 * heap sort(not stable):
 *  build max-heap to swap the head and tail elements until all elements be ordered
 *  time complexity: O(nlogn)
 *  space complexity: O(n) -- operating on the original vector can be O(1)
 *  param arr: reference of the vector
 *  return none
 */
void push_down(int pos, int sz, vector<int> &arr) {
    int tmp = arr[pos];
    int next = 2 * pos - 1;
    while (next <= sz) {
        if (next + 1 <= sz && arr[next + 1] > arr[next])
            next += 1;
        if (arr[next] <= tmp) break;
        arr[pos] = arr[next];
        pos = next;
        next = 2 * next - 1;
    }
    arr[pos] = tmp;
}

void heap_sort(vector<int> &arr) {
    int sz = arr.size();

    //build max-heap
    vector<int> heap(1);
    for (const auto &item: arr)
        heap.push_back(item);
    for (int i = sz / 2; i >= 1; --i)
        push_down(i, sz, heap);

    //swap head and tail elements, adjust the heap
    for (int i = sz; i >= 2; --i) {
        swap(1, i, heap);
        push_down(1, i - 1, heap);
    }

    //reverse and copy to the original vector
    for (int i = 1; i != sz + 1; ++i)
        arr[i - 1] = heap[i];
}

/*
 * merge sort(stable):
 *  from bottm to the up, not recursively
 * time complexity: O(nlogn)
 * space complexity: O(n)
 */

/*
 * merge two ordered squences
 * param start: left-most subscript of the first sequence
 * param mid: right-most subscript of the first sequence
 * param end: right-most subscript of the second sequence
 * param arr_A: reference of the original vector
 * param arr_B: merge two sequence into this vector
 * return: none
 */
void merge(int start, int mid, int end, vector<int> &arr_A, vector<int> &arr_B) {
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end)
        arr_B[k++] = arr_A[i] <= arr_A[j] ? arr_A[i++] : arr_A[j++];
    while (i <= mid)
        arr_B[k++] = arr_A[i++];
    while (j <= end)
        arr_B[k++] = arr_A[j++];
}

/*
 * merge every two h-length sequences in the original vector
 * param h: expected length of each sequence
 * param arr_A: reference of the original vector
 * param arr_B: tmp container to save the merged sequence
 * return: none
 */
void merge_pass(int h, vector<int> &arr_A, vector<int> &arr_B) {
    int i = 0;
    for (; i + 2 * h - 1 < arr_A.size(); i += 2 * h)
        merge(i, i + h - 1, i + 2 * h - 1, arr_A, arr_B);
    if (i + h - 1 < arr_A.size() - 1) //the left elements is more than one squence but less than two sequences
        merge(i, i + h - 1, arr_A.size() - 1, arr_A, arr_B);
    else                              //the left elements is less than one sequence
        for (; i != arr_A.size(); ++i)
            arr_B[i] = arr_A[i];
}

void merge_sort_nrc(vector<int> &arr) {
    int h = 1;
    vector<int> dev(arr.size());
    while (h < arr.size()) {
        merge_pass(h, arr, dev); //merge elements from arr to dev
        h *= 2;
        merge_pass(h, dev, arr); //merge elements from dev to arr
        h *= 2;
    }
}

/*
 * merge sort:
 *  from top to the bottm, recursively
 *  time complexity: O(nlogn)
 *  space complexity: O(n)
 */

/*
 * split sequence and merge them recursively
 * param low: left-most subscript of the total sequence
 * param high: right-most subscript of the total sequence
 * param arr_A: reference of the original vector
 * param arr_B: tmp vector to help merge sequence
 * return: none
 */
void merge_sort_child(int low, int high, vector<int> &arr_A, vector<int> &arr_B) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort_child(low, mid, arr_A, arr_B);
        merge_sort_child(mid + 1, high, arr_A, arr_B);
        merge(low, mid, high, arr_A, arr_B); //merge two sequences
        for (int i = low; i <= high; ++i) //copy back to the original vector
            arr_A[i] = arr_B[i];
    }
}

void merge_sort_rc(vector<int> &arr) {
    vector<int> dev(arr.size());
    merge_sort_child(0, arr.size() - 1, arr, dev);
}

/*
 * counting sort(stable):
 *  time complexity: O(k + n)
 *  space complexity: O(k + n)
 *  param arr: reference of the vector
 *  return: none
 */
void counting_sort(vector<int> &arr) {
    if (arr.empty()) return;
    int sz = arr.size();

    //find the maximum element;
    int max = arr[0];
    for (const auto &item: arr)
        if (item > max)
            max = item;

    //counting number
    vector<int> count(max + 1, 0);
    vector<int> dev(sz + 1, 0);
    for (const auto &item: arr)
        count[item]++;
    for (int i = 1; i <= max; ++i)
        count[i] += count[i - 1];

    //copy elements to the correct position
    for (int i = sz - 1; i >= 0; --i) //to keep stability at reversed order
        dev[count[arr[i]]--] = arr[i];
    for (int i = 0; i != sz; ++i)
        arr[i] = dev[i + 1];
}

/*
 * radix sort(stable):
 *  time complexity: O(d*(n+r))
 *  space complexity: O(n+r)
 *  return: none
 */

/*
 * extract value at given postion
 * param value: the element
 * param pos: position of the value to extract
 * return: none
 */
int radix(int value, int pos) {
    auto power = static_cast<int>(pow(10, pos - 1));
    return value / power % 10;
}

/*
 * radix sort:
 *  using buckect allocation as the stable sort algorithm
 *  param arr: reference of the original vector
 *  param width: max bit width of all elements
 *  return: none
 */
void radix_sort_child_1(vector<int> &arr, int width) {
    queue<int> A;
    for (const auto &elem: arr)
        A.push(elem);

    //using bucket allocation as the statble sort algorithm
    for (int pass = 1; pass <= width; ++pass) {
        //allocate elements into buckets
        vector<queue<int>> buckets(10);
        while (!A.empty()) {
            int elem = A.front();
            A.pop();
            int r = radix(elem, pass);
            buckets[r].push(elem);
        }

        //collect elements from buckets
        for (auto &bucket: buckets)
            while (!bucket.empty()) {
                A.push(bucket.front());
                bucket.pop();
            }
    }

    for (int i = 0; i != arr.size(); ++i) {
        arr[i] = A.front();
        A.pop();
    }
}

void radix_sort_1(vector<int> &arr) {
    radix_sort_child_1(arr, 2);
}

/*
 * radix sort:
 *  using counting sort as the stable sort algorithm
 *  param arr: reference of the original vector
 *  param width: max bit width of all elements
 *  return: none
 */
void radix_sort_child_2(vector<int> &arr, int width) {
    if (arr.empty()) return;
    int sz = arr.size();

    //using counting sort as the stable sort algorithm
    for (int pass = 1; pass <= width; ++pass) {
        vector<int> comp(sz, 0);
        for (int i = 0; i != sz; ++i)
            comp[i] = radix(arr[i], pass);

        //find the maximum element
        int max = comp[0];
        for (const auto &elem: comp)
            if (elem > max)
                max = elem;

        //counting number
        vector<int> dev(sz + 1, 0);
        vector<int> count(max + 1, 0);
        for (const auto &elem: comp)
            count[elem]++;
        for (int i = 1; i <= max; ++i)
            count[i] += count[i - 1];

        //copy elements to correct position
        for (int i = sz - 1; i >= 0; --i)
            dev[count[comp[i]]--] = arr[i];
        for (int i = 0; i != sz; ++i)
            arr[i] = dev[i + 1];
    }
}

void radix_sort_2(vector<int> &arr) {
    radix_sort_child_2(arr, 2);
}

/*
 * bucket sort(stable):
 *  time complexity: O(n)
 *  space complexity: O(n)
 *  param arr: reference of the original vector
 *  return: none
 */
void bucket_sort(vector<int> &arr) {
    //allocate elements into buckets by certain rule
    vector<vector<int>> buckets(20);
    for (const auto &elem: arr)
        buckets[elem / 5].push_back(elem);

    //do insert_sort for each bucket
    for (auto &bucket: buckets)
        insert_sort(bucket);

    //collect elements from buckets
    arr.clear();
    for (const auto &bucket: buckets)
        for (const auto &elem: bucket)
            arr.push_back(elem);
}

/*
 * test function for sorting alforithms
 * param sort: pointer of the sort function
 */
using TF = void(vector<int> &);

void test_sort(TF *sort) {
    vector<int> test_a = {};
    vector<int> test_b = {1};
    vector<int> test_c = {2, 1};
    vector<int> test_d = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> test_e = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> test_f = {4, 8, 45, 1, 7, 3, 49, 36, 4, 7, 3};
    vector<vector<int>> test{test_a, test_b, test_c, test_d, test_e, test_f};

    for (auto &arr: test) {
        sort(arr);
        for (const auto &item: arr)
            cout << item << " ";
        cout << endl;
    }
}

int main() {
//    test_sort(bubble_sort);
//    test_sort(quick_sort);
//    test_sort(insert_sort);
//    test_sort(shell_sort);
//    test_sort(selection_sort);
//    test_sort(heap_sort);
//    test_sort(merge_sort_nrc);
//    test_sort(merge_sort_rc);
//    test_sort(counting_sort);
//    test_sort(radix_sort_1);
//    test_sort(radix_sort_2);
//    test_sort(bucket_sort);

    return 0;
}
