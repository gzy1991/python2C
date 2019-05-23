#!/usr/bin/python
# -*- coding: UTF-8 -*-

import ctypes
ll = ctypes.cdll.LoadLibrary   
lib = ll("./libpycall.so")    
sum = lib.foo(1, 3)  
print(sum)
print('***finish***'  )
