#pragma once
#include"/home/wutpups/Desktop/OSDev/Kernel/low_level.h"

// VGA
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

#define VID_MEM_ADDR (char*) 0x0b8000   // Start of Video Memory

#define REG_SCREEN_CTRL 0x3D4   // I/O Port
#define REG_SCREEN_DATA 0x3D5   // I/O Port

// Text Attriutes
#define WHITE_ON_BLACK 0x0f

void update_cursor(int x, int y)
{
	int pos = y * VGA_WIDTH + x;
 
	port_byte_out(REG_SCREEN_CTRL, 0x0F);
	port_byte_out(REG_SCREEN_DATA, (int) (pos & 0xFF));
	port_byte_out(REG_SCREEN_CTRL, 0x0E);
	port_byte_out(REG_SCREEN_DATA, (int) ((pos >> 8) & 0xFF));
}

void disable_cursor()
{
	port_byte_out(REG_SCREEN_CTRL, 0x0A);
	port_byte_out(REG_SCREEN_DATA, 0x20);
}

int get_cursor_position(void)
{
    int pos = 0;
    port_byte_out(0x3D4, 0x0F);
    pos |= port_byte_in(0x3D5);
    port_byte_out(0x3D4, 0x0E);
    pos |= ((int)port_byte_in(0x3D5)) << 8;
    return pos;
}

int get_offset(int col, int row)
{
	return 2 * (row * VGA_WIDTH + col);
}

void putc(char character, char attribute, int col, int row)
{
	if(!attribute)
	{
		attribute = WHITE_ON_BLACK;
	}

	int offset;
	int pos = get_cursor_position();
	int posx = pos % VGA_WIDTH;
	int posy = pos / VGA_WIDTH;

	if(col <= 0 && row >= 0 && col <= VGA_WIDTH && row <= VGA_HEIGHT)
	{
		offset = get_offset(col, row);
	}
	else
	{
		offset = get_offset(posx, posy);
	}

	if(character == '\n')
	{
		if((posy) + 1 <= VGA_HEIGHT)
		{
			update_cursor(0, posy);
		}
		else
		{
			update_cursor(0, posy + 1);
		}
		return;
	}

	*(VID_MEM_ADDR + offset) = character;
	*(VID_MEM_ADDR + offset + 1) = attribute;
	
	if(posx + 1 > VGA_WIDTH)
	{
		posx = 0;
		if(posy + 1 > VGA_HEIGHT)
		{
			
		}
		else
		{
			posy++;
		}
	}
	else
	{
		posx++;
	}

	update_cursor(posx, posy);
}

void print(char* s)
{
	for(int i = 0; s[i] != 0; i++)
	{
		putc(s[i], 0x0f, -1, -1);
	}
}

void clear_screen()
{
	for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++)
	{
		*(VID_MEM_ADDR + i) = 0;
		*(VID_MEM_ADDR + i + 1) = 0;
	}

	update_cursor(0,0);
}