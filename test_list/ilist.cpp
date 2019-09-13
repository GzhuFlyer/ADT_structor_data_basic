//使用initialize_list (C++特性)

#include<iostream>
#include<initializer_list>

double sum(std::initializer_list<double> i1);
double average(const std::initializer_list<double> & ri1);

int main()
{
    using std::cout;
    cout << "List 1: sum " << sum({2,3,4})
         << ", ave = " << average({2,3,4}) << '\n';
    std::initializer_list<double> d1 = {1.1,2.2,3.3,4.4,5.5};
    cout << "List 2: sum = " << sum(d1)
         << ", ave = " << average(d1) << "\n";
    d1 = {16.0, 25.0, 36.0, 40.0, 64.0};
    cout << "List 3: sum = " << sum(d1)
         << ", ave = " << average(d1) << "\n";
    return 0;
}

double sum (std::initializer_list<double> i1)
{
    double tot = 0;
    for(auto p = i1.begin(); p != i1.end(); p++)
        tot += *p;
    return tot;
}

double average(const std::initializer_list<double> & ri1)
{
    double tot = 0;
    int n = ri1.size();
    double ave = 0.0;
    if(n > 0)
    {
        for(auto p = ri1.begin(); p != ri1.end(); p++)
            tot += *p;
        ave = tot / n;
    }
    return ave;
}