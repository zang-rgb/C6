/*
cJSON的主要功能是构建和解析json文件。
因为头文件的内容不是很多，所以我将其全部罗列出来，其中的核心函数是解析函数和打印函数。只有清楚cJSON的数据结构后，看相应的代码才能比较简单。头文件中并没有包含所有的函数，有的函数是在cJSON.c中定义的，一般是在解析过程中重复次数较多的函数。
*/

#ifndef cJSON__h
#define cJSON__h

#ifdef __cpluscplus
/*
首先，__cplusplus是cpp中的自定义宏，那么定义了这个宏的话表示这是一段cpp的代码，也就是说，上面的代码的含义是:如果这是一段cpp的代码，那么加入"extern "C"{"  和 " }"处理其中的代码，其中{ }内部的代码是通过extern"C"进行处理。要明白为何使用extern"C"，还得从cpp中对函数的重载处理开始说起。在c++中，为了支持重载机制，在编译生成的汇编码中，要对函数的名字进行一些处理，加入比如函数的返回类型等等.而在C中，只是简单的函数名字而已，不会加入其他的信息.也就是说:C++和C对产生的函数名字的处理是不一样的.

C++之父在设计C++之时，考虑到当时已经存在了大量的C代码，为了支持原来的C代码和已经写好C库，需要在C++中尽可能的支持C，而extern"C"就是其中的一个策略。因此，为了在C++代码中调用用C写成的库文件，就需要用extern"C"来告诉编译器:这是一个用C写成的库文件，请用C的方式来链接它们。
*/
extern "C"
{
#endif

/*cJSON Types: */
/* 这些宏定义是对结构体type的值定义，处理时只需要将type的值&255进行位运算，即可得到json里储存的数据类型。*/
#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6

#define cJSON_IsReference 256   // 100000000    2的8次方
#define cJSON_StringIsConst 512 // 1000000000   2的9次方

    /*
    cJSON的程序算法设计思想从其数据结构上就能反映出来。

    CJSON思想：结构体
    用一个结构体来表示其中的一条JSON的数据，而非一整段的JSON数据。
    嵌套（树）用child连接，兄弟关系用链表连接。
    CJSON是使用双向链表存储数据，访问类型与树结构，所以我们先来了解这个结构体。

    cJSON结构体中:
    type是值(value)的类型,一共有7种取值：
    分别是：False,Ture,NULL,Number,String,Array,Object。
    其中：
    如果type是Number类型,则valueint或valuedouble中存储着值。
    如果type是int类型,   则valueint中存储着值。
    如果type是double类型,则valuedouble中存储着值。
    如果type是String类型,则valuestring中存储着值。
    */
    typedef struct cJSON
    {
        struct cJSON *next;  // 向后链表指针
        struct cJSON *prev;  // 向前链表指针
        struct cJSON *child; // 对象或者数组的孩子节点指针

        int type; // value的类型

        char *valuestring;  // 字符串值
        int valueint;       // 整数值
        double valuedouble; // 浮点数值

        char *string; // 存放key
    } cJSON;

    /*
    源代码中该结构体提供了分配和释放空间的函数指针。
    实际上并没有跑到这块代码
    */
    typedef struct cJSON_Hooks
    {
        void *(*malloc_fn)(size_t sz); // malloc_fn是一个指向函数的指针，该函数参数为(size_t sz)，返回类型为void*
        void (*free_fn)(void *ptr);    // free_fn是一个指向函数的指针，该函数参数为(void *ptr)，返回类型为void
    } cJSON_Hooks;

    /*cJSON_InitHooks函数原型，向cJSON提供malloc和free函数*/
    void cJSON_InitHooks(cJSON_Hooks *hooks);

    /*
    extern是C语言中的一个关键字，一般用在变量名前或函数名前，用来说明“此变量/函数是在别处定义的，要在此处引用”
    源代码的.h文件加入了extern，表明extern声明的函数是在cJSON.c文件中定义的
    但其实不需要加入extern，因为在cJSON.c中#include了cJSON.h本文件。
    可能加了更好。
    */
    /* 提供一个JSON块，解析后返回一个可以查询的cJSON对象。完成后调用cJSON_Delete。 */
    extern cJSON *cJSON_Parse(const char *value);
    /* 将cJSON实体呈现为用于传输/存储的文本。完成后释放char*。 */
    extern char *cJSON_Print(cJSON *item);
    /* 将cJSON实体呈现为用于传输/存储的文本，而不进行任何格式化。完成后释放char*。 */
    char *cJSON_PrintUnformatted(cJSON *item);
    /* 使用缓冲策略将cJSON实体呈现为文本。预缓冲是对最终大小的猜测。猜测减少了重新分配。fmt=0表示无格式，=1表示有格式 */
    char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt);
    /* 删除一个cJSON实体和所有子实体。 */
    void cJSON_Delete(cJSON *c);

    /* 返回数组(或对象)中的项数。 */
    int cJSON_GetArraySize(cJSON *array);
    /* 从数组“数组”中检索项目编号“项目”。如果不成功，返回NULL。 */
    cJSON *cJSON_GetArrayItem(cJSON *array, int item);
    /* 从对象中获取项目"string"。不区分大小写。 */
    cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);

    /* 用于分析失败的语法。这将返回一个指向解析错误的指针。
    你可能需要回头看几个字才能理解它。当cJSON_Parse()返回0时定义。当cJSON_Parse()成功时为0。 */
    const char *cJSON_GetErrorPtr(void);

    /* 这些调用创建适当Type的cJSON项。 */
    cJSON *cJSON_CreateNull(void);
    cJSON *cJSON_CreateTrue(void);
    cJSON *cJSON_CreateFalse(void);
    cJSON *cJSON_CreateBool(int b);
    cJSON *cJSON_CreateNumber(double num);
    cJSON *cJSON_CreateString(const char *string);
    cJSON *cJSON_CreateArray(void);
    cJSON *cJSON_CreateObject(void);

    /* 根据count创建数组。 */
    cJSON *cJSON_CreateIntArray(const int *numbers, int count);
    cJSON *cJSON_CreateFloatArray(const float *numbers, int count);
    cJSON *cJSON_CreateDoubleArray(const double *numbers, int count);
    cJSON *cJSON_CreateStringArray(const char **strings, int count);

    /* 向指定的数组/对象追加项。 */
    void cJSON_AddItemToArray(cJSON *array, cJSON *item);
    void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
    void cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item); /* 当字符串确实是常量(例如，是一个文本，或者与常量一样好)，并且肯定会在cJSON对象中存活时，就使用这个方法 */
    /* 将对项的引用追加到指定的数组/对象。当您想要将现有的cJSON添加到新的cJSON中，但又不想破坏现有的cJSON时，可以使用此方法。 */
    void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
    void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

    /* 从数组/对象中删除/分离项。 */
    cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);
    void cJSON_DeleteItemFromArray(cJSON *array, int which);
    cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);
    void cJSON_DeleteItemFromObject(cJSON *object, const char *string);

    /* 更新数组项 */
    extern void cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem); /* 将已存在的项目向右移动。 */
    extern void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
    extern void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);

    /* 复制一个cJSON项目 */
    extern cJSON *cJSON_Duplicate(cJSON *item, int recurse);
    /* Duplicate将在需要释放的新内存中创建一个与传递的cJSON相同的新项目。
    递归!=0，它将复制连接到该项的所有子元素。条目->next和->prev指针在从Duplicate返回时总是0。*/

    /* ParseWithOpts允许您要求(并检查)JSON是否以null结尾，并检索指向解析后的最终字节的指针。 */
    extern cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

    extern void cJSON_Minify(char *json);

/* 用于快速创建内容的宏。 */
#define cJSON_AddNullToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateNull())
#define cJSON_AddTrueToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateTrue())
#define cJSON_AddFalseToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateFalse())
#define cJSON_AddBoolToObject(object, name, b) cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))
#define cJSON_AddNumberToObject(object, name, n) cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))
#define cJSON_AddStringToObject(object, name, s) cJSON_AddItemToObject(object, name, cJSON_CreateString(s))

/* 在分配整数值时，也需要将其传播到valuedouble。 */
#define cJSON_SetIntValue(object, val) ((object) ? (object)->valueint = (object)->valuedouble = (val) : (val))
#define cJSON_SetNumberValue(object, val) ((object) ? (object)->valueint = (object)->valuedouble = (val) : (val))

#ifdef __cpluscplus
}
#endif // 这个{}里面的#endif对应上面的#ifdef-cplusplus，{}里面的#ifdef-cplusplus对应最后的#endif, #ifdef与#endif总是一一对应的，表明条件编译开始和结束。

#endif // #ifdef与#endif总是一一对应的，表明条件编译开始和结束。