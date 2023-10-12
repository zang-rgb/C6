/* cJSON */
/* JSON parser in C. */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include "cJSON.h"

/*
解析失败的措施
将会定位在解析失败的字符上，并将不能解析的字符串输出
*/
static const char *ep;

/*
作  用：字符串解析失败函数
返回值：返回全局变量ep
*/
const char *cJSON_GetErrorPtr(void)
{
    return ep;
}

/*
作	用：用来比较参数s1和s2字符串,比较时会自动忽略大小写的差异
参	数：s1、s2是需要比较字符串
返回值：0表示相同  其他数值表示不相同
*/
static int cJSON_strcasecmp(const char *s1, const char *s2)
{
    if (NULL == s1 && NULL == s2) // s1均为null就返回0
    {
        return 0;
    }

    if (NULL == s1 || NULL == s2) // 只要有一方为null就返回1
    {
        return 1;
    }

    for (; tolower(*s1) == tolower(*s2); ++s1, ++s2) // tolower()大写转小写函数
    {
        if (*s1 == '\0') // 发现全部匹配成功就返回0
        {
            return 0;
        }
    }
    return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

// 默认将分配和释放空间函数指针指向malloc和free
// *******************  定义变量时一定要进行初始化！*********************
static void *(*cJSON_malloc)(size_t sz) = malloc;
static void (*cJSON_free)(void *ptr) = free;
/*
以下是错误的：
static void *(*cJSON_malloc)(size_t sz);
cJSON_malloc = malloc;
static void (*cJSON_free)(void *ptr) = free;
cJSON_free = free;
*/
/*
C语言编译错误：
error: initializer element is not constant（错误：初始值设定项元素不是常量）

C语言不允许全局变量在函数外进行赋值。除非是在定义变量的时候顺带一起对其进行初始化。

赋值语句要放在函数体内！
初始化可以在函数体外面，但是赋值一定要在函数体里面；
所以，请深刻理解初始化和赋值的区别；
    初始化是从无到有的过程，先分配空间，然后再填充数据；
    赋值是对己有的对象进行操作。
    初始化不是赋值，初始化的含义是在创建对象时赋予一个初值，而赋值是将对象的当前值擦除掉，以一个新值代替。
*/

/*
作	用：为str字符串在堆区开辟一块空间
参	数：字符串
返回值：堆区地址
*/
static char *cJSON_strdup(const char *str)
{
    size_t len = 0;    // size_t等价于unsigned int
    char *copy = NULL; // 保存堆区开辟的地址

    len = strlen(str) + 1;            // 计算字符串长度 最后需要加个'\0' 所以长度+1
    copy = (char *)cJSON_malloc(len); // 为字符串申请空间
    if (NULL == copy)                 // 空间申请失败
    {
        return 0;
    }

    memcpy(copy, str, len); // 将str复制到copy中,长度为len

    return copy;
}

/* 初始化钩子 */
/*
内存管理方面函数
在 c 语言中内存一般是 malloc 和 free 的。为了方便用户自由的管理内存， cjson 使用 Hook 技术来让使用者可以自定义内存管理函数。即用户自定义 malloc 和 free.具体实现方式可以参考下面的代码， 默认使用系统的 malloc 和 free 函数， 用 cJSON_InitHooks 函数（提供一个接口）可以替换成用户自定义的malloc 和 free 函数。
不过这个项目程序并没有调用cJSON_InitHooks这个函数。
*/
void cJSON_InitHooks(cJSON_Hooks *hooks)
{
    if (NULL == hooks)
    {
        // 如果未定义，则使用默认的malloc和free函数
        cJSON_malloc = malloc;
        cJSON_free = free;
        return;
    }
    // 定义了，则使用用户自定义的malloc和free函数
    cJSON_malloc = (hooks->malloc_fn) != NULL ? hooks->malloc_fn : malloc;
    cJSON_free = (hooks->free_fn) != NULL ? hooks->free_fn : free;
}

/*
作	用：为cJSON在堆区申请一块空间
返回值：堆区地址
*/
static cJSON *cJSON_New_Item(void)
{
    cJSON *node = (cJSON *)cJSON_malloc(sizeof(cJSON)); // 申请一个结构体的空间
    if (NULL == node)                                   // 申请空间失败
    {
        return NULL;
    }
    memset(node, 0, sizeof(cJSON)); // 初始化堆区开辟的内存
    return node;
}

/*
作 用：删除一个cJSON结构
参 数：结构体地址
*/
void cJSON_Delete(cJSON *c)
{
    cJSON *next = NULL;

    while (NULL != c)
    {
        next = c->next; // 指针向后移

        // 当前兄弟节点是最后一个节点且有孩子
        if (0 == (c->type & cJSON_IsReference) && NULL != c->child)
        {
            cJSON_Delete(c->child);
        }

        // 当前兄弟节点是最后一个且没有孩子，若有value为字符串就回收
        if (0 == (c->type & cJSON_IsReference) && NULL != c->valuestring)
        {
            cJSON_free(c->valuestring);
        }

        // 当前兄弟节点是最后一个且没有孩子，若有key也会受
        if (0 == (c->type & cJSON_StringIsConst) && NULL != c->string)
        {
            cJSON_free(c->string);
        }

        cJSON_free(c); // 回收根节点
        c = NULL;
    }
}

/*
作	用：将输入的字符串解析成数字(正数不需要+号,直接是数字,只有负数才有符号-)
参	数：item-结构体指针   num-字符串指针
返回值：字符串指针
*/
static const char *parse_number(cJSON *item, const char *num)
{                         //
    double n = 0;         // 保存数字
    double sign = 1;      // 数字符号的标志  1表示正数  -1表示负数
    double scale = 0;     // 用于有小数的数字,先不管小数点,记录扩大了多少倍
    int subscale = 0;     // 指数部分的数值值
    int signsubscale = 1; // 指数部分的符号位

    if (*num == '-') // 负数
    {
        sign = -1; // 设置标记
        num++;     // 指针后移
    }

    if (*num == '0') // 是0
    {
        num++;
    }

    /* 整数部分 */
    if (*num >= '1' && *num <= '9') // 数字不能从0开始
    {
        do
        {
            n = (n * 10.0) + (*num - '0');
            num++;                            // 指针后移
        } while (*num >= '0' && *num <= '9'); // 之后的数字范围就是0-9
    }

    /* 小数部分 */
    if (*num == '.' && num[1] >= '0' && num[1] <= '9') // 当前字符为"."且下一个字符为数字才有效
    {
        num++; // 跳过 小数点
        do
        {
            n = (n * 10.0) + (*num - '0');
            num++;
            scale++; // 记录扩大了多少倍
        } while (*num >= '0' && *num <= '9');
    }

    /* 指数部分 */
    if (*num == 'e' || *num == 'E')
    {
        num++; // 指针跳过指数

        if (*num == '+') // 指数位的符号位
        {
            num++;
        }
        else if (*num == '-')
        {
            signsubscale = -1; // 修改指数位的符号位
            num++;
        }

        while (*num >= '0' && *num <= '9') // 指数部分的数字位  可以从0开始
        {
            subscale = (subscale * 10) + (*num++ - '0');
        }
    }

    // 将之前扩大的再缩回来 公式：数值符号位 * 数值位 * 10^（指数符号位 * 指数数值位 - 扩大倍数）
    n = sign * n * pow(10.0, (subscale * signsubscale - scale));

    item->valuedouble = n;     // 将该值存入double类型中
    item->valueint = (int)n;   // 将该值存入int类型中
    item->type = cJSON_Number; // 将type类型设置为数字
    return num;
}

/* 作用：返回比x大的最小的2的N次方数 */
static int pow2gt(int x)
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x + 1;
}

/* 输出缓冲区结构体 */
typedef struct printbuffer
{
    char *buffer; // 缓冲区
    int length;   // 长度
    int offset;   // 偏移量
} printbuffer;

