#ifndef ALGORITHMS_SALES_DATA_H
#define ALGORITHMS_SALES_DATA_H

#include <iostream>
#include <string>
using namespace std;


class Sales_data{
    friend istream& read(istream&, Sales_data&);
    friend ostream& print(ostream&, const Sales_data&);
    friend Sales_data add(const Sales_data&, const Sales_data&);

public:
    explicit Sales_data(const string &s=""):bookNo(s){}
    Sales_data(const string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(n*p){}
    explicit  Sales_data(istream &is);
    ~Sales_data()= default;

    string isbn()const{ return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price()const;

private:
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

istream& read(istream &is, Sales_data &item);

ostream& print(ostream &os, const Sales_data &item);

Sales_data add(const Sales_data&lhs, const Sales_data &rhs);

#endif //ALGORITHMS_SALES_DATA_H
