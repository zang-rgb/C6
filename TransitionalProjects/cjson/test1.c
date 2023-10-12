#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

/*
作	用：将一个字符串文本解析为JSON格式,成功就返回文本在堆区的地址,失败就返回不能解析的地址然后打
        印不能解析的字符串部分回收堆区结构体内存。然后打印输出。再回收堆区存储解析好的文本
参	数：字符串地址
返回值：无
 */
void doit(char *text)
{
    char *out;                // 用于保存解析后的字符串地址
    cJSON *json;              // 声明cJSON结构体的指针
    json = cJSON_Parse(text); // 解析传进来的字符串
    if (json == NULL)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr()); // 打印不能被json解析的字符串
    }
    else
    {
        out = cJSON_Print(json); // 将树结构体使用json解析为字符串,并保存在堆区,返回堆区地址
        cJSON_Delete(json);      // 释放树结构体在堆区的空间
        printf("%s\n", out);     // 打印解析后的字符串
        free(out);               // 释放堆区解析好的字符串空间
    }
}

/* 从文件中读取字符串文本 */
void dofile(char *filename)
{
    FILE *f; // 文件指针
    long int len;
    char *data;

    f = fopen(filename, "rb"); // 以二进制方式读模式打开文件filename
    if (NULL == f)
    {
        printf("文件打开失败！\n");
        return;
    }
    fseek(f, 0, SEEK_END);             // 将文件指针定义到文件尾部,回退0个字节
    len = ftell(f);                    // 返回文件指针与文件开始处的字节数,即文件总字节数
    fseek(f, 0, SEEK_SET);             // 将文件指针定义到文件开始处,向后0个字节
    data = (char *)calloc(len + 1, 1); // 申请一块大于文件总字节数的空间,并初始化为0
    fread(data, 1, len, f);            // 将len个1大小字节的值拷贝到data内存中。返回成功读取的个数
    fclose(f);                         // 关闭fp指定文件,必要时刷新缓冲区(关闭失败返回EOF,成功返回0)
    doit(data);                        // 将字符串(data)先构造成树结构体,然后将书结构体使用json解析成字符串,并打印输出。
    free(data);                        // 释放堆区解析好的字符串空间
}

/* 下面测试代码用到的结构体 */
struct record
{
    const char *precision;
    double lat, lon;
    const char *address, *city, *state, *zip, *country;
};

