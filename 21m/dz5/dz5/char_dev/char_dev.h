#ifndef CHAR_DEV_H
#define CHAR_DEV_H

#define BUFFER_SIZE 255
#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)
#define GET_MAJOR _IOR('a', 'c', int32_t *)
#define CLEAR_DATA _IO('a', 'd')

#endif