//
// Created by xuqiang on 2023/10/16.
//
#include "ringbuffer.h"

bool_t ringbuffer_init(ringbuffer_t* ringbuffer, int size)
{
    ringbuffer->head = 0;
    ringbuffer->tail = 0;
    ringbuffer->valid_size = 0;
    ringbuffer->full_size = size;
    ringbuffer->data = (char*)malloc(size);
    if(ringbuffer->data == NULL)
        return false;
    return true;
}

void ringbuffer_release(ringbuffer_t* ringbuffer)
{
    if(ringbuffer->data)
        free(ringbuffer->data);
}

void ringbuffer_append(ringbuffer_t* ringbuffer, const char* buffer, int size)
{
    int len = ringbuffer->full_size - ringbuffer->valid_size;

    if(len >= size)
    {
        for(int i=0;i<size;i++)
        {
            ringbuffer->data[ringbuffer->tail] = buffer[i];
            ringbuffer->tail = (ringbuffer->tail + 1) % ringbuffer->full_size;
            ringbuffer->valid_size++;
        }
    }
    else
    {
        printf("no enough memory...");
        fflush(stdout);
    }
}

int ringbuffer_read(ringbuffer_t *ringbuffer, char *data, int size)
{
    if(size > ringbuffer->valid_size)
    {
        memcpy(data,ringbuffer->data + ringbuffer->head,ringbuffer->valid_size);
        return ringbuffer->valid_size;
    }

    int len = ringbuffer->full_size - ringbuffer->head;

    if(len >= size)
    {
        memcpy(data,ringbuffer->data + ringbuffer->head,size);
    }
    else
    {
        memcpy(data,&ringbuffer->data[ringbuffer->head],len);
        memcpy(data + len,ringbuffer->data,size - len);
    }
    return size;
}

void ringbuffer_popup(ringbuffer_t* ringbuffer, int size)
{
    ringbuffer->head = (ringbuffer->head + size) % ringbuffer->full_size;
    ringbuffer->valid_size -= size;
}

void ringbuffer_clear(ringbuffer_t* ringbuffer)
{
    ringbuffer->head = 0;
    ringbuffer->tail = 0;
    ringbuffer->valid_size = 0;
}

bool_t ringbuffer_empty(ringbuffer_t ringbuffer)
{
    if(ringbuffer.valid_size == 0)
        return true;
    return false;
}