/*
作	用：判断当前偏移量下比较needed长度的字符是否越界并作出保护措施
参	数：p-输出缓冲结构体指针  needed-比较的长度
返回值：返回比较的首地址
*/
static char *ensure(printbuffer *p, int needed)
{
    char *newbuffer = NULL;
    int newsize = 0;

    if (NULL == p || NULL == p->buffer) // 结构体为空或者结构体缓冲区为空
    {
        return NULL;
    }

    needed += p->offset; // 计算原本偏移量 + 新的比较长度

    if (needed <= p->length) // 判断偏移量+比较长度是否小于字符串长度
    {
        return p->buffer + p->offset; // 返回初始地址 + 偏移量
    }

    newsize = pow2gt(needed); // 返回比x大的最小的2的N次方数
    newbuffer = (char *)cJSON_malloc(newsize);
    if (NULL == newbuffer) // 空间申请失败
    {
        cJSON_free(p->buffer);
        p->length = 0;
        p->buffer = 0;
        return NULL;
    }

    memcpy(newbuffer, p->buffer, p->length); // 将p->buffer拷贝到newbuffer,长度为参数三

    cJSON_free(p->buffer); // 回收掉之前用于保存字符串的空间
    p->length = newsize;   // 更新输出缓冲区结构体
    p->buffer = newbuffer; // 更新输出缓冲区结构体
    return newbuffer + p->offset;
}

/*
作	用：获取缓冲区的字符串长度(不是缓冲区大小,缓冲区大于等于字符串长度)
参	数：p-输出缓冲结构体指针
返回值：长度
*/
static int update(printbuffer *p)
{
    char *str = NULL;

    if (NULL == p || NULL == p->buffer) // 结构体为空或者结构体缓冲区为空
    {
        return 0;
    }

    str = p->buffer + p->offset;
    return p->offset + strlen(str); // 偏移量 + 后半段长度
}

/*
作	用：将给的数字类型结构体转换为字符串存储到p缓冲区中，若p为null就申请空间
参	数：item-给的数字类型结构体  p-缓冲区指针
返回值：未解析的地址
*/
static char *print_number(cJSON *item, printbuffer *p)
{
    char *str = NULL;
    double d = item->valuedouble;
    if (0 == d)
    {
        if (NULL != p) // 输出缓冲区结构体指针不为空  需要判断添加是否安全
        {
            str = ensure(p, 2); // 0转换成字符串 俩个字节  "0\0"
        }
        else
        {
            str = (char *)cJSON_malloc(2); // 为0申请空间
            if (NULL == str)               // 申请失败
            {
                return NULL;
            }
        }
        strcpy(str, "0"); // 拷贝0字符串
    }
    else if (fabs(((double)item->valueint) - d) <= DBL_EPSILON && d <= INT_MAX && d >= INT_MIN) // 判断是整型
    {
        if (NULL != p)
        {
            str = ensure(p, 11); // 2 ^ 32 + 1(-4294967296,4294967297)可以用11个字符表示。
        }
        else
        {
            str = (char *)cJSON_malloc(11); // 为2 ^ 32 + 1 申请空间
            if (NULL == str)                // 申请失败
            {
                return NULL;
            }
        }
        sprintf(str, "%d", item->valueint); // 将整型值存储到str指向的缓冲区中
    }
    else // double类型
    {
        if (p != NULL) // 2 ^ 64 + 1(18446744073709551617)可以用21个字符表示。
        {
            str = ensure(p, 21);
        }
        else
        {
            str = (char *)cJSON_malloc(21);
            if (NULL == str)
            {
                return NULL;
            }
        }

        if (fabs(floor(d) - d) <= DBL_EPSILON && fabs(d) < 1.0e60) // 无小数的double类型数字
        {
            sprintf(str, "%.0f", d);
        }
        else if (fabs(d) < 1.0e-6 || fabs(d) > 1.0e9) // 范围在(1.0e-6,1.0e9)就用科学计数法
        {
            sprintf(str, "%e", d);
        }
        else // 其他情况就用正常写法
        {
            sprintf(str, "%f", d);
        }
    }
    return str;
}

/* utf转换函数   */
static unsigned parse_hex4(const char *str)
{
    unsigned h = 0;
    if (*str >= '0' && *str <= '9')
        h += (*str) - '0';
    else if (*str >= 'A' && *str <= 'F')
        h += 10 + (*str) - 'A';
    else if (*str >= 'a' && *str <= 'f')
        h += 10 + (*str) - 'a';
    else
        return 0;

    h = h << 4;
    str++;

    if (*str >= '0' && *str <= '9')
        h += (*str) - '0';
    else if (*str >= 'A' && *str <= 'F')
        h += 10 + (*str) - 'A';
    else if (*str >= 'a' && *str <= 'f')
        h += 10 + (*str) - 'a';
    else
        return 0;

    h = h << 4;
    str++;

    if (*str >= '0' && *str <= '9')
        h += (*str) - '0';
    else if (*str >= 'A' && *str <= 'F')
        h += 10 + (*str) - 'A';
    else if (*str >= 'a' && *str <= 'f')
        h += 10 + (*str) - 'a';
    else
        return 0;

    h = h << 4;
    str++;

    if (*str >= '0' && *str <= '9')
        h += (*str) - '0';
    else if (*str >= 'A' && *str <= 'F')
        h += 10 + (*str) - 'A';
    else if (*str >= 'a' && *str <= 'f')
        h += 10 + (*str) - 'a';
    else
        return 0;

    return h;
}

/* Parse the input text into an unescaped cstring, and populate item. */
static const unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
/*
作	用：将字符串拷贝到堆区
参	数：item-结构体指针   str-字符串指针
返回值：字符串解析后的地址
*/
static const char *parse_string(cJSON *item, const char *str)
{
    const char *ptr = str + 1; // *str为"字符,所以从下一个开始,遍历字符串的指针
    char *out;                 // 用于接受申请在堆区空间的地址
    char *ptr2;                // 指向新开辟的空间的指针 ,用于将这段字符串拷贝在堆区
    int len = 0;               // 计算这段字符串的长度
    unsigned int uc, uc2;

    if (*str != '\"') // 当*str不为"时发现解析错误
    {
        ep = str;
        return NULL;
    }

    /* 为了计算出这段字符串的长度 */
    while (('\"' != *ptr) && ('\0' != *ptr)) // 当前字符不能为"和\0
    {
        len++;
        if (*ptr++ == '\\') // 去掉转义字符
            ptr++;
    }

    out = (char *)cJSON_malloc(len + 1); // 给字符串开辟空间 多一个存放\0
    if (NULL == out)                     // 空间申请失败
    {
        return NULL;
    }

    ptr = str + 1; // 指针再回到字符串开始位置
    ptr2 = out;

    while ('\"' != *ptr && '\0' != *ptr) // 将字符串一个个拷贝到堆区空间
    {
        if ('\\' != *ptr) // 只要不是转义字符就直接赋值
        {
            *ptr2++ = *ptr++;
        }
        else
        {
            ptr++;
            switch (*ptr) // 将转义字符存入堆区那块空间
            {
            case 'b':
                *ptr2++ = '\b';
                break;
            case 'f':
                *ptr2++ = '\f';
                break;
            case 'n':
                *ptr2++ = '\n';
                break;
            case 'r':
                *ptr2++ = '\r';
                break;
            case 't':
                *ptr2++ = '\t';
                break;
            case 'u': // 将utf16转换为utf8    不做分析
                uc = parse_hex4(ptr + 1);
                ptr += 4;

                if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0)
                    break;

                if (uc >= 0xD800 && uc <= 0xDBFF) /* UTF16 surrogate pairs.	*/
                {
                    if (ptr[1] != '\\' || ptr[2] != 'u')
                        break; /* missing second-half of surrogate.	*/
                    uc2 = parse_hex4(ptr + 3);
                    ptr += 6;
                    if (uc2 < 0xDC00 || uc2 > 0xDFFF)
                        break; /* invalid second-half of surrogate.	*/
                    uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
                }

                len = 4;

                if (uc < 0x80)
                    len = 1;
                else if (uc < 0x800)
                    len = 2;
                else if (uc < 0x10000)
                    len = 3;
                ptr2 += len;

                switch (len)
                {
                case 4:
                    *--ptr2 = ((uc | 0x80) & 0xBF);
                    uc >>= 6;
                case 3:
                    *--ptr2 = ((uc | 0x80) & 0xBF);
                    uc >>= 6;
                case 2:
                    *--ptr2 = ((uc | 0x80) & 0xBF);
                    uc >>= 6;
                case 1:
                    *--ptr2 = (uc | firstByteMark[len]);
                }
                ptr2 += len;
                break;
            default:
                *ptr2++ = *ptr;
                break;
            }      // 以上是utf16转utf8  不做分析
            ptr++; // 指向内存地址的指针后移
        }
    }

    *ptr2 = '\0'; // 拷贝完成最后补'\0'

    if (*ptr == '\"') // 把字符串最后"跳过
        ptr++;

    item->valuestring = out;   // 将字符串给到结构体中的valuestring
    item->type = cJSON_String; // 将数据类型设置为字符串
    return ptr;                // 返回新的字符串地址
}

