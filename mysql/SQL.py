#!/usr/bin/python
# -*- coding: UTF-8 -*-
# import MySQLdb

# 使用pymysql代替'MySQLdb'.
import pymysql
pymysql.install_as_MySQLdb()


# 根据主键id进行查询
def getById(id ):
    # 连接database
    conn = pymysql.connect(host="localhost", user="root", password="123456", database="mydb", charset="utf8")
    # # 得到一个可以执行SQL语句的光标对象
    # cursor = conn.cursor()
    # 游标设置为字典类型
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    # 定义要执行的SQL语句
    sql = "select  *  from  scooter where id =%s "
    # sql2 = "select  *  from  scooter  "
    cursor.execute(sql,[id])
    # cursor.execute(sql )
    result = cursor.fetchone()
    # row_2 = cursor.fetchmany(3)
    # row_3 = cursor.fetchall()
    conn.commit()
    cursor.close()
    conn.close()

    print(result)
    return result
# getById("1")



# 插入数据到mysql
def insertInfo():
    import uuid
    import datetime
    conn = pymysql.connect(host="localhost", user="root", password="123456", database="mydb", charset="utf8")
    cursor = conn.cursor()
    id= uuid.uuid1().hex #生成一个主键，以32个字符表示的UUID
    dt = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") #时间戳
    # print(id)
    # print(dt)
    sql="""
    INSERT INTO scooter(
        id,
        m_prot_head1,
        m_prot_head2,
        m_bootloader_mode,
        m_aes_key,
        m_random_array,
        m_result,
        create_time
     ) VALUES (%s, %s, %s, %s, %s, %s, %s, %s);
    """
    # 执行SQL语句
    try:
        cursor.execute(sql, [id,
                             "",
                             "",
                             "",
                             "",
                             "",
                             "",
                             dt])
        # 提交事务
        conn.commit()
    except Exception as e:
        # 有异常，回滚事务
        conn.rollback()
    cursor.close()
    conn.close()
    return True

# insertInfo()