#ifndef CONNECTION_H
#define CONNECTION_H
#include<mysql/mysql.h>
#include<ctime>
#include"public.hpp"

class Connection
{
public:
    //初始化数据库连接
    Connection();
    //释放数据库连接
    ~Connection();
    //连接数据库
    bool connect(string ip,unsigned short port,
                string user,string passwd,
                string dbname);
    //对数据库进行操作，增加、删除、修改
    bool update(string sql);
    //查询操作
    MYSQL_RES* query(string sql);

    //刷新链接的起始空闲时间点
    void refreshAliveTime(){_aliveTime=clock();}
    //获取连接的空闲时间
    clock_t getAliveTime(){return clock()-_aliveTime;}

private:
    MYSQL* _conn;
    clock_t _aliveTime;//记录每个连接空闲状态的初始时间点
};

#endif