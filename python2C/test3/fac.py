#!/usr/bin/python
# -*- coding: UTF-8 -*-
from ctypes import *
# gcc -o fac.so -shared -fPIC fac.c

fac=  CDLL('C:/work/PycharmProjects/python2C/python2C/test3/fac.so')

i=5
fac_result=fac.fac(i)
print("阶乘  "+str(i)+":! == "+str(fac_result))

s = "Hello, World"
c_s = c_char_p(s.encode('utf-8'))
re_result= fac.reverse(c_s)  #返回的是指针
print(string_at(re_result, -1).decode("utf-8"))

st_result = fac.returnString()
print(string_at(st_result, -1).decode("utf-8"))
# print(string_at(st_result, -1) )

te_result=fac.testchar(11)
b = string_at(te_result)
print(b.decode("utf-8"))
