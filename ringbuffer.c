//
// Created by xuqiang on 2023/10/16.
//
#include "ringbuffer.h"

bool_t ringbuffer_init(ringbuffer_st* ringbuffer, int size)
{
    ringbuffer->head = 0;
    ringbuffer->tail = 0;
    ringbuffer->buffer_size = 0;
    ringbuffer->full_size = size;
    ringbuffer->data = (uint8_t*)malloc(size);
    if(ringbuffer->data == NULL)
        return false;
    return true;
}

void ringbuffer_release(ringbuffer_st* ringbuffer)
{
    if(ringbuffer->data)
        free(ringbuffer->data);
}

void ringbuffer_append(ringbuffer_st* ringbuffer, const data_t* buffer, int size)
{
    int len = ringbuffer->full_size - ringbuffer->buffer_size;

    if(len >= size)
    {
        for(int i=0;i<size;i++)
        {
            ringbuffer->data[ringbuffer->tail] = buffer[i];
            ringbuffer->tail = (ringbuffer->tail + 1) % ringbuffer->full_size;
            ringbuffer->buffer_size++;
        }
    }
    else
    {
        printf("no enough memory...\n");
        fflush(stdout);
    }
}

int ringbuffer_read(ringbuffer_st *ringbuffer, data_t* data, int size)
{
    if(size > ringbuffer->buffer_size)
    {
        memcpy(data,ringbuffer->data + ringbuffer->head,ringbuffer->buffer_size);
        return ringbuffer->buffer_size;
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

data_t ringbuffer_data(ringbuffer_st* ringbuffer, int index)
{
    data_t data;
    data = ringbuffer->data[(ringbuffer->head + index) % ringbuffer->full_size];
    return data;
}

void ringbuffer_popup(ringbuffer_st* ringbuffer, int size)
{
    ringbuffer->head = (ringbuffer->head + size) % ringbuffer->full_size;
    ringbuffer->buffer_size -= size;
}

void ringbuffer_clear(ringbuffer_st* ringbuffer)
{
    ringbuffer->head = 0;
    ringbuffer->tail = 0;
    ringbuffer->buffer_size = 0;
}

bool_t ringbuffer_empty(ringbuffer_st* ringbuffer)
{
    if(ringbuffer->buffer_size == 0)
        return true;
    return false;
}
