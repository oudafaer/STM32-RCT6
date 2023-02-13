#ifndef __LCD_H
#define __LCD_H		
#include "stm32f10x.h"

#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����

//������ɫ
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
#define BROWN           0XBC40  //��ɫ
#define BRRED           0XFC07  //�غ�ɫ
#define GRAY            0X8430  //��ɫ

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800			//ͼƬ���ݴ�С


/**********SPI���ŷ��䣬����TFT��������ʵ������޸�*********/

#define SPI_SCK_0  GPIOB->BRR=0X0020       // ����sck�ӿڵ�PB5   ����
#define SPI_SCK_1  GPIOB->BSRR=0X0020       //��λ
#define SPI_SDA_0  GPIOB->BRR=0X0040       // ����SDA�ӿڵ�PB6
#define SPI_SDA_1  GPIOB->BSRR=0X0040
#define SPI_RST_0  GPIOB->BRR=0X0080       // ����RST�ӿڵ�PB7
#define SPI_RST_1  GPIOB->BSRR=0X0080
#define SPI_DC_0   GPIOB->BRR=0X0100      // ����DC�ӿڵ�PB8
#define SPI_DC_1   GPIOB->BSRR=0X0100
#define SPI_BLK_0   GPIOB->BRR=0X0200    // ����/WR ��CS�ӿڵ�PB9
#define SPI_BLK_1   GPIOB->BSRR=0X0200

//GUI��ɫ

#define DARKBLUE        0X01CF  //����ɫ
#define LIGHTBLUE       0X7D7C  //ǳ��ɫ  
#define GRAYBLUE        0X5458  //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN      0X841F  //ǳ��ɫ 
#define LGRAY           0XC618  //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE       0XA651  //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12  //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

void SYS_init(unsigned char PLL);
void IO_init(void);
void Delay_us(unsigned int _us_time);
void Delay_ms(unsigned int _ms_time);
void TFT_full(unsigned int color);
void TFT_clear(void);

void LCD_Writ_Bus(uint8_t dat);//ʵ�ʷ���
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��


void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//ָ�����������ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//��ָ��λ�û�һ������
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//��ָ��λ�û�һ��Բ

//���ں��ֱȽ��鷳����ֱ��ȫ��ע���ˣ����ԶԱȹٷ����̣��������Ҫ���ϣ��ܼ򵥡�
// void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ���ִ�
// void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����12x12����
// void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����16x16����
// void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����24x24����
// void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����32x32����

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾһ���ַ�
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ�ַ���
uint32_t mypow(uint8_t m,uint8_t n);//����
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��������
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��λС������
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//��ʾͼƬ



#endif












