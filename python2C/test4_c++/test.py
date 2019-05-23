

#!/usr/bin/python
# -*- coding: UTF-8 -*-
from ctypes import *


# https://blog.csdn.net/u013179327/article/details/43735963

obj = CDLL("C:/work/PycharmProjects/python2C/python2C/test4_c++/libtest.so")

rst = obj.get_func_name_wrap()

data = string_at(rst, -1).decode("utf-8")
print (data)