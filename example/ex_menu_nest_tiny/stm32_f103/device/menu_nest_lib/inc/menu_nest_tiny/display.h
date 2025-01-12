#ifndef DISPLAY_H
#define DISPLAY_H

#include "stdint.h"

// 请按照要求修改以下宏定义
#define CHAR_WIDTH 7
#define CHAR_HEIGHT 10

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// 请直接写数字。因为这个宏会被字符串化为"20"，所以不要写成(DISPLAY_WIDTH / CHAR_WIDTH )这种形式
#define LINE_MAX_CHAR_NUM 18

// 检查你的显示库是否是需要手动刷新的。如果需要手动刷新，请修改为1，并完成刷新函数。如果为直接在屏幕上更改的，请修改为0。
#define DISPLAY_NEED_UPDATE (1)

#if DISPLAY_NEED_UPDATE
void display_update();
#endif

//在y行顶格显示一行文字。带有空格填充，并且最多显示LINE_MAX_CHAR_NUM个字符
void display_line_text(uint16_t y,const char * str);

//清屏
void display_clear();

// 在y行绘制一条水平线，color为1表示前景色，0表示背景色
void display_draw_waterline(uint16_t y, uint8_t color);

// 在x列绘制一条垂直线，color为1表示前景色，0表示背景色
void display_draw_verticalline(uint16_t x, uint8_t color);

#endif //DISPLAY_H