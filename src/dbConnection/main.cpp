#include<iostream>
#include<list>
#include"connection.hpp"
#include"connectionPool.hpp"
using namespace std;

const int dataNum=1000;//测试数据量

void connTest()
{
    for(int i=0;i<dataNum;i++)
    {
        Connection conn;
        char sql[1024]={0};
        sprintf(sql,
        "insert into user(name,age,sex) values('%s',%d,'%s')",
        "zhangsan",20,"male");
        conn.connect("127.0.0.1",3306,"root","123456","chat");
        conn.update(sql);
    }
}

void connPoolTest()
{   
    ConnectionPool* cp=ConnectionPool::getConnectionPool();
    for(int i=0;i<dataNum;i++)
    {
        shared_ptr<Connection> sp=cp->getConnection();
        char sql[1024]={0};
        sprintf(sql,
        "insert into user(name,age,sex) values('%s',%d,'%s')",
        "zhangsan",20,"male");
        sp->update(sql);
    }
}

//单线程服务器压力测试（不使用连接池）
void singleThreadConnTest()
{
    clock_t begin=clock();  
    connTest();
    clock_t end=clock();
    double duration = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

//单线程连接池压力测试
void singleThreadConnPoolTest()
{
    clock_t begin=clock();
    connPoolTest();
    clock_t end=clock();
    double duration = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

//多线程连接测试（不使用连接池）
void mutiThreadConnection()
{
    clock_t begin=clock();

    list<thread> tl;
    for(int i=0;i<4;i++)
    {
        tl.push_back(thread(connTest));
    }

    for(auto& tt:tl)
    {
        tt.join();
    }

    clock_t end=clock();
    double duration = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

//多线程连接池压力测试
void mutiThreadConnectionPool()
{
    clock_t begin=clock();

    list<thread> tl;
    for(int i=0;i<4;i++)
    {
        tl.push_back(thread(connPoolTest));
    }

    for(auto& tt:tl)
    {
        tt.join();
    }

    clock_t end=clock();
    double duration = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << duration << " seconds" << std::endl;
}

int main()
{
    /*
    dataNum:1000    ->  time:10.3022 s
    dataNum:5000    ->  time:35.1183 s
    dataNum:10000    ->  time:60.1086 s
    */
    // singleThreadConnTest();

    /*
    dataNum:1000    ->  time:0.071227 s
    dataNum:5000    ->  time:4.45264 s
    dataNum:10000    ->  time:3.37099 s
    */
    singleThreadConnPoolTest();
    
    /*
    dataNum:1000    ->  time:2.48859 s
    dataNum:5000    ->  time:20.1149 s
    dataNum:10000    ->  time:40.711 s
    */
    // mutiThreadConnection();

    /*
    dataNum:1000    ->  time:0.569368 s
    dataNum:5000    ->  time:4.81965 s
    dataNum:10000    ->  time:1.72819 s
    */
    // mutiThreadConnectionPool();
    // ConnectionPool::getConnectionPool();
    return 0;
}