/*
作	用：将字符串转换成文本模式
参	数：str-当前需要转义的字符串地址  p-输出缓冲区结构指针
返回值：返回该字符串在输出缓冲区起始地址
*/
static char *print_string_ptr(const char *str, printbuffer *p)
{
    const char *ptr = NULL; // 用于遍历查找 和计算字符串长度
    char *ptr2 = NULL;      // 接受out值
    char *out = NULL;       // 获取输出缓冲区的地址
    int len = 0;            // 保存字符串长度
    int flag = 0;           // 1表示字符串包含控制字符或者"或者\  0表示正常字符
    unsigned char token = ' ';

    for (ptr = str; '\0' != *ptr; ptr++) // 判断子串中是否包含控制字符或者"或者\ 有则为1无则为0
    {
        flag |= ((*ptr > 0 && *ptr < 32) || (*ptr == '\"') || (*ptr == '\\')) ? 1 : 0;
        if (1 == flag)
            break;
    }

    if (0 == flag) // 不包含控制字符 " \ 三种
    {
        len = ptr - str; // 计算长度

        if (NULL != p) // 输出缓冲区指针不为NULL
        {
            // 判断当前偏移量下比较len+3(因为需要放俩个""和一个\0)长度的字符是否越界并作出保护措施
            out = ensure(p, len + 3);
        }
        else
        {
            out = (char *)cJSON_malloc(len + 3); // 为字符串申请空间
        }

        if (!out) // 空间申请失败
            return 0;

        ptr2 = out;
        *ptr2++ = '\"';       // 先放第一个"
        strcpy(ptr2, str);    // 再拷贝字符串
        ptr2[len] = '\"';     // 最后放第二个"
        ptr2[len + 1] = '\0'; // 最后补\0
        return out;           // 返回该字符串在输出缓冲区起始地址
    }

    if (NULL == str) // 字符串为NULL
    {
        if (NULL != p) // 输出缓冲区指针不为NULL
        {
            // 判断当前偏移量下比较3(因为需要放俩个""和一个\0)长度的字符是否越界并作出保护措施
            out = ensure(p, 3);
        }
        else
        {
            out = (char *)cJSON_malloc(3); // 为字符串申请空间
        }

        if (NULL == out) // 空间申请失败
            return NULL;
        strcpy(out, "\"\""); // 想输出缓冲区放入 ""\0
        return out;          // 返回该字符串在输出缓冲区起始地址
    }
    ptr = str;
    while ('\0' != (token = *ptr) && ++len) // 计算字符串总长度
    {
        // 查找字符串 "\bfnrt 中首次出现字符token的位置,
        // 返回首次出现c的位置的指针,如果s中不存在c则返回NULL
        if (NULL != strchr("\"\\\b\f\n\r\t", token))
            len++;
        else if (token < 32) // 控制字符(不可见) 占5字节
            len += 5;

        ptr++;
    }

    if (NULL != p) // 输出缓冲区指针不为NULL
    {
        // 判断当前偏移量下比较len + 3长度的字符是否越界并作出保护措施
        out = ensure(p, len + 3);
    }
    else
    {
        out = (char *)cJSON_malloc(len + 3); // 为字符串申请空间
    }

    if (NULL == out) // 空间申请失败
    {
        return NULL;
    }

    ptr2 = out;
    ptr = str;
    *ptr2++ = '\"';      // 存入第一个"
    while ('\0' != *ptr) // 存入字符串内容
    {
        if ((unsigned char)*ptr > 31 && *ptr != '\"' && *ptr != '\\') // 不是控制字符也不是\和"
            *ptr2++ = *ptr++;
        else
        {
            *ptr2++ = '\\';
            switch (token = *ptr++)
            {
            case '\\':
                *ptr2++ = '\\';
                break;
            case '\"':
                *ptr2++ = '\"';
                break;
            case '\b':
                *ptr2++ = 'b';
                break;
            case '\f':
                *ptr2++ = 'f';
                break;
            case '\n':
                *ptr2++ = 'n';
                break;
            case '\r':
                *ptr2++ = 'r';
                break;
            case '\t':
                *ptr2++ = 't';
                break;
            default:
                sprintf(ptr2, "u%04x", token);
                ptr2 += 5;
                break; /* escape and print */
            }
        }
    }
    *ptr2++ = '\"'; // 存入第二个"
    *ptr2++ = '\0'; // 存入最后的\0
    return out;     // 返回该字符串在输出缓冲区起始地址
}

/* 向缓冲区存入字符串*/
static char *print_string(cJSON *item, printbuffer *p)
{
    return print_string_ptr(item->valuestring, p);
}

/* 预先声明这些原型。 */
static const char *parse_value(cJSON *item, const char *value);
static char *print_value(cJSON *item, int depth, int fmt, printbuffer *p);
static const char *parse_array(cJSON *item, const char *value);
static char *print_array(cJSON *item, int depth, int fmt, printbuffer *p);
static const char *parse_object(cJSON *item, const char *value);
static char *print_object(cJSON *item, int depth, int fmt, printbuffer *p);

/* 跳过控制字符和空格(ASCII-32) ，小于32是控制字符 32是空格*/
static const char *skip(const char *in)
{
    while (in != NULL && *in != '\0' && (unsigned char)*in <= 32)
    {
        in++; // 指针后移
    }
    return in;
}

/* 检查JSON 是否为空终止，并检索指向解析的最终字节的指针。
    在return_parse_end中提供ptr并且解析失败 */
cJSON *cJSON_ParseWithOpts(const char *value,
                           const char **return_parse_end, int require_null_terminated)
{
    const char *end = 0;         // 用于接收“跳过任何间距，获取的值”的地址
    cJSON *c = cJSON_New_Item(); // 申请空间
    /*
    在计算机内存中，0、’\0’、null是一样的，值都是0。以数字的方式读取就是0，以字符的方式读取就是’\0’，以某些其他方式读取就是null（比如指针，null的定义跟编译器有关，有的编译器定义null可能不是0）
    */
    // ep = NULL;
    // ep = '\0';
    ep = 0; // 初始化异常指针
    /*
    一般比较一个指针和NULL是否相等不要写成 if ( p ==NULL)，而写成 if ( NULL == p )，原因是第一种写法中如果不小心把双等号 == 写成单等号 = ，则编译器不会报错，但是程序的意思完全不一样了；而第二种写法如果不小心把双等号 == 写成了单等号 = ，则编译器会发现并报错。
    */
    if (NULL == c) // 申请内存失败
    {
        return 0;
    }
    end = parse_value(c, skip(value));
    if (NULL == end) // 发现没有数据  解析失败
    {
        cJSON_Delete(c); // 释放申请的空间
        return NULL;
    }
    /* 如果我们需要没有附加以null结尾的JSON，跳过，然后检查是否有null终止符 */
    // 函数中参数中提供了require_null_terminated是为了确保json字符串必须以'\0'字符作为结尾。
    // 若参数提供了return_parse_end，将返回json字符串解析完成后剩余的部分。
    if (require_null_terminated)
    {
        end = skip(end);  // 跳过空格
        if ('\0' != *end) // 遇到'\0'
        {
            cJSON_Delete(c); // 回收
            ep = end;
            return NULL;
        }
    }
    if (return_parse_end)
        *return_parse_end = end;

    return c;
}

