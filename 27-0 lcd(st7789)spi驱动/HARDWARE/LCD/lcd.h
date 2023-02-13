#ifndef __LCD_H
#define __LCD_H		
#include "stm32f10x.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

//画笔颜色
#define WHITE           0xFFFF
#define BLACK           0x0000
#define BLUE            0x001F
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0
#define BROWN           0XBC40  //棕色
#define BRRED           0XFC07  //棕红色
#define GRAY            0X8430  //灰色

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800			//图片数据大小


/**********SPI引脚分配，连接TFT屏，更具实际情况修改*********/

#define SPI_SCK_0  GPIOB->BRR=0X0020       // 设置sck接口到PB5   清零
#define SPI_SCK_1  GPIOB->BSRR=0X0020       //置位
#define SPI_SDA_0  GPIOB->BRR=0X0040       // 设置SDA接口到PB6
#define SPI_SDA_1  GPIOB->BSRR=0X0040
#define SPI_RST_0  GPIOB->BRR=0X0080       // 设置RST接口到PB7
#define SPI_RST_1  GPIOB->BSRR=0X0080
#define SPI_DC_0   GPIOB->BRR=0X0100      // 设置DC接口到PB8
#define SPI_DC_1   GPIOB->BSRR=0X0100
#define SPI_BLK_0   GPIOB->BRR=0X0200    // 设置/WR 或CS接口到PB9
#define SPI_BLK_1   GPIOB->BSRR=0X0200

//GUI颜色

#define DARKBLUE        0X01CF  //深蓝色
#define LIGHTBLUE       0X7D7C  //浅蓝色  
#define GRAYBLUE        0X5458  //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN      0X841F  //浅绿色 
#define LGRAY           0XC618  //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE       0XA651  //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12  //浅棕蓝色(选择条目的反色)

void SYS_init(unsigned char PLL);
void IO_init(void);
void Delay_us(unsigned int _us_time);
void Delay_ms(unsigned int _ms_time);
void TFT_full(unsigned int color);
void TFT_clear(void);

void LCD_Writ_Bus(uint8_t dat);//实际发送
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化


void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//指定区域填充颜色
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//在指定位置画一个点
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//在指定位置画一条线
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//在指定位置画一个矩形
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//在指定位置画一个圆

//由于汉字比较麻烦，就直接全部注释了，可以对比官方例程，如果有需要加上，很简单。
// void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示汉字串
// void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个12x12汉字
// void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个16x16汉字
// void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个24x24汉字
// void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个32x32汉字

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示一个字符
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示字符串
uint32_t mypow(uint8_t m,uint8_t n);//求幂
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示整数变量
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示两位小数变量
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//显示图片



#endif