/* 创建一组对象作为演示 */
void create_objects(void)
{
    cJSON *root; // 根节点(根结构体)
    cJSON *fmt;  // 用于保存视频实例中子对象的地址
    cJSON *img;  // 用于保存走廊实例中子对象的地址
    cJSON *thm;  // 用于保存走廊实例中子子对象的地址
    cJSON *fld;  // 用于保存唱片实例中子子对象的地址
    char *out;   // 保存解析后字符串在堆区的地址
    int i;       // 用于遍历

    /* 星期数(数组) */
    const char *strings[7] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday"};

    /* 矩阵(二维数组) */
    int numbers[3][3] = {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};

    /* 走廊(数组) */
    int ids[4] = {116, 943, 234, 38793};

    /* 唱片(结构体数组) */
    struct record fields[2] =
        {
            {"zip", 37.7668, -1.223959e+2, "", "SAN FRANCISCO", "CA", "94107", "US"},
            {"zip", 37.371991, -1.22026e+2, "", "SUNNYVALE", "CA", "94085", "US"}};

    /* 构造视频实例*/

    // 创建一个结构体对象 将type类型设置为对象, 并申请一块地址空间。返回地址
    root = cJSON_CreateObject();

    // 创建子结构体value为"Jack (\"Bee\") Nimble",key为"name"。然后连接fmt父结构体
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));

    // 创建子结构体对象并保存子结构体地址到fmt中,设置key为"type"。然后连接fmt父结构体
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());

    // 创建子结构体value为"rect",key为"type"。然后连接fmt父结构体
    cJSON_AddStringToObject(fmt, "type", "rect");

    // 创建子结构体value为1920,key为"width"。然后连接fmt父结构体
    cJSON_AddNumberToObject(fmt, "width", 1920);

    // 创建子结构体value为1080,key为"height"。然后连接fmt父结构体
    cJSON_AddNumberToObject(fmt, "height", 1080);

    // 创建子结构体value为false,key为"interlace"。然后连接fmt父结构体
    cJSON_AddFalseToObject(fmt, "interlace");

    // 创建子结构体value为24,key为"frame rate"。然后连接fmt父结构体
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    /* 树结构体解析成json格式字符串,并输出，回收堆区地址*/
    out = cJSON_Print(root); // 将root树结构解析成cjson格式字符串,并存放在堆区,成功返回堆区地址。失败返回NULL
    cJSON_Delete(root);      // 释放root树结构体在堆区的空间
    printf("%s\n", out);     // 打印解析后的字符串
    free(out);               // 释放堆区解析好的字符串空间

    /* 星期数(数组): */
    root = cJSON_CreateStringArray(strings, 7); // 构造星期数树结构(字符串数组)

    /* 树结构体解析成json格式字符串,并输出,回收堆区地址*/
    out = cJSON_Print(root); // 将root树结构解析成cjson格式字符串,并存放在堆区,成功返回堆区地址。失败返回NULL
    cJSON_Delete(root);      // 释放root树结构体在堆区的空间
    printf("%s\n", out);     // 打印解析后的字符串
    free(out);               // 释放堆区解析好的字符串空间

    /* 矩阵 */
    root = cJSON_CreateArray(); // 构造矩阵树结构(整型数组)
    for (i = 0; i < 3; i++)
    {
        // 创建一个子结构体数组，并与root连接起来
        cJSON_AddItemToArray(root, cJSON_CreateIntArray(numbers[i], 3));
    }

    // 创建子结构体,并成为root的第1个孩子节点
    // cJSON_ReplaceItemInArray(root,1,cJSON_CreateString("Replacement"));

    /* 树结构体解析成json格式字符串,并输出,回收堆区地址*/
    out = cJSON_Print(root); // 将root树结构解析成cjson格式字符串,并存放在堆区,成功返回堆区地址。失败返回NULL
    cJSON_Delete(root);      // 释放root树结构体在堆区的空间
    printf("%s\n", out);     // 打印解析后的字符串
    free(out);               // 释放堆区解析好的字符串空间

    /* 走廊 */
    root = cJSON_CreateObject();                                                   // 创建子结构体(类型为对象)
    cJSON_AddItemToObject(root, "Image", img = cJSON_CreateObject());              // 添加img子对象到root中
    cJSON_AddNumberToObject(img, "Width", 800);                                    // 添加子节点到img对象中
    cJSON_AddNumberToObject(img, "Height", 600);                                   // 添加子节点到img对象中
    cJSON_AddStringToObject(img, "Title", "View from 15th Floor");                 // 添加子节点到img对象中
    cJSON_AddItemToObject(img, "Thumbnail", thm = cJSON_CreateObject());           // 添加thm子对象到img对象中
    cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943"); // 添加子节点到thm对象中
    cJSON_AddNumberToObject(thm, "Height", 125);                                   // 添加子节点到thm对象中
    cJSON_AddStringToObject(thm, "Width", "100");                                  // 添加子节点到thm对象中
    cJSON_AddItemToObject(img, "IDs", cJSON_CreateIntArray(ids, 4));               // 添加ids子数组到img对象中

    /* 树结构体解析成json格式字符串,并输出,回收堆区地址*/
    out = cJSON_Print(root); // 将root树结构解析成cjson格式字符串,并存放在堆区,成功返回堆区地址。失败返回NULL
    cJSON_Delete(root);      // 释放root树结构体在堆区的空间
    printf("%s\n", out);     // 打印解析后的字符串
    free(out);               // 释放堆区解析好的字符串空间

    /* 唱片 */
    root = cJSON_CreateArray(); // 创建子结构体(类型为数组)
    for (i = 0; i < 2; i++)     // 二维数组
    {
        cJSON_AddItemToArray(root, fld = cJSON_CreateObject());         // 添加fld子对象到root中
        cJSON_AddStringToObject(fld, "precision", fields[i].precision); // 添加子节点到fld对象中
        cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);        // 添加子节点到fld对象中
        cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);       // 添加子节点到fld对象中
        cJSON_AddStringToObject(fld, "Address", fields[i].address);     // 添加子节点到fld对象中
        cJSON_AddStringToObject(fld, "City", fields[i].city);           // 添加子节点到fld对象中
        cJSON_AddStringToObject(fld, "State", fields[i].state);         // 添加子节点到fld对象中
        cJSON_AddStringToObject(fld, "Zip", fields[i].zip);             // 添加子节点到fld对象中
        cJSON_AddStringToObject(fld, "Country", fields[i].country);     // 添加子节点到fld对象中
    }

    // 创建子数组结构体,并成为root的第1个子对象且key==city的value
    // cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root,1),"City",cJSON_CreateIntArray(ids,4));

    /* 树结构体解析成json格式字符串,并输出,回收堆区地址*/
    out = cJSON_Print(root); // 将root树结构解析成cjson格式字符串,并存放在堆区,成功返回堆区地址。失败返回NULL
    cJSON_Delete(root);      // 释放root树结构体在堆区的空间
    printf("%s\n", out);     // 打印解析后的字符串
    free(out);               // 释放堆区解析好的字符串空间
}

#if 1
int main(int argc, const char *argv[])
{
    /* 一堆 cjson */
    char text1[] = "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    char text2[] = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
    char text3[] = "[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
    char text4[] = "{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
    char text5[] = "[\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\": 37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";

    /* 字符串方式调用 */
    doit(text1);
    doit(text2);
    doit(text3);
    doit(text4);
    doit(text5);

    /* 从文件中读取字符串文本 */
    /*	dofile("../../tests/test2"); */
    /*	dofile("../../tests/test3"); */
    /*	dofile("../../tests/test4"); */
    /*	dofile("../../tests/test5"); */

    /* Now some samplecode for building objects concisely: */
    create_objects();

    return 0;
}
#endif
