/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.3.30
 *  Last modified: 2018.4.3
 *
 *  Function:
 *      Advanced knowledge
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

#include <numeric>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

template<typename T>
void print_seq(const T &seq, const char *sep = " ", const string &end = "\n") {
    copy(seq.cbegin(), seq.cend(), ostream_iterator<typename T::value_type>(cout, sep));
    cout << end;
}

/*
 * 顺序容器和关联容器 ------------------------------------------------------------------------------------------------
 * 1.forward_list没有size操作,因为保存或计算其大小就会比手写链表多出额外的开销
 *
 * 2.接受一对迭代器的拷贝操作不要求拷贝前后的容器类型or元素类型相同,只要元素类型可以转换就行了,assign操作同理
 *
 * 3.swap操作
 *   除array外swap不对任何元素进行拷贝|删除|插入操作,可以保证在常数时间内完成,而array则要进行元素交换,时间与元素数目成正相关
 *   除string外指向容器的迭代器|引用|指针在swap操作之后都不会失效
 *
 * 4.插入或删除操作之后,尾后迭代器一般会失效(vector,deque,string),所以此类运算中不要保存尾后迭代器,而是反复调用end()
 *
 * 5.set和map的关键字类型都是const的
 *   set的迭代器是const的,因为set中的元素不允许改变
 *   map|multimap和set|multiset中元素是按照字典序存储的
 *   map下标访问,如果关键字不在map中,则对自动添加元素,值为默认值,所以下标运算符不能用于const map,可用at|find作为替代方案
 *   map|set插入一个关键字已经存在的元素,不会发生任何操作,map中关键字对应的值也不会发生变化
 *   自定义类型需要自定义比较操作,如 multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn), 其中compare是Sales_data的比较函数
 *
 * 6.无序容器使用一个哈希函数+关键字类型的==运算符来组织元素
 *   无序容器在存储上为一组桶,每个桶保存零个或者多个元素,无序容器的性能依赖与哈希函数的质量和桶的数量大小
 *   可利用hash模板和自定义==运算符自定义无序容器,C++ Primer P396
 *   无论在有序容器还是无序容器中,具有相同关键字的元素都是相邻存储的
 *
 * 泛型算法 ------------------------------------------------------------------------------------------------
 * 7.泛型算法
 *   算法不会改变容器的大小
 *   find|count|accumulate|equal|find_if|count_if
 *   fill|fill_n|replace|replace_copy
 *   sort|stable_sort|partition|stable_partition|unique|for_each
 *
 * 8.lambda表达式
 *   [capture list](parameter list) -> return type { function type }
 *   lambda不能有默认参数
 *   lambda表达式中忽略括号和参数列表等价于指定一个空参数列表
 *   如果lambda函数函数体包含任何单一return语句之外的内容,且未指定返回类型,则返回void
 *   捕获列表只用于局部非static变量,lambda可以直接使用局部static变量和它所在函数之外的声明的名字
 *   被捕获的变量的值实在lambda创建时拷贝,而不是调用时拷贝
 *   捕获元素的方式:值捕获|引用捕获|隐式捕获|混合隐式+显示捕获
 *   指定lambda返回类型之后,函数体中可以有多条语句
 *
 * 9.bind函数
 *   auto new_callable = bind(callable, arg_list);
 *   eg: auto g = bind(f, a, b, _2, c, _1);
 *       g(X, Y) <==> f(a, b, Y, c, X)
 *   bind函数可实现参数重排序|减少参数数目
 *   如果传引用参数, 则需要经过ref|cref进行转换
 *
 * 10.迭代器
 *   插入迭代器: back_inserter(seq)|front_inserter(seq)|inserter(seq, p)
 *   流迭代器: istream_iterator|ostream_iterator
 *   反向迭代器: rbegin()|rend()|crbegin()|crend()  iter.base()可反向
 *   移动迭代器: ...
 *
 * 11.特定容器的算法 list and forward_list
 *   优先使用成员函数版本的算法,通用版本性能低很多
 *   链表特有的操作会改变容器,通用版本算法不会改变容器
 */

/**
 * example for generic algorithms
 * @param words: vector of words
 * @param sz: threshold for length of string
 */
void elim_dups(vector<string> &words){
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elim_dups(words);
    auto isshorter = [](const string &a, const string &b) { return a.size() < b.size(); };
    stable_sort(words.begin(), words.end(), isshorter);
    auto wc = find_if(words.begin(), words.end(), [sz](const string &s) { return s.size() >= sz; });
    auto cnt = words.end() - wc;
    cout << cnt << " word" << (cnt > 1 ? "s" : "") << " of length " << sz << " or longer" << endl;
    for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
    cout << endl;
}

int main(){
    deque<int> vecs, new_nums;
    vector<int> nums{1,2,3,4,5,6,7,4,8};
    list<int> devs{1,2,3,4,5,6,7,4, 8, 9};
    auto res = find(nums.begin(), nums.end(), 4);
    auto cnt = count(nums.begin(), nums.end(), 4);
    auto sum = accumulate(nums.begin(), nums.end(), 0);
    auto eqs = equal(nums.begin(), nums.end(), devs.begin()); //if b includes a, also a == b

    fill(devs.begin(), devs.end(), 0);
    fill_n(devs.begin(), 5, 1);
    fill_n(back_inserter(vecs), 5, 1);
    replace(nums.begin(), nums.end(), 4, 8);
    replace_copy(nums.begin(), nums.end(), back_inserter(new_nums), 4, 8);

    //use of istream_iterator
    istringstream str_cin("the quick red fox jumps over the slow red turtle");
    istream_iterator<string> is(str_cin), eof;
    vector<string> words(is, eof);
//    elim_dups(words);
    biggies(words, 5);
    print_seq(words);

    return 0;
}