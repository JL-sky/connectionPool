#include"connection.hpp"

Connection::Connection(){
    _conn=mysql_init(nullptr);
};
Connection::~Connection()
{
    if(_conn)
        mysql_close(_conn);
}

bool Connection::connect(string ip,unsigned short port,
            string user,string passwd,
            string dbname)
{
    MYSQL* p=mysql_real_connect(
        _conn,
        ip.c_str(),
        user.c_str(),
        passwd.c_str(),
        dbname.c_str(),
        port,
        nullptr,0
    );
    if(!p)
    {
        LOG("数据库连接失败！");
        LOG("错误信息:"+string(mysql_error(_conn))+"\n");
        return false;
    }

    mysql_query(_conn,"set names gbk");
    // LOG("数据库连接成功！");
    return true;

}

bool Connection::update(string sql)
{
    if(mysql_query(_conn,sql.c_str()))
    {
        LOG("更新失败！");
        LOG("错误信息："+string(mysql_error(_conn))+"\n");
        return false;
    }
    // LOG("更新成功！");
    return true;
}

MYSQL_RES* Connection::query(string sql)
{
    if(mysql_query(_conn,sql.c_str()))
    {
        LOG("查询失败！");
        LOG("错误信息："+string(mysql_error(_conn))+"\n");
        return nullptr;
    }
    return mysql_use_result(_conn);
}