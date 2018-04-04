#ifndef ALGORITHMS_STRBLOB_H
#define ALGORITHMS_STRBLOB_H

/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.4
 *  Last modified: 2018.4.4
 *
 *  Function:
 *      example of dynamic memory
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

#include <memory>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

class StrBlob{
public:
    using size_type = vector<string>::size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size()const{return data->size();}
    bool empty()const{return data->empty();}

    void push_back(const string &s){data->push_back(s);}
    void pop_back();

    string& front();
    const string& front()const;
    string& back();
    const string& back()const;

private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg)const;
};

StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob!");
    data->pop_back();
}

string& StrBlob::front(){
    check(0, "front on empty StrBlob!");
    return data->front();
}

const string& StrBlob::front()const {
    check(0, "front on empty StrBlob!");
    return data->front();
}

string& StrBlob::back() {
    check(0, "back on empty StrBlob!");
    return data->back();
}

const string& StrBlob::back()const {
    check(0, "back on empty StrBlob!");
    return data->back();
}

void StrBlob::check(size_type i, const string &msg) const {
    if(i >= data->size())
        throw out_of_range(msg);
}

#endif //ALGORITHMS_STRBLOB_H
