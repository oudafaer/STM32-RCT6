#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"
#include "delay.h"


void SYS_init(unsigned char PLL)
{
	
		 
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 	  
  	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION
	
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	while(((RCC->CFGR>>2)& 0x03 )!=0x00); 	
	RCC->CIR = 0x00000000;     //�ر������ж�		 
	//����������				  
  
//	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
	
 	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(((RCC->CR>>17)&0x00000001)==0);//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//����2����λ
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(((RCC->CFGR>>2)&0x03)!=0x02);   //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	
	
}

void IO_init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ�� 
	GPIOB->CRL&=0X000FFFFF;				//��B567������Ϊͨ���������,���50MH
	GPIOB->CRL|=0X33300000;				
	GPIOB->CRH&=0XFFFFFF00;				//��B89������Ϊͨ���������,���50MH
	GPIOB->CRH|=0X00000033;
	GPIOB->ODR=0XFFFF;
}
//��ʱ����
void Delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
  }
}
void Delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }
/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(unsigned  char byte)				//��Һ����дһ��8λ����
{
  
  unsigned char counter;
 
  for(counter=0;counter<8;counter++)
  { 
    SPI_SCK_0;		  
    if((byte&0x80)==0)
    {
      SPI_SDA_0;
    }
    else SPI_SDA_1;
    byte=byte<<1;	
    SPI_SCK_1;		
  }		
	SPI_SCK_0;
}
void LCD_WR_DATA8(uint8_t dat)
{
    SPI_DC_1;//д����
	SPI_SCK_0;	
	LCD_Writ_Bus(dat);
}
/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
    SPI_DC_1;//д����
	SPI_SCK_0;
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}

void LCD_WR_REG(unsigned char o_command)
{
	SPI_DC_0;
	SPI_SCK_0;	
    LCD_Writ_Bus(o_command);
}

void TFT_clear(void)
{
    unsigned int ROW,column;
  LCD_WR_REG(0x2a);     //Column address set
  LCD_WR_DATA8(0x00);    //start column
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x00);    //end column
  LCD_WR_DATA8(0xF0);

  LCD_WR_REG(0x2b);     //Row address set
  LCD_WR_DATA8(0x00);    //start row
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x00);    //end row
  LCD_WR_DATA8(0xF0);
    LCD_WR_REG(0x2C);     //Memory write
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
      { 
    
          for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
            {
              
				LCD_WR_DATA8(0xFF);
				LCD_WR_DATA8(0xFF);
            }
      }
  }
 void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+24);
		LCD_WR_DATA(x2+24);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+24);
		LCD_WR_DATA(y2+24);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+24);
		LCD_WR_DATA(y2+24);
		LCD_WR_REG(0x2c);//������д
	}
}
void TFT_full(unsigned int color)
  {
    unsigned int ROW,column;
    LCD_WR_REG(0x2a);     //Column address set
  LCD_WR_DATA8(0x00);    //start column
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x00);    //end column
  LCD_WR_DATA8(0xF0);

  LCD_WR_REG(0x2b);     //Row address set
  LCD_WR_DATA8(0x00);    //start row
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x00);    //end row
  LCD_WR_DATA8(0xF0);
    LCD_WR_REG(0x2C);     //Memory write
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
      { 
    
  for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop
          {

			  LCD_WR_DATA8(color>>8);
			  LCD_WR_DATA8(color);
          }
      }
  }

