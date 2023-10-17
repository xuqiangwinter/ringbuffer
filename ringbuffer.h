//
// Created by xuqiang on 2023/10/16.
//

#ifndef CODE_RINGBUFFER_H
#define CODE_RINGBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int head;
    int tail;
    int full_size;
    int valid_size;
    char* data;
} ringbuffer_t;

typedef int bool_t;

bool_t ringbuffer_init(ringbuffer_t* ringbuffer, int size);
void ringbuffer_release(ringbuffer_t* ringbuffer);
void ringbuffer_append(ringbuffer_t* ringbuffer, const char* buffer, int size);
int ringbuffer_read(ringbuffer_t* ringbuffer, char* data, int size);
void ringbuffer_popup(ringbuffer_t* ringbuffer, int size);
void ringbuffer_clear(ringbuffer_t* ringbuffer);
bool_t ringbuffer_empty(ringbuffer_t ringbuffer);

#ifdef __cplusplus
}
#endif

#endif //CODE_RINGBUFFER_H
