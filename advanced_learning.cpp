/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.3.30
 *  Last modified: 2018.3.31
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

using namespace std;

/*
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
 */


int main(){
    const map<string, int> mp{{"zhang", 2}};
    cout << mp.size() << endl;
    int num = mp.at("zhang");
    cout << num << endl;
    cout << mp.size() << endl;

    return 0;
}