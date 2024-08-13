#include "menu_nest/render.h"
#include "stdlib.h"
#include "string.h"

//假设是属性是数字，信息是字符串，回调函数应知道属性和信息的类型。
//此回调函数的目的是将字符串信息打印属性中的数字次
void callback(MN_render * o_MN_render){
    int * p_count = (int *)(o_MN_render->mp_attribute);
    char * p_str = (char *)(o_MN_render->mp_memory);

    for(int i = 0;i < *p_count;i++){
        printf("%s\n",p_str);
    }
}

int render_test_main(){
    int  * test_attr = (int *)malloc(sizeof(int)); 
    char * test_memory = (char *)malloc(sizeof(char) * 32);
    
    *test_attr = 3;
    strcpy(test_memory,"this is test str.");

    MN_render * obj = MN_render_create(test_memory);
    MN_render_set_attribute(obj,test_attr);
    MN_render_set_rendering_callback(obj,callback);

    MN_render_rendering(obj);

    printf("---------------------\n");
    *(int *)(MN_render_get_attribute(obj)) = 5;//更改渲染器属性

    MN_render_rendering(obj);

    MN_render_destroy(obj);//注意，render并不是完全拥有memory和attr，销毁时并不会销毁这两个。
    free(test_attr);
    test_attr = NULL;
    free(test_memory);
    test_memory = NULL;
    return 0;
}