/* cJSON解析默认函数 */
cJSON *cJSON_Parse(const char *value)
{
    return cJSON_ParseWithOpts(value, 0, 0);
}

/* 将cJSON格式的结构转成文本格式 */
char *cJSON_Print(cJSON *item)
{
    return print_value(item, 0, 1, NULL);
}

/* 将cJSON格式的结构转成文本格式(无格式) */
char *cJSON_PrintUnformatted(cJSON *item)
{
    return print_value(item, 0, 0, 0);
}

/* 将cJSON格式的结构存储到输出缓冲区 */
char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt)
{
    printbuffer p;
    p.buffer = (char *)cJSON_malloc(prebuffer);
    p.length = prebuffer;
    p.offset = 0;
    return print_value(item, 0, fmt, &p);
    return p.buffer;
}

/* 解析器核心——遇到文本时，适当地处理。 */
static const char *parse_value(cJSON *item, const char *value)
{
    if (!value)
        return 0; /* 不能为空，若为空，返回0 */
    // strncmp函数为字符串比较函数，函数声明为int strncmp ( const char * str1, const char * str2, size_t n );
    // 若str1与str2的前n个字符相同，则返回0；若s1大于s2，则返回大于0的值；若s1 小于s2，则返回小于0的值。
    // 对于json为null、true或者false的情况，直接将type置为对应的类型即可。
    if (!strncmp(value, "null", 4))
    {
        item->type = cJSON_NULL;
        return value + 4;
    }
    if (!strncmp(value, "false", 5))
    {
        item->type = cJSON_False;
        return value + 5;
    }
    if (!strncmp(value, "true", 4))
    {
        item->type = cJSON_True;
        item->valueint = 1;
        return value + 4;
    }
    // 以下需要了解JSON的结构
    if (*value == '\"')
    {
        return parse_string(item, value);
    }
    if (*value == '-' || (*value >= '0' && *value <= '9'))
    {
        return parse_number(item, value);
    }
    if (*value == '[')
    {
        return parse_array(item, value);
    }
    if (*value == '{')
    {
        return parse_object(item, value);
    }
    // 未找到匹配项,将地址给到ep。
    ep = value;
    return 0;
}

/*
功	能：将json结构体转换为字符串。
参	数：item-json结构体指针   depth-深度  fmt-输出格式  p-输出缓冲区结构体指针
返回值：字符串首地址
*/
static char *print_value(cJSON *item, int depth, int fmt, printbuffer *p)
{
    char *out = NULL;
    if (NULL == item) // 结构体指针为NULL
    {
        return NULL;
    }

    if (NULL != p) // 输出缓冲结构指针不为NULL
    {
        switch (item->type)
        {
        case cJSON_NULL: // 输出缓冲区指针不为NULL且类型为null 直接在原始地址偏移量下拷贝null
        {
            out = ensure(p, 5); // 检查当前偏移量下还能否放进去5个字符 "null\0" 并返回偏移后的地址
            if (out != NULL)
                strcpy(out, "null");
            break;
        }
        case cJSON_False: // 输出缓冲区指针不为NULL且类型为false 直接在原始地址偏移量下拷贝false
        {
            out = ensure(p, 6); // 检查当前偏移量下还能否放进去6个字符 "false\0" 并返回偏移后的地址
            if (out != NULL)
                strcpy(out, "false");
            break;
        }
        case cJSON_True: // 输出缓冲区指针不为NULL且类型为true 直接在原始地址偏移量下拷贝true
        {
            out = ensure(p, 5); // 检查当前偏移量下还能否放进去6个字符 "false\0" 并返回偏移后的地址
            if (out != NULL)
                strcpy(out, "true");
            break;
        }
        case cJSON_Number:               // 输出缓冲区指针不为NULL且类型为数字
            out = print_number(item, p); // 将结构体的数字存入到输出缓冲区中 还会检测能否放下
            break;
        case cJSON_String:               // 输出缓冲区指针不为NULL且类型为数字
            out = print_string(item, p); // 将结构体的字符串存入到输出缓冲区中 还会检测能否放下
            break;
        case cJSON_Array:                           // 输出缓冲区指针不为NULL且类型为数字
            out = print_array(item, depth, fmt, p); // 将结构体的数组存入到输出缓冲区中 还会检测能否放下
            break;
        case cJSON_Object:                           // 输出缓冲区指针不为NULL且类型为数字
            out = print_object(item, depth, fmt, p); // 将结构体的对象存入到输出缓冲区中 还会检测能否放下
            break;
        }
    }
    else // 输出缓冲结构指针为NULL  需要申请空间 首次申请不需要检查大小问题
    {
        switch (item->type)
        {
        case cJSON_NULL:
            out = cJSON_strdup("null");
            break;
        case cJSON_False:
            out = cJSON_strdup("false");
            break;
        case cJSON_True:
            out = cJSON_strdup("true");
            break;
        case cJSON_Number:
            out = print_number(item, NULL);
            break;
        case cJSON_String:
            out = print_string(item, NULL);
            break;
        case cJSON_Array:
            out = print_array(item, depth, fmt, NULL);
            break;
        case cJSON_Object:
            out = print_object(item, depth, fmt, NULL);
            break;
        }
    }
    return out;
}

/*
作	用：从输入文本构建数组。
参	数：item-结构体指针   value-字符串指针
返回值：解析后的文本地址
*/
static const char *parse_array(cJSON *item, const char *value)
{
    cJSON *child = NULL; // 节点指针(结构体指针)

    if (*value != '[') // 不是数组 匹配失败
    {
        ep = value;
        return 0;
    }

    item->type = cJSON_Array; // 设置类型为数组
    value = skip(value + 1);  // 更新指针,跳过一些空格和控制字符

    if (*value == ']') // 空数组
    {
        return value + 1;
    }

    // 如果不是空数组,就再申请一块空间  这块空间是item的孩子节点
    item->child = child = cJSON_New_Item();

    if (NULL == item->child) // 空间申请失败
    {
        return NULL;
    }

    // 先将指针跳过控制字符和空格,然后将接下来字符串指针找匹配的函数,
    // 然后将其放入孩纸结构体中,最后再将指针跳过控制字符和空格
    value = skip(parse_value(child, skip(value)));

    if (NULL == value) // 如果字符串指针走完了  就结束
    {
        return NULL;
    }

    while (*value == ',') // 如果碰到逗号
    {
        cJSON *new_item; // 定义新指针

        new_item = cJSON_New_Item(); // 申请新的空间
        if (NULL == new_item)        // 空间申请失败
        {
            return NULL;
        }

        // 该节点为孩子节点的弟弟节点  下面是将俩兄弟节点连接起来
        child->next = new_item;
        new_item->prev = child;

        child = new_item; // 更新节点指针

        // 先将指针跳过控制字符和空格,然后将接下来字符串指针找匹配的函数,
        // 然后将其放入孩纸结构体中,最后再将指针跳过控制字符和空格
        value = skip(parse_value(child, skip(value + 1)));

        if (NULL == value) // 走完了
        {
            return NULL;
        }
    }

    if (*value == ']') // 数组结束标志
    {
        return value + 1;
    }

    ep = value; // 特殊情况,为找打数组结束标志
    return NULL;
}

