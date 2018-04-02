/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.2
 *  Last modified: 2018.4.2
 *
 *  Function:
 *      to get the LCS of two sequences
 */

#include <iostream>
#include <fstream>
#include <sstream>

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
using TArray = vector<vector<int>>;

/**
 * extract the LCS
 * @param Directions: record from computed matrix
 * @param X: the first sequence
 * @param seq: vector to save the LCS
 * @param i
 * @param j
 */
void extract_LCS(const TArray &Directions, const vector<int> &X,
                 vector<int> &seq, int i, int j) {
    if (i == 0 || j == 0)
        return;

    if (Directions[i][j] == 0) {
        extract_LCS(Directions, X, seq, i - 1, j - 1);
        seq.push_back(X[i-1]);
    } else if (Directions[i][j] == 1)
        extract_LCS(Directions, X, seq, i - 1, j);
    else
        extract_LCS(Directions, X, seq, i, j - 1);
}

/**
 * to get the LCS of two sequences
 * @param X: the first sequence
 * @param Y: the second sequence
 * @return: pair<seq, length>
 */
pair<vector<int>, int> LCS(const vector<int> &X, const vector<int> &Y) {
    size_t x_length = X.size();
    size_t y_length = Y.size();
    TArray Length(x_length+1, vector<int>(y_length+1, 0));
    TArray Directions(x_length+1, vector<int>(y_length+1, 0));

    for (int i = 1; i <= x_length; ++i)
        for (int j = 1; j <= y_length; ++j)
            if (X[i-1] == Y[j-1]) {
                Length[i][j] = Length[i - 1][j - 1] + 1;
                Directions[i][j] = 0;
            } else if (Length[i - 1][j] >= Length[i][j - 1]) {
                Length[i][j] = Length[i - 1][j];
                Directions[i][j] = 1;
            } else {
                Length[i][j] = Length[i][j - 1];
                Directions[i][j] = 2;
            }

    vector<int> seq;
    extract_LCS(Directions, X, seq, x_length, y_length);
    return make_pair(seq, Length[x_length][y_length]);
}

int main() {
    int elem;
    vector<int> X, Y;
    cout << "Please input sequence X:";
    while (cin >> elem && elem != 0)
        X.push_back(elem);

    cout << "Please input sequence Y:";
    while (cin >> elem && elem != 0)
        Y.push_back(elem);

    auto res = LCS(X, Y);
    cout << "The length of LCS is " << res.second << ":";
    for (const auto &elem: res.first)
        cout << elem << " ";
    cout << endl;

    return 0;
}

/*
 2 4 3 1 2 1 0
 1 2 3 2 4 1 2 0
 */