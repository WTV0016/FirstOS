#pragma once

void memcpy(char* src, char* dest, unsigned int num_bytes)
{
    for(int i = 0; i < num_bytes; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}