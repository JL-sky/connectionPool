#ifndef PUBLIC_H
#define PUBLIC_H
#include<iostream>
#include<string>
using namespace std;

#define LOG(str)\
    cout<<__FILE__<<":"<<__LINE__<<":"<<__TIMESTAMP__<<":"<<str<<endl;
#endif