void LCD_Init(void)				////ST7789V2
{
	SPI_SCK_1;			//�ر�ע�⣡��
	SPI_RST_0;
	Delay_ms(1000);
	SPI_RST_1;
	Delay_ms(1000);
    LCD_WR_REG(0x11); 			//Sleep Out
	Delay_ms(120);               //DELAY120ms 
	 	  //-----------------------ST7789V Frame rate setting-----------------//
//************************************************
                LCD_WR_REG(0x3A);        //65k mode
                LCD_WR_DATA8(0x05);
                LCD_WR_REG(0xC5); 		//VCOM
                LCD_WR_DATA8(0x1A);
                LCD_WR_REG(0x36);                 // ��Ļ��ʾ��������
                LCD_WR_DATA8(0x00);
                //-------------ST7789V Frame rate setting-----------//
                LCD_WR_REG(0xb2);		//Porch Setting
                LCD_WR_DATA8(0x05);
                LCD_WR_DATA8(0x05);
                LCD_WR_DATA8(0x00);
                LCD_WR_DATA8(0x33);
                LCD_WR_DATA8(0x33);

                LCD_WR_REG(0xb7);			//Gate Control
                LCD_WR_DATA8(0x05);			//12.2v   -10.43v
                //--------------ST7789V Power setting---------------//
                LCD_WR_REG(0xBB);//VCOM
                LCD_WR_DATA8(0x3F);

                LCD_WR_REG(0xC0); //Power control
                LCD_WR_DATA8(0x2c);

                LCD_WR_REG(0xC2);		//VDV and VRH Command Enable
                LCD_WR_DATA8(0x01);

                LCD_WR_REG(0xC3);			//VRH Set
                LCD_WR_DATA8(0x0F);		//4.3+( vcom+vcom offset+vdv)

                LCD_WR_REG(0xC4);			//VDV Set
                LCD_WR_DATA8(0x20);				//0v

                LCD_WR_REG(0xC6);				//Frame Rate Control in Normal Mode
                LCD_WR_DATA8(0X01);			//111Hz

                LCD_WR_REG(0xd0);				//Power Control 1
                LCD_WR_DATA8(0xa4);
                LCD_WR_DATA8(0xa1);

                LCD_WR_REG(0xE8);				//Power Control 1
                LCD_WR_DATA8(0x03);

                LCD_WR_REG(0xE9);				//Equalize time control
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x08);
                //---------------ST7789V gamma setting-------------//
                LCD_WR_REG(0xE0); //Set Gamma
                LCD_WR_DATA8(0xD0);
                LCD_WR_DATA8(0x05);
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x08);
                LCD_WR_DATA8(0x14);
                LCD_WR_DATA8(0x28);
                LCD_WR_DATA8(0x33);
                LCD_WR_DATA8(0x3F);
                LCD_WR_DATA8(0x07);
                LCD_WR_DATA8(0x13);
                LCD_WR_DATA8(0x14);
                LCD_WR_DATA8(0x28);
                LCD_WR_DATA8(0x30);
                 
                LCD_WR_REG(0XE1); //Set Gamma
                LCD_WR_DATA8(0xD0);
                LCD_WR_DATA8(0x05);
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x09);
                LCD_WR_DATA8(0x08);
                LCD_WR_DATA8(0x03);
                LCD_WR_DATA8(0x24);
                LCD_WR_DATA8(0x32);
                LCD_WR_DATA8(0x32);
                LCD_WR_DATA8(0x3B);
                LCD_WR_DATA8(0x14);
                LCD_WR_DATA8(0x13);
                LCD_WR_DATA8(0x28);
                LCD_WR_DATA8(0x2F);

                LCD_WR_REG(0x21); 		//����
               
                LCD_WR_REG(0x29);         //������ʾ 

}
  
/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   ���ε���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
                color   Բ����ɫ
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

// /******************************************************************************
//       ����˵������ʾ���ִ�
//       ������ݣ�x,y��ʾ����
//                 *s Ҫ��ʾ�ĺ��ִ�
//                 fc �ֵ���ɫ
//                 bc �ֵı���ɫ
//                 sizey �ֺ� ��ѡ 16 24 32
//                 mode:  0�ǵ���ģʽ  1����ģʽ
//       ����ֵ��  ��
// ******************************************************************************/
// void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
// {
// 	while(*s!=0)
// 	{
// 		if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
// 		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
// 		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
// 		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
// 		else return;
// 		s+=2;
// 		x+=sizey;
// 	}
// }

// /******************************************************************************
//       ����˵������ʾ����12x12����
//       ������ݣ�x,y��ʾ����
//                 *s Ҫ��ʾ�ĺ���
//                 fc �ֵ���ɫ
//                 bc �ֵı���ɫ
//                 sizey �ֺ�
//                 mode:  0�ǵ���ģʽ  1����ģʽ
//       ����ֵ��  ��
// ******************************************************************************/
// void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
// {
// 	uint8_t i,j,m=0;
// 	uint16_t k;
// 	uint16_t HZnum;//������Ŀ
// 	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
// 	uint16_t x0=x;
// 	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	                         
// 	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//ͳ�ƺ�����Ŀ
// 	for(k=0;k<HZnum;k++) 
// 	{
// 		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
// 		{ 	
// 			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
// 			for(i=0;i<TypefaceNum;i++)
// 			{
// 				for(j=0;j<8;j++)
// 				{	
// 					if(!mode)//�ǵ��ӷ�ʽ
// 					{
// 						if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
// 						else LCD_WR_DATA(bc);
// 						m++;
// 						if(m%sizey==0)
// 						{
// 							m=0;
// 							break;
// 						}
// 					}
// 					else//���ӷ�ʽ
// 					{
// 						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
// 						x++;
// 						if((x-x0)==sizey)
// 						{
// 							x=x0;
// 							y++;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}				  	
// 		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 	}
// } 

