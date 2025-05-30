#include "font.h"

char font8x8_basic[256][13] = {
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 0
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 1
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 2
	{0x18,	0x24,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 3
	{0x14,	0x28,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 4
	{0x00,	0x24,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 5
	{0x24,	0x18,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 6
	{0x10,	0x28,	0x10,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 7
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x10,	0x10,	0x10}, // char # 8
	{0x14,	0x28,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 9
	{0x28,	0x10,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 10
	{0x10,	0x20,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 11
	{0x10,	0x08,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 12
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x10,	0x10}, // char # 13
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 14
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 15
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 16
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 17
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 18
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 19
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 20
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 21
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 22
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 23
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 24
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 25
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 26
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 27
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 28
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 29
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 30
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 31
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 32
	{0x00,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x00,	0x00,	0x10,	0x00,	0x00,	0x00}, // char # 33
	{0x24,	0x24,	0x24,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 34
	{0x00,	0x14,	0x14,	0x14,	0x7f,	0x28,	0xfe,	0x50,	0x50,	0x50,	0x00,	0x00,	0x00}, // char # 35
	{0x10,	0x3c,	0x50,	0x50,	0x70,	0x38,	0x1c,	0x14,	0x14,	0x78,	0x10,	0x00,	0x00}, // char # 36
	{0x00,	0x61,	0x92,	0x94,	0x68,	0x18,	0x16,	0x29,	0x49,	0x86,	0x00,	0x00,	0x00}, // char # 37
	{0x00,	0x18,	0x24,	0x24,	0x38,	0x71,	0x89,	0x8e,	0xc6,	0x7e,	0x00,	0x00,	0x00}, // char # 38
	{0x10,	0x10,	0x10,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 39
	{0x06,	0x08,	0x10,	0x30,	0x20,	0x20,	0x20,	0x20,	0x30,	0x10,	0x08,	0x06,	0x00}, // char # 40
	{0x60,	0x10,	0x08,	0x04,	0x04,	0x04,	0x04,	0x04,	0x04,	0x08,	0x10,	0x60,	0x00}, // char # 41
	{0x00,	0x10,	0x52,	0x24,	0x3c,	0x24,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 42
	{0x00,	0x00,	0x00,	0x10,	0x10,	0x10,	0xfe,	0x10,	0x10,	0x10,	0x00,	0x00,	0x00}, // char # 43
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x30,	0x30,	0x10,	0x20,	0x00}, // char # 44
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x7e,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 45
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x30,	0x30,	0x00,	0x00,	0x00}, // char # 46
	{0x01,	0x02,	0x02,	0x04,	0x08,	0x08,	0x10,	0x10,	0x20,	0x40,	0x40,	0x80,	0x00}, // char # 47
	{0x00,	0x18,	0x24,	0x42,	0x42,	0x42,	0x42,	0x42,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 48
	{0x00,	0x30,	0xd0,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xfe,	0x00,	0x00,	0x00}, // char # 49
	{0x00,	0x78,	0x04,	0x04,	0x04,	0x08,	0x10,	0x20,	0x40,	0x7c,	0x00,	0x00,	0x00}, // char # 50
	{0x00,	0x78,	0x04,	0x04,	0x08,	0x30,	0x0c,	0x04,	0x04,	0x78,	0x00,	0x00,	0x00}, // char # 51
	{0x00,	0x08,	0x18,	0x28,	0x28,	0x48,	0x88,	0xfc,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 52
	{0x00,	0x3c,	0x20,	0x20,	0x38,	0x04,	0x04,	0x04,	0x04,	0x38,	0x00,	0x00,	0x00}, // char # 53
	{0x00,	0x1c,	0x20,	0x40,	0x5c,	0x62,	0x42,	0x42,	0x22,	0x1c,	0x00,	0x00,	0x00}, // char # 54
	{0x00,	0x7e,	0x02,	0x04,	0x08,	0x08,	0x10,	0x10,	0x20,	0x20,	0x00,	0x00,	0x00}, // char # 55
	{0x00,	0x3c,	0x42,	0x42,	0x24,	0x3c,	0x46,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 56
	{0x00,	0x38,	0x44,	0x42,	0x42,	0x46,	0x3a,	0x02,	0x04,	0x38,	0x00,	0x00,	0x00}, // char # 57
	{0x00,	0x00,	0x00,	0x18,	0x18,	0x00,	0x00,	0x00,	0x18,	0x18,	0x00,	0x00,	0x00}, // char # 58
	{0x00,	0x00,	0x00,	0x30,	0x30,	0x00,	0x00,	0x00,	0x30,	0x30,	0x10,	0x20,	0x00}, // char # 59
	{0x00,	0x00,	0x00,	0x02,	0x0c,	0x10,	0x60,	0x10,	0x0c,	0x02,	0x00,	0x00,	0x00}, // char # 60
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x7e,	0x00,	0x7e,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 61
	{0x00,	0x00,	0x00,	0x40,	0x30,	0x08,	0x06,	0x08,	0x30,	0x40,	0x00,	0x00,	0x00}, // char # 62
	{0x00,	0x7c,	0x42,	0x02,	0x04,	0x08,	0x10,	0x00,	0x00,	0x10,	0x00,	0x00,	0x00}, // char # 63
	{0x00,	0x3c,	0x62,	0xde,	0xb2,	0xa2,	0xa6,	0x9b,	0x44,	0x3c,	0x00,	0x00,	0x00}, // char # 64
	{0x00,	0x00,	0x18,	0x18,	0x24,	0x24,	0x24,	0x7e,	0x42,	0x81,	0x00,	0x00,	0x00}, // char # 65
	{0x00,	0x00,	0x7c,	0x42,	0x42,	0x7c,	0x42,	0x42,	0x42,	0x7c,	0x00,	0x00,	0x00}, // char # 66
	{0x00,	0x00,	0x3e,	0x40,	0x80,	0x80,	0x80,	0x80,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 67
	{0x00,	0x00,	0x78,	0x44,	0x42,	0x42,	0x42,	0x42,	0x44,	0x78,	0x00,	0x00,	0x00}, // char # 68
	{0x00,	0x00,	0x7e,	0x40,	0x40,	0x40,	0x7c,	0x40,	0x40,	0x7e,	0x00,	0x00,	0x00}, // char # 69
	{0x00,	0x00,	0x7e,	0x40,	0x40,	0x40,	0x7c,	0x40,	0x40,	0x40,	0x00,	0x00,	0x00}, // char # 70
	{0x00,	0x00,	0x3e,	0x40,	0x80,	0x80,	0x8e,	0x82,	0x42,	0x3e,	0x00,	0x00,	0x00}, // char # 71
	{0x00,	0x00,	0x42,	0x42,	0x42,	0x7e,	0x42,	0x42,	0x42,	0x42,	0x00,	0x00,	0x00}, // char # 72
	{0x00,	0x00,	0x7c,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x7c,	0x00,	0x00,	0x00}, // char # 73
	{0x00,	0x00,	0x3c,	0x04,	0x04,	0x04,	0x04,	0x04,	0x04,	0x78,	0x00,	0x00,	0x00}, // char # 74
	{0x00,	0x00,	0x42,	0x44,	0x48,	0x70,	0x50,	0x48,	0x44,	0x42,	0x00,	0x00,	0x00}, // char # 75
	{0x00,	0x00,	0x40,	0x40,	0x40,	0x40,	0x40,	0x40,	0x40,	0x7e,	0x00,	0x00,	0x00}, // char # 76
	{0x00,	0x00,	0xc6,	0xc6,	0xaa,	0xaa,	0xaa,	0x92,	0x82,	0x82,	0x00,	0x00,	0x00}, // char # 77
	{0x00,	0x00,	0x42,	0x62,	0x52,	0x52,	0x4a,	0x4a,	0x46,	0x42,	0x00,	0x00,	0x00}, // char # 78
	{0x00,	0x00,	0x38,	0x44,	0x82,	0x82,	0x82,	0x82,	0x44,	0x38,	0x00,	0x00,	0x00}, // char # 79
	{0x00,	0x00,	0x7c,	0x42,	0x42,	0x42,	0x7c,	0x40,	0x40,	0x40,	0x00,	0x00,	0x00}, // char # 80
	{0x00,	0x00,	0x38,	0x44,	0x82,	0x82,	0x82,	0x82,	0x44,	0x38,	0x06,	0x03,	0x00}, // char # 81
	{0x00,	0x00,	0x78,	0x44,	0x44,	0x44,	0x78,	0x48,	0x44,	0x42,	0x00,	0x00,	0x00}, // char # 82
	{0x00,	0x00,	0x3e,	0x40,	0x40,	0x38,	0x04,	0x02,	0x02,	0x7c,	0x00,	0x00,	0x00}, // char # 83
	{0x00,	0x00,	0xfe,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x00,	0x00,	0x00}, // char # 84
	{0x00,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 85
	{0x00,	0x00,	0x81,	0x42,	0x42,	0x44,	0x24,	0x28,	0x38,	0x10,	0x00,	0x00,	0x00}, // char # 86
	{0x00,	0x00,	0x81,	0x81,	0x92,	0x5a,	0x5a,	0x6a,	0x66,	0x24,	0x00,	0x00,	0x00}, // char # 87
	{0x00,	0x00,	0x81,	0x42,	0x24,	0x18,	0x18,	0x24,	0x42,	0x81,	0x00,	0x00,	0x00}, // char # 88
	{0x00,	0x00,	0x82,	0x44,	0x28,	0x28,	0x10,	0x10,	0x10,	0x10,	0x00,	0x00,	0x00}, // char # 89
	{0x00,	0x00,	0xfe,	0x02,	0x04,	0x08,	0x10,	0x20,	0x40,	0xfe,	0x00,	0x00,	0x00}, // char # 90
	{0x1e,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x1e,	0x00}, // char # 91
	{0x80,	0x40,	0x40,	0x20,	0x10,	0x10,	0x08,	0x08,	0x04,	0x02,	0x02,	0x01,	0x00}, // char # 92
	{0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x78,	0x00}, // char # 93
	{0x00,	0x08,	0x08,	0x18,	0x14,	0x24,	0x24,	0x42,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 94
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0x00}, // char # 95
	{0x10,	0x08,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 96
	{0x00,	0x00,	0x00,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 97
	{0x40,	0x40,	0x40,	0x5c,	0x62,	0x42,	0x42,	0x42,	0x62,	0x5c,	0x00,	0x00,	0x00}, // char # 98
	{0x00,	0x00,	0x00,	0x1e,	0x20,	0x40,	0x40,	0x40,	0x20,	0x1e,	0x00,	0x00,	0x00}, // char # 99
	{0x02,	0x02,	0x02,	0x3a,	0x46,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 100
	{0x00,	0x00,	0x00,	0x3c,	0x22,	0x42,	0x7e,	0x40,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 101
	{0x1e,	0x20,	0x20,	0xfe,	0x20,	0x20,	0x20,	0x20,	0x20,	0x20,	0x00,	0x00,	0x00}, // char # 102
	{0x00,	0x00,	0x00,	0x3a,	0x46,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x02,	0x02,	0x3c}, // char # 103
	{0x40,	0x40,	0x40,	0x5c,	0x62,	0x42,	0x42,	0x42,	0x42,	0x42,	0x00,	0x00,	0x00}, // char # 104
	{0x18,	0x18,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 105
	{0x18,	0x18,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x70}, // char # 106
	{0x40,	0x40,	0x40,	0x44,	0x48,	0x50,	0x60,	0x50,	0x48,	0x44,	0x00,	0x00,	0x00}, // char # 107
	{0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 108
	{0x00,	0x00,	0x00,	0xb6,	0xda,	0x92,	0x92,	0x92,	0x92,	0x92,	0x00,	0x00,	0x00}, // char # 109
	{0x00,	0x00,	0x00,	0x5c,	0x62,	0x42,	0x42,	0x42,	0x42,	0x42,	0x00,	0x00,	0x00}, // char # 110
	{0x00,	0x00,	0x00,	0x3c,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 111
	{0x00,	0x00,	0x00,	0x5c,	0x62,	0x42,	0x42,	0x42,	0x62,	0x5c,	0x40,	0x40,	0x40}, // char # 112
	{0x00,	0x00,	0x00,	0x3a,	0x46,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x02,	0x02,	0x02}, // char # 113
	{0x00,	0x00,	0x00,	0x5c,	0x64,	0x40,	0x40,	0x40,	0x40,	0x40,	0x00,	0x00,	0x00}, // char # 114
	{0x00,	0x00,	0x00,	0x3c,	0x40,	0x60,	0x18,	0x04,	0x04,	0x78,	0x00,	0x00,	0x00}, // char # 115
	{0x00,	0x00,	0x20,	0xfc,	0x20,	0x20,	0x20,	0x20,	0x20,	0x1c,	0x00,	0x00,	0x00}, // char # 116
	{0x00,	0x00,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 117
	{0x00,	0x00,	0x00,	0x82,	0x44,	0x44,	0x44,	0x28,	0x28,	0x10,	0x00,	0x00,	0x00}, // char # 118
	{0x00,	0x00,	0x00,	0x81,	0x91,	0x5a,	0x5a,	0x6a,	0x24,	0x24,	0x00,	0x00,	0x00}, // char # 119
	{0x00,	0x00,	0x00,	0x42,	0x24,	0x18,	0x18,	0x18,	0x24,	0x42,	0x00,	0x00,	0x00}, // char # 120
	{0x00,	0x00,	0x00,	0x81,	0x42,	0x42,	0x24,	0x24,	0x18,	0x18,	0x10,	0x30,	0xe0}, // char # 121
	{0x00,	0x00,	0x00,	0x7e,	0x02,	0x04,	0x08,	0x10,	0x20,	0x7e,	0x00,	0x00,	0x00}, // char # 122
	{0x1c,	0x10,	0x10,	0x10,	0x10,	0x60,	0x10,	0x10,	0x10,	0x10,	0x10,	0x0c,	0x00}, // char # 123
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x00}, // char # 124
	{0x30,	0x08,	0x08,	0x08,	0x08,	0x06,	0x08,	0x08,	0x08,	0x08,	0x08,	0x30,	0x00}, // char # 125
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x71,	0x8e,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 126
	{0x00,	0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x3c,	0x00,	0x00,	0x00}, // char # 127
	{0x00,	0x00,	0x3e,	0x40,	0x80,	0x80,	0x80,	0x80,	0x40,	0x3e,	0x04,	0x02,	0x06}, // char # 128
	{0x00,	0x24,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 129
	{0x08,	0x10,	0x00,	0x3c,	0x22,	0x42,	0x7e,	0x40,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 130
	{0x18,	0x24,	0x00,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 131
	{0x00,	0x24,	0x00,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 132
	{0x10,	0x08,	0x00,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 133
	{0x10,	0x28,	0x10,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 134
	{0x00,	0x00,	0x00,	0x1e,	0x20,	0x40,	0x40,	0x40,	0x20,	0x1e,	0x08,	0x04,	0x0c}, // char # 135
	{0x18,	0x24,	0x00,	0x3c,	0x22,	0x42,	0x7e,	0x40,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 136
	{0x00,	0x12,	0x00,	0x3c,	0x22,	0x42,	0x7e,	0x40,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 137
	{0x10,	0x08,	0x00,	0x3c,	0x22,	0x42,	0x7e,	0x40,	0x40,	0x3e,	0x00,	0x00,	0x00}, // char # 138
	{0x00,	0x24,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 139
	{0x18,	0x24,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 140
	{0x10,	0x08,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 141
	{0x24,	0x00,	0x18,	0x18,	0x24,	0x24,	0x24,	0x7e,	0x42,	0x81,	0x00,	0x00,	0x00}, // char # 142
	{0x10,	0x28,	0x10,	0x28,	0x28,	0x24,	0x44,	0x7e,	0x42,	0x81,	0x00,	0x00,	0x00}, // char # 143
	{0x08,	0x10,	0x7e,	0x40,	0x40,	0x40,	0x7c,	0x40,	0x40,	0x7e,	0x00,	0x00,	0x00}, // char # 144
	{0x00,	0x00,	0x00,	0xfc,	0x12,	0x12,	0x7e,	0x90,	0x90,	0x6e,	0x00,	0x00,	0x00}, // char # 145
	{0x00,	0x00,	0x0f,	0x18,	0x18,	0x28,	0x2e,	0x78,	0x48,	0x8f,	0x00,	0x00,	0x00}, // char # 146
	{0x18,	0x24,	0x00,	0x3c,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 147
	{0x00,	0x24,	0x00,	0x3c,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 148
	{0x20,	0x10,	0x00,	0x3c,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 149
	{0x18,	0x24,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 150
	{0x20,	0x10,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 151
	{0x00,	0x24,	0x00,	0x81,	0x42,	0x42,	0x24,	0x24,	0x18,	0x18,	0x10,	0x30,	0xe0}, // char # 152
	{0x24,	0x00,	0x38,	0x44,	0x82,	0x82,	0x82,	0x82,	0x44,	0x38,	0x00,	0x00,	0x00}, // char # 153
	{0x24,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 154
	{0x00,	0x08,	0x1c,	0x28,	0x48,	0x48,	0x48,	0x68,	0x1c,	0x08,	0x00,	0x00,	0x00}, // char # 155
	{0x00,	0x0e,	0x10,	0x10,	0x10,	0x38,	0x10,	0x10,	0x20,	0x3e,	0x00,	0x00,	0x00}, // char # 156
	{0x00,	0x81,	0x42,	0x24,	0x18,	0x7c,	0x10,	0x7c,	0x10,	0x10,	0x00,	0x00,	0x00}, // char # 157
	{0x00,	0xe0,	0x90,	0x90,	0xe0,	0x96,	0xbc,	0x94,	0x92,	0x9e,	0x00,	0x00,	0x00}, // char # 158
	{0x0e,	0x10,	0x10,	0x3c,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xe0}, // char # 159
	{0x08,	0x10,	0x00,	0x38,	0x04,	0x04,	0x3c,	0x44,	0x44,	0x3e,	0x00,	0x00,	0x00}, // char # 160
	{0x08,	0x10,	0x00,	0x78,	0x08,	0x08,	0x08,	0x08,	0x08,	0x08,	0x00,	0x00,	0x00}, // char # 161
	{0x08,	0x10,	0x00,	0x3c,	0x42,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 162
	{0x08,	0x10,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x46,	0x3a,	0x00,	0x00,	0x00}, // char # 163
	{0x14,	0x28,	0x00,	0x5c,	0x62,	0x42,	0x42,	0x42,	0x42,	0x42,	0x00,	0x00,	0x00}, // char # 164
	{0x14,	0x28,	0x42,	0x62,	0x52,	0x52,	0x4a,	0x4a,	0x46,	0x42,	0x00,	0x00,	0x00}, // char # 165
	{0x00,	0x78,	0x08,	0x38,	0x48,	0x7c,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 166
	{0x00,	0x38,	0x44,	0x44,	0x44,	0x38,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 167
	{0x00,	0x00,	0x00,	0x08,	0x00,	0x00,	0x08,	0x10,	0x20,	0x40,	0x42,	0x3e,	0x00}, // char # 168
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x7e,	0x40,	0x40,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 169
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xfe,	0x02,	0x02,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 170
	{0x00,	0xc4,	0x48,	0x48,	0x50,	0x37,	0x21,	0x43,	0x44,	0x87,	0x00,	0x00,	0x00}, // char # 171
	{0x00,	0xc4,	0x48,	0x48,	0x50,	0x22,	0x26,	0x4a,	0x4f,	0x82,	0x00,	0x00,	0x00}, // char # 172
	{0x00,	0x00,	0x00,	0x10,	0x00,	0x00,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x00}, // char # 173
	{0x00,	0x00,	0x00,	0x00,	0x12,	0x24,	0x48,	0x24,	0x12,	0x00,	0x00,	0x00,	0x00}, // char # 174
	{0x00,	0x00,	0x00,	0x00,	0x48,	0x24,	0x12,	0x24,	0x48,	0x00,	0x00,	0x00,	0x00}, // char # 175
	{0x94,	0x00,	0x00,	0x94,	0x00,	0x94,	0x00,	0x00,	0x94,	0x00,	0x94,	0x00,	0x00}, // char # 176
	{0x49,	0x94,	0x00,	0x49,	0x94,	0x49,	0x00,	0x94,	0x49,	0x94,	0x49,	0x00,	0x94}, // char # 177
	{0xff,	0x94,	0x94,	0xff,	0x94,	0xff,	0x94,	0x94,	0xff,	0x94,	0xff,	0x94,	0x94}, // char # 178
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 179
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xf0,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 180
	{0x10,	0x10,	0x10,	0x10,	0x10,	0xf0,	0x10,	0xf0,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 181
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0xf4,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 182
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xfc,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 183
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xf0,	0x10,	0xf0,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 184
	{0x14,	0x14,	0x14,	0x14,	0x14,	0xf4,	0x04,	0xf4,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 185
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 186
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xfc,	0x04,	0xf4,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 187
	{0x14,	0x14,	0x14,	0x14,	0x14,	0xf4,	0x04,	0xfc,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 188
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0xfc,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 189
	{0x10,	0x10,	0x10,	0x10,	0x10,	0xf0,	0x10,	0xf0,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 190
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xf0,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 191
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x1f,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 192
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 193
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 194
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x1f,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 195
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 196
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xff,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 197
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x1f,	0x10,	0x1f,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 198
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x17,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 199
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x17,	0x10,	0x1f,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 200
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x1f,	0x10,	0x17,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 201
	{0x14,	0x14,	0x14,	0x14,	0x14,	0xf7,	0x00,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 202
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0xf7,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 203
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x17,	0x10,	0x17,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 204
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 205
	{0x14,	0x14,	0x14,	0x14,	0x14,	0xf7,	0x00,	0xf7,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 206
	{0x10,	0x10,	0x10,	0x10,	0x10,	0xff,	0x00,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 207
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 208
	{0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0xff,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 209
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 210
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0x1f,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 211
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x1f,	0x10,	0x1f,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 212
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x1f,	0x10,	0x1f,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 213
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x1f,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 214
	{0x14,	0x14,	0x14,	0x14,	0x14,	0x14,	0xff,	0x14,	0x14,	0x14,	0x14,	0x14,	0x14}, // char # 215
	{0x10,	0x10,	0x10,	0x10,	0x10,	0xff,	0x10,	0xff,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 216
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0xf0,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 217
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x1f,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 218
	{0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff}, // char # 219
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff}, // char # 220
	{0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0,	0xf0}, // char # 221
	{0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f,	0x0f}, // char # 222
	{0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 223
	{0x00,	0x00,	0x00,	0x31,	0x49,	0x86,	0x84,	0x84,	0x8a,	0x71,	0x00,	0x00,	0x00}, // char # 224
	{0x38,	0x48,	0x48,	0x50,	0x50,	0x58,	0x44,	0x42,	0x42,	0x5c,	0x00,	0x00,	0x00}, // char # 225
	{0x00,	0x00,	0x3f,	0x20,	0x20,	0x20,	0x20,	0x20,	0x20,	0x20,	0x00,	0x00,	0x00}, // char # 226
	{0x00,	0x00,	0x00,	0x7f,	0x24,	0x24,	0x24,	0x24,	0x24,	0x24,	0x00,	0x00,	0x00}, // char # 227
	{0x00,	0x00,	0xff,	0x40,	0x20,	0x10,	0x10,	0x20,	0x40,	0xff,	0x00,	0x00,	0x00}, // char # 228
	{0x00,	0x00,	0x00,	0x7f,	0x84,	0x84,	0x84,	0x84,	0x84,	0x78,	0x00,	0x00,	0x00}, // char # 229
	{0x00,	0x00,	0x00,	0x42,	0x42,	0x42,	0x42,	0x42,	0x66,	0x5a,	0x40,	0x40,	0x40}, // char # 230
	{0x00,	0x00,	0x00,	0xfe,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x00,	0x00,	0x00}, // char # 231
	{0x00,	0x00,	0x10,	0x7c,	0x92,	0x92,	0x92,	0x92,	0x7c,	0x10,	0x00,	0x00,	0x00}, // char # 232
	{0x00,	0x00,	0x38,	0x44,	0x82,	0xba,	0x82,	0x82,	0x44,	0x38,	0x00,	0x00,	0x00}, // char # 233
	{0x00,	0x00,	0x7c,	0xc6,	0x82,	0x82,	0x82,	0x84,	0x44,	0xee,	0x00,	0x00,	0x00}, // char # 234
	{0x38,	0x40,	0x60,	0x18,	0x24,	0x42,	0x42,	0x42,	0x42,	0x3c,	0x00,	0x00,	0x00}, // char # 235
	{0x00,	0x00,	0x00,	0x00,	0x66,	0x99,	0x99,	0x99,	0x66,	0x00,	0x00,	0x00,	0x00}, // char # 236
	{0x10,	0x10,	0x10,	0x7c,	0x92,	0x91,	0x91,	0x91,	0x92,	0x7c,	0x10,	0x10,	0x10}, // char # 237
	{0x00,	0x00,	0x00,	0x1e,	0x20,	0x40,	0x7c,	0x40,	0x60,	0x1e,	0x00,	0x00,	0x00}, // char # 238
	{0x00,	0x00,	0x00,	0x38,	0x44,	0x82,	0x82,	0x82,	0x82,	0x82,	0x00,	0x00,	0x00}, // char # 239
	{0x00,	0x00,	0x00,	0x00,	0x7e,	0x00,	0x7e,	0x00,	0x7e,	0x00,	0x00,	0x00,	0x00}, // char # 240
	{0x00,	0x00,	0x00,	0x10,	0x10,	0xfe,	0x10,	0x10,	0x00,	0xfe,	0x00,	0x00,	0x00}, // char # 241
	{0x00,	0x00,	0x40,	0x30,	0x08,	0x06,	0x08,	0x30,	0x40,	0x00,	0x7e,	0x00,	0x00}, // char # 242
	{0x00,	0x00,	0x02,	0x0c,	0x10,	0x60,	0x10,	0x0c,	0x02,	0x00,	0x7e,	0x00,	0x00}, // char # 243
	{0x0c,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10}, // char # 244
	{0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x10,	0x60}, // char # 245
	{0x00,	0x00,	0x00,	0x10,	0x00,	0x00,	0xfe,	0x00,	0x00,	0x10,	0x00,	0x00,	0x00}, // char # 246
	{0x00,	0x00,	0x00,	0x00,	0x72,	0x4e,	0x00,	0x72,	0x4e,	0x00,	0x00,	0x00,	0x00}, // char # 247
	{0x00,	0x10,	0x28,	0x10,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 248
	{0x00,	0x00,	0x00,	0x00,	0x18,	0x3c,	0x3c,	0x18,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 249
	{0x00,	0x00,	0x00,	0x00,	0x18,	0x3c,	0x3c,	0x18,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 250
	{0x01,	0x01,	0x02,	0x02,	0x02,	0x04,	0x04,	0xc4,	0x28,	0x28,	0x18,	0x10,	0x00}, // char # 251
	{0x00,	0x3c,	0x24,	0x24,	0x24,	0x24,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 252
	{0x00,	0x3c,	0x04,	0x18,	0x3c,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00}, // char # 253
	{0x00,	0x00,	0x00,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0x00,	0x00,	0x00}, // char # 254
	{0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00} // char # 255
}; 



void character(uint16_t x, uint16_t y, char c, Color clr, uint16_t size)
{
    const unsigned char* glyph = font8x8_basic[(uint8_t)c];

    for (int row = 0; row < 13; ++row) {
        unsigned char byte = glyph[row];
        for (int bit = 0; bit < 8; ++bit) {
            if (byte & (1 << (7 - bit))) {  
                int pixel_x = x + bit;
                int pixel_y = y + row;
                if (pixel_x >= 0 && pixel_y >= 0) {
                    pixel(pixel_x, pixel_y, clr);
                }
            }
        }
    }
}
void print_string(uint16_t x, uint16_t y, const char* str, Color clr, uint16_t size)
{
    uint16_t cursor_x = x;
    uint16_t cursor_y = y;

    while (*str) {
        character(cursor_x, cursor_y, *str, clr, size);
        cursor_x += 8 * size;  
        str++;
    }
}
