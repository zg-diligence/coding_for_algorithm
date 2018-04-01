/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.3.28
 *  Last modified: 2018.3.30
 *
 *  Function:
 *     C++ Basic Knowledge
 */

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cctype>
#include <initializer_list>
#include "Sales_data.h"

using namespace std;

/*
 * 1.执行浮点运算一般选用double,因为float通常精度不够而且双精度浮点数和单精度浮点数的计算代价相差无几.
 *
 * 2.给一个无符号类型赋值超出其表示范围时,结果是初始值对无符号类型表示数值总数取模后的余数.unsigned char = -1 ==> 255
 *
 * 3.如果使用列表初始化且初始值存在丢失信息的风险,则编译器将报错.int a{2.35}
 *
 * 4.定义在任何函数体之外的变量被初始化为0,定义在函数体内部的内置类型变量不被初始化.
 *
 * 5.如果想声明一个变量而非定义它,就在变量名前添加关键字extern,而且不要显示初始化变量,否则在函数体内部会报错,在函数体外部等价于定义一个新的变量.声明可以有多个,但是定义只能有一个.
 *
 * 6.嵌套作用域时候,局部作用域中的变量会自动覆盖全局作用域中的变量,可用::variable_name显式声明使用全局变量.
 *
 * 7.引用
 *  引用并非对象,它是已经存在对象的一个别名,所以不存在引用的引用.
 *  引用的引用实质上是绑定前一个引用对应的对象,即一个对象可以有多个引用与之绑定.
 *  指针是一个对象,可以先后指向不同的对象;而引用不是一个对象,始终只能指向一个对象;可以定义指针的引用,但不可以定义引用的指针.
 *
 * 8.const
 *  不可建立常量对象的非常量引用,常量或非常量的常量引用不能改变对象的值
 *  不可建立常量对象的普通指针,常量或非常量的指向常量的指针不能改变指向对象的值
 *  指向常量的指针or引用,其对象既可以是常量也可以是变量
 *  区分:常量引用|常量指针|指向常量的指针
 *
 * 9.auto vs decltype
 *
 * 10.string
 *  size_type 是一个无符号类型,应避免与int一起运算
 *  string与字符串字面值混在一条语句中使用时,必须确保加法运算符两侧的运算对象至少有一个是string.
 *  diffenrence_type 迭代器之间的距离,有符号整数
 *  ptrdiff_t 指针之间的距离,有符号整数
 *
 * 11.int (*parray)[10] = &arr; //parray指向一个含有10个整数的数组
 *    int (&arrRef)[10] = arr;  //arrRef引用一个含有10个整数的数组
 *    auto ia(arr); //ia是一个指针
 *    decltype(arr) //得到一个数组,数组大小和arr一样
 *    内置数组的下表可以是负整数,标准库数组则必须为非负整数
 *
 * 12.取余符号 m % n 符号和m相同
 *
 * 13.优先级
 *  赋值运算符 < 关系运算符       a = b != c
 *  解引用运算符　< 后置递增运算符 *p++
 *  解引用运算符 < 点运算符       *p.size()
 *  在输出表达式中使用条件运算符时记得用括号,条件运算符优先级很低
 *
 * 14.箭头运算符|点运算符
 *  箭头运算符作用于一个指针类型的运算对象得到的是一个左值
 *  点运算符分两种情况,得到左值/右值取决与成员所属的对象为左值/右值
 *
 * 15.sizeof运算符
 *  sizeof(arr) 返回数组所占总内存空间
 *  cout << sizeof(vector<int>) << endl; //24
 *  cout << sizeof(string) << endl;      //32
 *  cout << sizeof("abc") << endl;       //4
 *  cout << sizeof(a) << endl;           //24
 *  cout << a.size() << endl;            //7
 *
 * 16.类型转换
 *  隐式转换:数组转换为指针 decltype关键字的参数|取地址运算符|sizeof|typeid这几个不会转换成指针
 *  显示转换:static_cast|const_cast(只能改变运算对象底层的const)|reinterpret_cast|dynamic_cast
 *
 * 17.switch-case
 *  case标签必须是整数或者常量表达式(int/char)
 *  switch内部各个标签下的语句在同一作用域内,匹配到一个标签之后就开始执行,而不再检查后面的标签,所以记得用break
 *
 * 18.数组作为函数参数
 *  void print(int (*matrix)[10], int row_size);
 *  void print(int matrix[][], int row_size); //等价定义
 *
 * 19.可变形参 initializer_list
 *  initializer_list 必须为同一数据类型,且均为常量
 *
 * 20.函数重载
 *  重载函数必须在形参数量或形参类型上有所不同,不允许除了返回类型之外其他所有的元素都相同
 *  底层const可以重载,顶层const则不能视为重载
 *  在不同的作用域中无法重载函数,内层定义会隐藏外层的定义,名字查找发生在类型检查之前
 *
 * 21.默认实参
 *  一旦某个形参被赋予默认值,它后面所有的形参都必须具有默认值
 *  默认实参声明可以有多次,但每次只能为之前没有默认值的形参添加默认实参,且其右边的形参必须均有默认值
 *  局部变量不能作为默认实参
 *
 * 22.decltype作用于函数或者数组均不会发生指针转换,如果需要返回指针必须显示声明为指针类型
 *    函数返回值不能为数组或函数类型,但是可以返回数组指针或函数指针
 *
 * 23.class/struct
 *  类内部定义的成员函数默认为内联函数,这样的话能够节省开销.
 *  类在声明之后定义之前是一个不完全函数,可以定义指向其的指针或引用,可以声明其作为参数或返回值类型的函数,但是不能创建对象
 *  类外定义的成员函数其返回类型出现在函数名之前,不属于类作用域内部,如果使用类内定义数据类型需要声明作用域
 *  类中定义的函数体在整个类可见之后才被处理,类中成员对所有成员函数可见
 *  如果成员是const|引用|属于某种未提供默认构造函数的类类型,必须通过构造函数初始值列表为这些成员提供初值
 *  类成员的初始化顺序与它们在类中出现的顺序一致
 *
 * 24.explicit关键字
 *  抑制构造函数的隐式转换,注意隐式转换只允许一步转换,且只有单参数构造函数才有可能发生隐式转换
 *  explicit声明的构造函数只能用于直接初始化
 *  explicit声明只能在类内部
 *
 * 25.类的静态成员
 *  静态成员函数不含this指针,不与任何对象绑定在一起,静态成员函数不能声明成const的
 *  即使一个常量静态数据成员在类内部被初始化了,通常情况下也应该在类的外部定义一下该成员
 *  静态数据成员可以是不完全类型,静态数据成员也可以作为默认实参,普通成员则不可以
 *  static声明只能在类内部,不可以在类外定义时重复声明
 */

/*
 * test for class Sales_data
 */
void run(){
    Sales_data total;
    if(read(cin, total)){
        Sales_data trans;
        while(read(cin, trans)){
            if(total.isbn() == trans.isbn()){
                total.combine(trans);
            }
            else {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    }
    else{
        cerr << "No data?" << endl;
    }
}


int main(int argc, char **argv){
    run();
    return 0;
}
