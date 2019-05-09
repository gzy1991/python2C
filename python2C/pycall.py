import ctypes  
ll = ctypes.cdll.LoadLibrary   
lib = ll("./libpycall.so")    
sum = lib.foo(1, 3)  
print(sum)
print('***finish***'  )
