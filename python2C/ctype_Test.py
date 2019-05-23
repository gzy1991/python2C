#!/usr/bin/python
# -*- coding: UTF-8 -*-
from ctypes import *
print(windll.kernel32)

msvcrt = cdll.msvcrt
print(msvcrt)

print(msvcrt.printf)
msg_str = b"Hello world!\n"
msvcrt.printf(b"Testing: %s", msg_str)
# 强制刷新缓冲区，立即输出，
# 若无此句，会导致下面的python语句输出结束了才输出下面的字符串
msvcrt.fflush(0)
print("***************************")
# 构建并使用C 数据类型
i = c_int(9)
print(i)
print(i.value)

i.value = 1212;
print(i.value)

str_cp = c_char_p(b"learn python ctypes")
print(str_cp)
print(str_cp.value)

str_cp = c_wchar_p("hello python")
print(str_cp)
print(str_cp.value)

print("***************************")

# num = c_int()
# print("input a int number:")
# msvcrt.scanf(b"%d", byref(num))
# print(num.value)