/*
功	能：将cjson数组结构体转换为字符串格式
参	数：item数组结构体指针 depth-深度  fmt-调整格式  p-输出缓冲结构体指针
返回值：
*/
static char *print_array(cJSON *item, int depth, int fmt, printbuffer *p)
{
    char **entries; // 保存一个数组的地址。该数组是指针数组。
    char *out = NULL;
    char *ptr = NULL;
    char *ret = NULL;
    int len = 5;
    cJSON *child = item->child;
    int numentries = 0; // 数组元素个数
    int i = 0;          // 循环计数器
    int fail = 0;       // 处理出错标志
    size_t tmplen = 0;

    /* 计算数组元素个数 */
    while (NULL != child)
    {
        numentries++;
        child = child->next;
    }

    /* 显现的处理元素个数为0时 */
    if (0 == numentries)
    {
        if (NULL != p)
            out = ensure(p, 3);
        else
            out = (char *)cJSON_malloc(3);

        if (NULL != out)
            strcpy(out, "[]");

        return out;
    }

    if (NULL != p)
    {
        /* 组成输出数组 */
        i = p->offset;
        ptr = ensure(p, 1);
        if (NULL == ptr)
            return NULL;

        *ptr = '[';
        p->offset++;

        child = item->child;
        while (NULL != child && 0 == fail)
        {
            print_value(child, depth + 1, fmt, p);
            p->offset = update(p);
            if (NULL != child->next)
            {
                len = fmt ? 2 : 1;
                ptr = ensure(p, len + 1);
                if (NULL == ptr)
                    return NULL;

                *ptr++ = ',';
                if (0 != fmt)
                    *ptr++ = ' ';

                *ptr = '\0';
                p->offset += len;
            }
            child = child->next;
        }
        ptr = ensure(p, 2);
        if (!ptr)
            return 0;
        *ptr++ = ']';
        *ptr = 0;
        out = (p->buffer) + i;
    }
    else
    {
        /* 分配一个指针数组来保存每个元素的指针*/
        entries = (char **)cJSON_malloc(numentries * sizeof(char *));
        if (NULL == entries) // 内存申请失败
            return 0;
        memset(entries, 0, numentries * sizeof(char *)); // 初始化内存

        /* 检索所有结果: */
        child = item->child;
        while (NULL != child && 0 == fail)
        {
            ret = print_value(child, depth + 1, fmt, 0);
            entries[i++] = ret;
            if (NULL != ret)
                len += strlen(ret) + 2 + (fmt ? 1 : 0);
            else
                fail = 1;        // 结束标记
            child = child->next; // 指向它的兄弟节点
        }

        /* 如果没有失败,尝试malloc输出字符串 */
        if (0 == fail)
            out = (char *)cJSON_malloc(len);

        if (NULL == out)
            fail = 1;

        if (0 != fail)
        {
            for (i = 0; i < numentries; i++)
            {
                if (entries[i])
                    cJSON_free(entries[i]);
            }
            cJSON_free(entries);
            return NULL;
        }

        *out = '[';
        ptr = out + 1;
        *ptr = '\0';
        for (i = 0; i < numentries; i++)
        {
            tmplen = strlen(entries[i]);
            memcpy(ptr, entries[i], tmplen);
            ptr += tmplen;
            if (i != numentries - 1)
            {
                *ptr++ = ',';
                if (0 != fmt)
                    *ptr++ = ' ';
                *ptr = '\0';
            }
            cJSON_free(entries[i]);
        }
        cJSON_free(entries);
        *ptr++ = ']';
        *ptr++ = '\0';
    }
    return out;
}

/*
功	能：从文本构建一个对象(就是{....}包含的)
参	数：item-结构体 value-字符串指针
返回值：字符串新的指针
*/
static const char *parse_object(cJSON *item, const char *value)
{
    cJSON *child = NULL;

    if ('{' != *value) // 不是对象
    {
        ep = value; // 将后面不能解析的字符串给到ep
        return NULL;
    }

    item->type = cJSON_Object; // 类型置为对象
    value = skip(value + 1);   // 开始找{后的非控制字符

    if ('}' == *value) // 若第一个非控制/空格字符为}，则内容为空，即{}。
    {
        return value + 1;
    }

    item->child = child = cJSON_New_Item(); // 为child分配空间，用child指向下一层结点
    if (!item->child)
        return 0;

    // 由JSON的object结构可知，在排除内容为空的前提下，{后遇到的可能是
    // 空格或字符串，所以用skip跳过空格，那么第一个直接遇到的就是字符串
    // 所以直接调用parse_string()函数。最外层的skip函数可以直接指向':'。
    value = skip(parse_string(child, skip(value)));
    if (!value)
        return 0;

    child->string = child->valuestring;
    child->valuestring = '\0';

    if (':' != *value) // 没找到":"
    {
        ep = value;
        return NULL;
    }

    /* 跳过任何间距，获取值。 */
    value = skip(parse_value(child, skip(value + 1)));

    if (!value)
        return 0;

    while (',' == *value) //','表明后面还有内容，那么就将上述操作再进行多次即可
    {
        cJSON *new_item;
        new_item = cJSON_New_Item();
        if (new_item == NULL) // 申请空间失败
        {
            return NULL;
        }

        // 将兄弟节点连接起来
        child->next = new_item;
        new_item->prev = child;

        child = new_item; // 更新节点指针

        /* 跳过任何间距，获取值。 */
        value = skip(parse_string(child, skip(value + 1)));
        if ('\0' == *value) // 字符串指针遇到'\0'
        {
            return NULL;
        }

        child->string = child->valuestring; // 将key放入string中
        child->valuestring = '\0';

        if (':' != *value) // 未找到":"
        {
            ep = value;
            return NULL;
        }

        /* 跳过任何间距，获取值。 */
        value = skip(parse_value(child, skip(value + 1)));
        if (value == NULL)
            return NULL;
    }

    if ('}' == *value) // {}结束标记
    {
        return value + 1;
    }

    ep = value; // 匹配到'}' 发生错误
    return NULL;
}

