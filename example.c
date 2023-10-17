#include "ringbuffer.h"

int main()
{
    ringbuffer_t ringbuffer;
    ringbuffer_init(&ringbuffer, 1024);

    char buf1[11] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
    ringbuffer_append(&ringbuffer,buf1,11);
    char buf2[16] = {0x0c,0x0d,0x0e,0x0f,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f};
    ringbuffer_append(&ringbuffer,buf2,16);
    char temp[64] = {'\0'};
    int size = ringbuffer_read(&ringbuffer,temp,11);
    printf("read size: %d\n",size);
    for(int i=0;i<size;i++)
    {
        printf("0x%02x ",temp[i]);
    }
    printf("\n");
    ringbuffer_popup(&ringbuffer,ringbuffer.valid_size);
    ringbuffer_clear(&ringbuffer);
    printf("ringbuffer is empty: %d\n", ringbuffer_empty(ringbuffer));
    printf("ring buffer head %d\n",ringbuffer.head);
    printf("ring buffer tail %d\n",ringbuffer.tail);
    ringbuffer_append(&ringbuffer,"m",1);
    printf("ring buffer head %d\n",ringbuffer.head);
    printf("ring buffer tail %d",ringbuffer.tail);

    ringbuffer_release(&ringbuffer);
    return 0;
}