// /******************************************************************************
//       ����˵������ʾ����16x16����
//       ������ݣ�x,y��ʾ����
//                 *s Ҫ��ʾ�ĺ���
//                 fc �ֵ���ɫ
//                 bc �ֵı���ɫ
//                 sizey �ֺ�
//                 mode:  0�ǵ���ģʽ  1����ģʽ
//       ����ֵ��  ��
// ******************************************************************************/
// void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
// {
// 	uint8_t i,j,m=0;
// 	uint16_t k;
// 	uint16_t HZnum;//������Ŀ
// 	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
// 	uint16_t x0=x;
//   TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
// 	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//ͳ�ƺ�����Ŀ
// 	for(k=0;k<HZnum;k++) 
// 	{
// 		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
// 		{ 	
// 			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
// 			for(i=0;i<TypefaceNum;i++)
// 			{
// 				for(j=0;j<8;j++)
// 				{	
// 					if(!mode)//�ǵ��ӷ�ʽ
// 					{
// 						if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
// 						else LCD_WR_DATA(bc);
// 						m++;
// 						if(m%sizey==0)
// 						{
// 							m=0;
// 							break;
// 						}
// 					}
// 					else//���ӷ�ʽ
// 					{
// 						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
// 						x++;
// 						if((x-x0)==sizey)
// 						{
// 							x=x0;
// 							y++;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}				  	
// 		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 	}
// } 


// /******************************************************************************
//       ����˵������ʾ����24x24����
//       ������ݣ�x,y��ʾ����
//                 *s Ҫ��ʾ�ĺ���
//                 fc �ֵ���ɫ
//                 bc �ֵı���ɫ
//                 sizey �ֺ�
//                 mode:  0�ǵ���ģʽ  1����ģʽ
//       ����ֵ��  ��
// ******************************************************************************/
// void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
// {
// 	uint8_t i,j,m=0;
// 	uint16_t k;
// 	uint16_t HZnum;//������Ŀ
// 	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
// 	uint16_t x0=x;
// 	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
// 	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
// 	for(k=0;k<HZnum;k++) 
// 	{
// 		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
// 		{ 	
// 			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
// 			for(i=0;i<TypefaceNum;i++)
// 			{
// 				for(j=0;j<8;j++)
// 				{	
// 					if(!mode)//�ǵ��ӷ�ʽ
// 					{
// 						if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
// 						else LCD_WR_DATA(bc);
// 						m++;
// 						if(m%sizey==0)
// 						{
// 							m=0;
// 							break;
// 						}
// 					}
// 					else//���ӷ�ʽ
// 					{
// 						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
// 						x++;
// 						if((x-x0)==sizey)
// 						{
// 							x=x0;
// 							y++;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}				  	
// 		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 	}
// } 

// /******************************************************************************
//       ����˵������ʾ����32x32����
//       ������ݣ�x,y��ʾ����
//                 *s Ҫ��ʾ�ĺ���
//                 fc �ֵ���ɫ
//                 bc �ֵı���ɫ
//                 sizey �ֺ�
//                 mode:  0�ǵ���ģʽ  1����ģʽ
//       ����ֵ��  ��
// ******************************************************************************/
// void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
// {
// 	uint8_t i,j,m=0;
// 	uint16_t k;
// 	uint16_t HZnum;//������Ŀ
// 	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
// 	uint16_t x0=x;
// 	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
// 	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//ͳ�ƺ�����Ŀ
// 	for(k=0;k<HZnum;k++) 
// 	{
// 		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
// 		{ 	
// 			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
// 			for(i=0;i<TypefaceNum;i++)
// 			{
// 				for(j=0;j<8;j++)
// 				{	
// 					if(!mode)//�ǵ��ӷ�ʽ
// 					{
// 						if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
// 						else LCD_WR_DATA(bc);
// 						m++;
// 						if(m%sizey==0)
// 						{
// 							m=0;
// 							break;
// 						}
// 					}
// 					else//���ӷ�ʽ
// 					{
// 						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
// 						x++;
// 						if((x-x0)==sizey)
// 						{
// 							x=x0;
// 							y++;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}				  	
// 		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 	}
// }


/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ�� 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //����6x12����
		else if(sizey==16)temp=ascii_1608[num][i];		 //����8x16����
		else if(sizey==24)temp=ascii_2412[num][i];		 //����12x24����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//�ǵ���ģʽ
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//����ģʽ
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//��һ����
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


/******************************************************************************
      ����˵������ʾͼƬ
      ������ݣ�x,y�������
                length ͼƬ����
                width  ͼƬ���
                pic[]  ͼƬ����    
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}
