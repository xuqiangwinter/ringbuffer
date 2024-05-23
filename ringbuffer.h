//
// Created by xuqiang on 2023/10/16.
//
#ifndef CODE_RINGBUFFER_H
#define CODE_RINGBUFFER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

typedef uint8_t data_t;

typedef struct
{
    int head;
    int tail;
    int full_size;
    int buffer_size;
    data_t* data;
} ringbuffer_st;

typedef int bool_t;

//初始化环形缓冲区
bool_t ringbuffer_init(ringbuffer_st* ringbuffer, int size);

//释放资源
void ringbuffer_release(ringbuffer_st* ringbuffer);

//添加数据到环形缓冲区
/*
    ringbuffer_st* ringbuffer: 环形缓冲区
    const data_t* buffer: 添加的数据内存地址
    int size: 添加的数据大小
*/
void ringbuffer_append(ringbuffer_st* ringbuffer, const data_t* buffer, int size);

//从环形缓冲区读取数据
/*
    ringbuffer_st* ringbuffer: 环形缓冲区
    data_t* data: 读取的数据存放地址
    int size: 读取的大小

    return: 实际读取的大小
*/
int ringbuffer_read(ringbuffer_st* ringbuffer, data_t* data, int size);

//根据下标获取环形缓冲区数据
/*
    ringbuffer_st ringbuffer: 环形缓冲区
    int index: 数据所在下标

    return: index对应在环形缓冲区的值
*/
data_t ringbuffer_data(ringbuffer_st* ringbuffer, int index);

//移除缓冲区数据
/*
    ringbuffer_st* ringbuffer: 环形缓冲区
    int size: 移除数据大小
*/
void ringbuffer_popup(ringbuffer_st* ringbuffer, int size);

//清空缓冲区数据
/*
    ringbuffer_st* ringbuffer: 环形缓冲区
*/
void ringbuffer_clear(ringbuffer_st* ringbuffer);

//判断环形缓冲区是否为空
/*
    ringbuffer_st* ringbuffer: 环形缓冲区

    return: true为空， false不为空
*/
bool_t ringbuffer_empty(ringbuffer_st* ringbuffer);

#ifdef __cplusplus
}
#endif

#endif //CODE_RINGBUFFER_H