/*
功	能：将对象结构体转换为字符串存储在输出缓冲区中
参	数：item-对象   depth-深度  fmt-输出格式(1-有换行符 0-无)    p-输出缓冲结构体指针
返回值：返回字符串在堆区起始地址
*/
static char *print_object(cJSON *item, int depth, int fmt, printbuffer *p)
{
    char **entries = NULL; // 保存item中元素的value在输出缓冲区的地址
    char **names = NULL;   // 保存item中元素的key在输出缓冲区的地址
    char *out = NULL;      // 保存item转换为文本在堆区的位置
    char *ptr = NULL;
    char *ret = NULL;
    char *str = NULL;
    int len = 7;                // 字符串的长度 最少 "","" 7个字节
    int i = 0, j = 0;           // 循环计数器
    cJSON *child = item->child; // 指向item的第一个儿子
    int numentries = 0;         // 保存对象中对的个数
    int fail = 0;               // 保存到输出缓冲区的出错标志
    size_t tmplen = 0;

    while (NULL != child) // 计算有多少对元素
    {
        numentries++;
        child = child->next;
    }

    if (0 == numentries) // 键值对的个数为0
    {
        if (NULL != p) // 输出缓冲结构体指针不为NULL
        {
            // 判断当前偏移量下比较len+3(因为需要放俩个""和一个\0)长度的字符是否越界并作出保护措施
            out = ensure(p, fmt ? depth + 4 : 3);
        }
        else
        {
            out = (char *)cJSON_malloc(fmt ? depth + 4 : 3);
        }

        if (!out) // 申请空间失败
        {
            return 0;
        }

        ptr = out;
        *ptr++ = '{'; // 大括号开

        if (0 != fmt)
        {
            *ptr++ = '\n';
            for (i = 0; i < depth - 1; i++)
                *ptr++ = '\t';
        }
        *ptr++ = '}'; // 大括号闭
        *ptr++ = '\0';
        return out;
    }
    if (NULL != p) // 输出缓冲结构体指针不为NULL
    {
        /* 组成的输出: */
        i = p->offset;
        len = fmt ? 2 : 1; // 有换行符多一个字符"\n\0"

        // 判断当前偏移量下比较len+1(有换行符三个字节，无换行符俩个字节)长度的字符是否越界并作出保护措施
        ptr = ensure(p, len + 1);
        if (NULL == ptr) // 地址无效
            return NULL;

        *ptr++ = '{'; // 大括号开

        if (1 == fmt) // 判断有无换行符
            *ptr++ = '\n';

        *ptr = '\0';
        p->offset += len;    // 输出缓冲结构体的偏移量更新
        child = item->child; // 指向下一个儿子
        depth++;             // 深度+1
        while (NULL != child)
        {
            if (1 == fmt) // 有换行符
            {
                ptr = ensure(p, depth); // 安全检查
                if (NULL == ptr)        // 指针无效
                    return NULL;

                for (j = 0; j < depth; j++)
                    *ptr++ = '\t';

                p->offset += depth; // 更新输出缓冲结构体指针的偏移量
            }
            print_string_ptr(child->string, p); // 将字符串转换成文本模式
            p->offset = update(p);              // 获取缓冲区的字符串长度

            len = fmt ? 2 : 1;    // 计算长度
            ptr = ensure(p, len); // 安全检查
            if (NULL == ptr)      // 指针无效
                return NULL;

            *ptr++ = ':';

            if (1 == fmt)
                *ptr++ = '\t';

            p->offset += len; // 更新输出缓冲结构体指针偏移量

            print_value(child, depth, fmt, p); // 将json结构体转换为字符串。
            p->offset = update(p);             // 获取缓冲区的字符串长度

            len = (fmt ? 1 : 0) + (child->next ? 1 : 0);

            ptr = ensure(p, len + 1); // 安全检查
            if (NULL == ptr)          // 指针无效
                return NULL;

            if (NULL != child->next) // 判断还有无元素(节点)
                *ptr++ = ',';

            if (1 == fmt)
                *ptr++ = '\n';

            *ptr = '\0';
            p->offset += len;    // 更新输出缓冲结构体指针偏移量
            child = child->next; // 继续下一个节点
        }
        ptr = ensure(p, fmt ? (depth + 1) : 2); // 安全检查 考虑了换行符和tab
        if (NULL == ptr)                        // 指针无效
            return 0;

        if (1 == fmt)
        {
            for (i = 0; i < depth - 1; i++) // 深度
                *ptr++ = '\t';
        }
        *ptr++ = '}';
        *ptr = '\0';
        out = (p->buffer) + i;
    }
    else // 输出缓冲结构体指针不为NULL
    {
        entries = (char **)cJSON_malloc(numentries * sizeof(char *)); // 给value申请空间
        if (NULL == entries)                                          // 申请空间失败
        {
            return NULL;
        }
        names = (char **)cJSON_malloc(numentries * sizeof(char *)); // 给key申请空间
        if (NULL == names)                                          // 申请空间失败
        {
            cJSON_free(entries); // 释放前面申请成功的空间
            return NULL;
        }
        memset(entries, 0, sizeof(char *) * numentries); // 给value空间初始化
        memset(names, 0, sizeof(char *) * numentries);   // 给key空间初始化

        /* 将所有结果收集到我们的数组中: */
        child = item->child; // 指向数组第一个元素
        depth++;             // 深度增加 \t

        if (0 != fmt)
            len += depth;

        while (NULL != child)
        {
            names[i] = str = print_string_ptr(child->string, 0);    // 返回该元素key字符串在输出缓冲区的起始位置
            entries[i++] = ret = print_value(child, depth, fmt, 0); // 返回该元素value字符串在输出缓冲区的起始位置

            if (NULL != str && NULL != ret)
            {
                // fmt为换行符 depth为深度\t 深度可叠加 但是换行符最多有一个
                // key为一个字符串 value为一个字符串 所以会多出来俩个\0 因为strlen不算\0
                len += strlen(ret) + strlen(str) + 2 + (fmt ? 2 + depth : 0);
            }
            else // 出错了
            {
                fail = 1;
            }

            child = child->next; // 处理下一个元素(下一个节点)
        }

        /* 尝试分配输出字符串 */
        if (0 == fail)
            out = (char *)cJSON_malloc(len);
        if (NULL == out) // 申请失败
            fail = 1;

        /* 处理失败 */
        if (1 == fail)
        {
            for (i = 0; i < numentries; i++) // 将俩个数组中保存堆区开辟的空间依次释放掉
            {
                if (NULL != names[i])
                    cJSON_free(names[i]);

                if (NULL != entries[i])
                    cJSON_free(entries[i]);
            }
            cJSON_free(names);
            cJSON_free(entries);
            return NULL;
        }

        /* 组成的输出: */
        *out = '{';    // 存入大括开
        ptr = out + 1; // 指向未填充的地址
        if (1 == fmt)  // 有换行符
            *ptr++ = '\n';

        *ptr = '\0';
        for (i = 0; i < numentries; i++)
        {
            if (1 == fmt)
            {
                for (j = 0; j < depth; j++) // 深度
                    *ptr++ = '\t';
            }

            tmplen = strlen(names[i]);     // 计算当前key字符串的长度
            memcpy(ptr, names[i], tmplen); // 拷贝
            ptr += tmplen;                 // 指针更新
            *ptr++ = ':';
            if (1 == fmt)
                *ptr++ = '\t';

            strcpy(ptr, entries[i]);   // 拷贝当前value字符串
            ptr += strlen(entries[i]); // 指针更新
            if (i != numentries - 1)
                *ptr++ = ',';

            if (1 == fmt)
                *ptr++ = '\n';

            *ptr = '\0';
            cJSON_free(names[i]); // 释放掉当前键值对所占的内存
            cJSON_free(entries[i]);
        }

        cJSON_free(names);
        cJSON_free(entries);

        if (1 == fmt) // 格式操作
        {
            for (i = 0; i < depth - 1; i++)
                *ptr++ = '\t';
        }
        *ptr++ = '}'; // 大括号闭
        *ptr++ = '\0';
    }
    return out; // 返回字符串在堆区起始地址
}

/* 获取数组大小/对象个数 */
int cJSON_GetArraySize(cJSON *array)
{
    cJSON *c = array->child; // 指向第一个儿子
    int i = 0;
    while (NULL != c)
    {
        i++;
        c = c->next;
    }
    return i;
}

/* 查找数组结构体第item(从0开始)个子结构体的地址并返回 */
cJSON *cJSON_GetArrayItem(cJSON *array, int item)
{
    cJSON *c = array->child;
    while (NULL != c && item > 0)
    {
        item--;
        c = c->next;
    }
    return c;
}

/* 查找对象结构体中key为string的子结构体的地址并返回 */
cJSON *cJSON_GetObjectItem(cJSON *object, const char *string)
{
    cJSON *c = object->child;
    while (NULL != c && 0 != cJSON_strcasecmp(c->string, string))
    {
        c = c->next;
    }
    return c;
}

/* 将兄弟节点连接起来  类似与链表结构 */
static void suffix_object(cJSON *prev, cJSON *item)
{
    prev->next = item;
    item->prev = prev;
}

/* 用于处理引用的实用程序(拷贝一份item结构体)  */
static cJSON *create_reference(cJSON *item)
{
    cJSON *ref = cJSON_New_Item();
    if (NULL == ref) // 申请失败
    {
        return NULL;
    }

    memcpy(ref, item, sizeof(cJSON)); // 内存初始化
    ref->string = '\0';
    ref->type |= cJSON_IsReference;
    ref->next = NULL;
    ref->prev = NULL;

    return ref;
}

