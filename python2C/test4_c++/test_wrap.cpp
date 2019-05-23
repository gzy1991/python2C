#include "test.h"
#include "string.h"

extern "C" {
char * get_func_name_wrap(){
    static string name;
    get_func_name(name);
    return const_cast<char*>(name.c_str());
}
}