/*
功	能：添加元素(子结构体)到数组(父结构体)最后
参	数：array-数组结构体  item-元素子结构体
返回值：无
*/
void cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    cJSON *c = array->child; // 指向父结构体的第一个儿子

    if (NULL == item) // 若发现子结构体指针为空就直接结束
    {
        return;
    }

    if (NULL == c) // 若发现父结构的儿子为空时,直接添加
    {
        array->child = item;
    }
    else // 若发现父结构的儿子不为空时,就开始找最后那个儿子节点
    {
        while (NULL != c && NULL != c->next)
        {
            c = c->next;
        }
        suffix_object(c, item); // 连接新节点函数
    }
}

/*
功	能：添加子结构到对象中
参	数：object-对象  string-新子结构的key  item-新结构体的value
返回值：无
*/
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item)
{
    if (NULL == item) // 子结构体指针为NULL
    {
        return;
    }
    /*
    错误
    if ('\0' != item->string) // 子结构体中的key(string)不为空.就释放掉
    {
        cJSON_free(item->string);
    }
    */
    if (item->string) // 子结构体中的key(string)不为空.就释放掉
        cJSON_free(item->string);

    // 先在堆区开辟空间将key(string)放入然后再将堆区地址给到key(string)保管
    item->string = cJSON_strdup(string);

    cJSON_AddItemToArray(object, item); // 将子结构体放入对象(jbject)中
}

/*
功	能：添加元素结构体到对象结构体中
参	数：object-对象  string-新添加元素的key   item-新添加元素的value
返回值：无
*/
void cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item)
{
    if (NULL == item)
    {
        return;
    }
    /*
    错误
    if (0 == (item->type & cJSON_StringIsConst) && '\0' != item->string) // 若item的key存在就先释放
    {
        cJSON_free(item->string);
    }
    */
    if (!(item->type & cJSON_StringIsConst) && item->string) // 若item的key存在就先释放
        cJSON_free(item->string);

    item->string = (char *)string;      // 将key放入item
    item->type |= cJSON_StringIsConst;  // 将type放入item
    cJSON_AddItemToArray(object, item); // 再将item放入对象(数组)中
}

/* 添加元素引用到数组中 */
void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)
{
    cJSON_AddItemToArray(array, create_reference(item));
}

/* 添加元素引用到对象中 */
void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item)
{
    cJSON_AddItemToObject(object, string, create_reference(item));
}

/*
功	能：将元素从数组中分离
参	数：array-数组  which-下标(要分离元素的下标)
返回值：分离后元素的地址
*/
cJSON *cJSON_DetachItemFromArray(cJSON *array, int which)
{
    cJSON *c = array->child; // 指向第一个儿子(第0个元素)

    while (NULL != c && which > 0) // 寻找要分离的元素位置
    {
        c = c->next;
        which--;
    }

    if (NULL == c) // 指针为NULL
    {
        return NULL;
    }

    if (NULL != c->prev) // 要分离的元素不是第0个元素
    {
        c->prev->next = c->next;
    }

    if (NULL != c->next) // 要分离的元素不是最后一个元素
    {
        c->next->prev = c->prev;
    }

    if (c == array->child) // 要分离的元素是第0个元素
    {
        array->child = c->next;
    }

    c->prev = c->next = NULL; // 其他情况
    return c;
}

/* 从数组中删除元素 */
void cJSON_DeleteItemFromArray(cJSON *array, int which)
{
    cJSON_Delete(cJSON_DetachItemFromArray(array, which));
}

/*
功	能：从对象中分离元素
参	数：object-对象  string-要查找元素的key
返回值：元素分离后的地址
*/
cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string)
{
    int i = 0;
    cJSON *c = object->child;
    while (NULL != c && 0 != cJSON_strcasecmp(c->string, string)) // 查找要删除的key为string
    {
        i++;
        c = c->next;
    }

    if (NULL != c) // 找到了
        return cJSON_DetachItemFromArray(object, i);
    return NULL;
}

/* 从对象中删除元素 */
void cJSON_DeleteItemFromObject(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObject(object, string));
}

/*
功	能：添加元素到数组或者对象中
参	数：array-数组  which-插入的下标(从0开始)  newitem-插入的新元素(新节点)
返回值：无
*/
void JSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *c = array->child;       // 用于保存插入的元素节点
    while (NULL != c && which > 0) // 找插入的位置
    {
        c = c->next;
        which--;
    }

    if (NULL == c) // 发现插入位置大于等于数组元素个数
    {
        cJSON_AddItemToArray(array, newitem); // 添加到数组最后
        return;
    }

    /* 连接新节点 */
    newitem->next = c;
    newitem->prev = c->prev;
    c->prev = newitem;

    if (c == array->child) // 如果是第0个元素(第一个儿子)
        array->child = newitem;
    else
        newitem->prev->next = newitem;
}

/*
作	用：将newiem节点替换为array的第which子节点
参	数：array-根节点, which-替换的第几个子节点  newitem-新的子节点
返回值：无
*/
void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *c = array->child;

    while (NULL != c && which > 0) // 找到需要替换的子节点
    {
        c = c->next;
        which--;
    }

    if (NULL == c) // 替换的位置超过目前节点
    {
        return;
    }

    newitem->next = c->next; // 新节点连接弟弟节点
    newitem->prev = c->prev; // 新节点连接哥哥节点

    if (NULL != newitem->next) // 新节点不是最后一个
    {
        newitem->next->prev = newitem; // 弟弟节点连接新节点
    }

    if (c == array->child) // 若被替换的节点是父节点的第一个孩子节点
    {
        array->child = newitem; // 就将父节点的孩子节点设置为新节点
    }
    else
    {
        newitem->prev->next = newitem; // 哥哥节点连接新节点
    }

    c->next = NULL;  // 将旧节点指针置为空
    c->prev = NULL;  // 将旧节点指针置为空
    cJSON_Delete(c); // 回收被替换的指针内存
}

/*
作	用：用新的value，替换object对象中key==string那一个子节点
参	数：object-被替换的根对象的一个子节点    string-被替换的key    newitem-新子节点的value
返回值：无
*/
void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem)
{
    int i = 0;
    cJSON *c = object->child;

    while (NULL != c && cJSON_strcasecmp(c->string, string)) // 查找object下key为string的子节点
    {
        i++;
        c = c->next;
    }

    if (NULL != c) // 找到了
    {
        newitem->string = cJSON_strdup(string);       // 在堆区存放字符串的地址给到子节点的key
        cJSON_ReplaceItemInArray(object, i, newitem); // 将object的第i个子节点替换为newitem
    }
}

/* 创建子结构体(类型为NULL) */
cJSON *cJSON_CreateNull(void)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间成功
    {
        return NULL;
    }
    item->type = cJSON_NULL; // 将结构体的type类型设置为true
    return item;             // 返回结构体地址
}

/* 创建子结构体(类型为true) */
cJSON *cJSON_CreateTrue(void)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间成功
    {
        return NULL;
    }
    item->type = cJSON_True; // 将结构体的type类型设置为true
    return item;             // 返回结构体地址
}

/* 创建子结构体(类型为false) */
cJSON *cJSON_CreateFalse(void)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = cJSON_False; // 将结构体的type类型设置为false
    return item;              // 返回结构体地址
}

/* 创建子结构体(类型为bool) */
cJSON *cJSON_CreateBool(int b)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = b ? cJSON_True : cJSON_False; // 设置结构体的type类型为bool
    return item;
}

/* 创建子结构体(类型为数字) */
cJSON *cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = cJSON_Number; // 将结构体的type类型设置为数字
    item->valuedouble = num;   // 将num给到valuedouble
    item->valueint = (int)num; // 将num给到valueint
    return item;
}

/* 创建子结构体(类型为字符串) */
cJSON *cJSON_CreateString(const char *string) // 参数const防止字符串被修改
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = cJSON_String;                // 将结构体的type类型设置为字符串
    item->valuestring = cJSON_strdup(string); // 将堆区开辟的空间地址给到valuestring中
    return item;
}

/* 创建子结构体(类型为数组)  */
cJSON *cJSON_CreateArray(void)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = cJSON_Array; // 将结构体的type类型设置为字符串
    return item;
}

/* 创建子结构体(类型为对象)  */
cJSON *cJSON_CreateObject(void)
{
    cJSON *item = cJSON_New_Item(); // 向堆区给结构体申请一块空间
    if (NULL == item)               // 申请空间失败
    {
        return NULL;
    }
    item->type = cJSON_Object; // 将结构体的type类型设置为字符串
    return item;
}

/*
功	能：创建一个数组结构体
参	数：number-数组指针	count-数组的长度
返回值：返回数组结构体地址
*/
cJSON *cJSON_CreateIntArray(const int *numbers, int count)
{
    int i = 0;
    cJSON *n = 0;                   // 保存创建的子结构体(子节点)地址
    cJSON *p = 0;                   // 保存每次更新后的前一个节点(父节点或者哥哥节点)
    cJSON *a = cJSON_CreateArray(); // 保存创建的父结构体(父节点)地址
    if (NULL == a)                  // 堆区内存申请失败
        return NULL;

    for (i = 0; i < count; i++)
    {
        n = cJSON_CreateNumber(numbers[i]); // 创建子结构体(类型为数字)
        if (NULL == n)                      // 堆区内存申请失败
            return NULL;
        if (0 == i) // 第一个子节点,就是父节点的儿子(child)
            a->child = n;
        else
            suffix_object(p, n); // 将兄弟节点连接起来
        p = n;                   // 更新前一个节点
    }
    return a; // 返回父节点的地址
}

/*
功	能：创建浮点型数组
参	数：numbers-双精度数组指针 count-数组个数
返回值：返回数组结构体指针
*/
cJSON *cJSON_CreateFloatArray(const float *numbers, int count)
{
    int i = 0;
    cJSON *n = 0;                   // 接收数字类型结构体的地址
    cJSON *p = 0;                   // 保存每次更新后的前一个节点(父节点或者哥哥节点)
    cJSON *a = cJSON_CreateArray(); // 保存创建的父结构体(父节点)地址
    if (NULL == a)                  // 堆区内存申请失败
        return NULL;

    for (i = 0; NULL != a && i < count; i++)
    {
        n = cJSON_CreateNumber(numbers[i]); // 创建子结构体(类型为数字)
        if (NULL == n)                      // 堆区内存申请失败
            return NULL;
        if (0 == i) // 第一个儿子
            a->child = n;
        else
            suffix_object(p, n); // 连接兄弟节点
        p = n;                   // 更新前一个节点
    }
    return a;
}

/*
功	能：创建双进度型数组或者对象的结构体
参	数：numbers-双精度数组指针 count-数组个数
返回值：返回数组结构体指针
*/
cJSON *cJSON_CreateDoubleArray(const double *numbers, int count)
{
    int i = 0;
    cJSON *n = 0;                   // 接收数字类型结构体的地址
    cJSON *p = 0;                   // 保存每次更新后的前一个节点(父节点或者哥哥节点)
    cJSON *a = cJSON_CreateArray(); // 保存创建的父结构体(父节点)地址
    if (NULL == a)                  // 堆区内存申请失败
        return NULL;

    for (i = 0; NULL != a && i < count; i++)
    {
        n = cJSON_CreateNumber(numbers[i]); // 创建子结构体(类型为数字)
        if (NULL == n)                      // 堆区内存申请失败
            return NULL;
        if (0 == i) // 第一个儿子
            a->child = n;
        else
            suffix_object(p, n); // 连接兄弟节点
        p = n;
    }
    return a;
}

/*
功	能：创建字符串数组或者对象
参	数：strings-字符串数组指针 count-数组个数
返回值：返回数组结构体指针
*/
cJSON *cJSON_CreateStringArray(const char **strings, int count)
{
    int i = 0;
    cJSON *n = 0;                   // 接收字符串类型结构体的地址
    cJSON *p = 0;                   // 保存每次更新后的前一个节点(父节点或者哥哥节点)
    cJSON *a = cJSON_CreateArray(); // 保存创建的父结构体(父节点)地址
    if (NULL == a)                  // 堆区内存申请失败
        return NULL;

    for (i = 0; NULL != a && i < count; i++)
    {
        n = cJSON_CreateString(strings[i]); // 创建子结构体(类型为字符串)
        if (NULL == n)                      // 堆区内存申请失败
            return NULL;
        if (0 == i) // 第一个儿子
            a->child = n;
        else
            suffix_object(p, n); // 连接兄弟节点
        p = n;
    }
    return a;
}

/*
功	能：深复制一份结构体
参	数：item-结构体指针  recurse-递归层数
返回值：返回新复制的地址
*/
cJSON *cJSON_Duplicate(cJSON *item, int recurse)
{
    cJSON *newitem = NULL;  // 保存首地址
    cJSON *cptr = NULL;     // 拷贝区域的指针
    cJSON *nptr = NULL;     // 原区域的指针
    cJSON *newchild = NULL; // 新子节点

    if (NULL == item)
        return NULL;

    newitem = cJSON_New_Item();
    if (NULL == newitem)
        return NULL;

    /* 复制所有的变量 */
    newitem->type = item->type;
    newitem->valueint = item->valueint;
    newitem->valuedouble = item->valuedouble;
    if (NULL != item->valuestring) // 拷贝value
    {
        newitem->valuestring = cJSON_strdup(item->valuestring);
        if (NULL == newitem->valuestring) // 开辟失败
        {
            cJSON_Delete(newitem);
            return NULL;
        }
    }
    if (NULL != item->string) // 拷贝key
    {
        newitem->string = cJSON_strdup(item->string);
        if (NULL == newitem->string) // 开辟失败
        {
            cJSON_Delete(newitem);
            return 0;
        }
    }

    /* 如果是非递归的，那么我们就完成了! */
    if (0 == recurse)
        return newitem;

    /* 递归复制 */
    cptr = item->child;
    while (cptr)
    {
        newchild = cJSON_Duplicate(cptr, 1);
        if (NULL == newchild) // 开辟失败
        {
            cJSON_Delete(newitem);
            return 0;
        }
        if (NULL != nptr) // 不是第一个儿子
        {
            nptr->next = newchild; // 连接兄弟节点
            newchild->prev = nptr;
            nptr = newchild; // 更新拷贝区域的指针
        }
        else // 第一个儿子
        {
            newitem->child = newchild; // 设置为父节点的儿子
            nptr = newchild;           // 更新拷贝区域的指针
        }
        cptr = cptr->next; // 更新原区域
    }
    return newitem;
}

/*
功	能：移除文档中的所有空白和注释,实现对 JSON 内容的最小化压缩。实现无开销和近乎完美的表现
参	数：json-结构体指针
返回值：无
*/
void cJSON_Minify(char *json)
{
    char *into = json;
    while ('\0' != *json)
    {
        if (*json == ' ') // 是空格
            json++;
        else if (*json == '\t') // 是制表符\t
            json++;
        else if (*json == '\r') // \r回到当前行的行首，而不会换到下一行，如果接着输出的话，本行以前的内容会被逐一覆盖；
            json++;
        else if (*json == '\n') // 换行符
            json++;
        else if (*json == '/' && json[1] == '/') // C++风格注释
            while (*json && *json != '\n')       // 不是\0也不是换行符
                json++;
        else if (*json == '/' && json[1] == '*') // c风格注释/*
        {
            while ('\0' != *json && !(*json == '*' && json[1] == '/')) // 到*/注释结束
                json++;
            json += 2; // 最后跳过 */ 俩个字节
        }
        else if (*json == '\"') // 字符串 开始
        {
            *into++ = *json++;                     // 开始拷贝
            while ('\0' != *json && *json != '\"') // 到 \" 结束
            {
                if (*json == '\\') // 发现是转义字符,会多占一个字节
                    *into++ = *json++;
                *into++ = *json++;
            }
            *into++ = *json++;
        }
        else
            *into++ = *json++; // 其他所有字符
    }
    *into = '\0';
}
