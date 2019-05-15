/* file chua cac ham va dinh nghia chan de su dung lcd */
//cac chan su dung

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define RS_Port GPIOB
#define EN_Port GPIOB
#define D4_Port GPIOB
#define D5_Port GPIOB
#define D6_Port GPIOA
#define D7_Port GPIOA
// neu da khai bao trong main.h thi khong can khai bao lai
/*
#define RS_Pin GPIO_PIN_0
#define RS_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_1
#define EN_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_2
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_3
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_4
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_5
#define D7_GPIO_Port GPIOA
*/
// cac ham su dung
void LCD_Enable();
void LCD_Send4Bit(unsigned char Data);
void LCD_SendCommand(unsigned char command);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);
// dinh nghia cac ham
void LCD_Enable() {
  HAL_GPIO_WritePin(EN_Port,EN_Pin,1);
  HAL_Delay(1);
  HAL_GPIO_WritePin(EN_Port,EN_Pin,0);  
  HAL_Delay(1); 
}

void LCD_Send4Bit(unsigned char Data) {
  HAL_GPIO_WritePin(D4_Port,D4_Pin,Data&0x01);
  HAL_GPIO_WritePin(D5_Port,D5_Pin,(Data>>1)&0x01);
  HAL_GPIO_WritePin(D6_Port,D6_Pin,(Data>>2)&0x01);
  HAL_GPIO_WritePin(D7_Port,D7_Pin,(Data>>3)&0x01); 
}

void LCD_SendCommand(unsigned char command) {
  LCD_Send4Bit(command >>4);
  LCD_Enable();
  LCD_Send4Bit(command);
  LCD_Enable();
}

void LCD_Clear() {
  LCD_SendCommand(0x01);  
  HAL_Delay(1); 
}

void LCD_Init() {
  LCD_Send4Bit(0x00);
  HAL_GPIO_WritePin(RS_Port,RS_Pin,0);
  LCD_Send4Bit(0x03);
  LCD_Enable();
  LCD_Enable();
  LCD_Enable();
  LCD_Send4Bit(0x02);
  LCD_Enable();
  LCD_SendCommand(0x28);
  LCD_SendCommand(0x0C);
  LCD_SendCommand(0x06);
  LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y) {
  unsigned char address;
  if(y==0)
    address=0x80;
  else if(y==1) {
    address=0xc0;
  }
  else if(y==2) {
    address=0x94;
  }
  else
    address=0xd4;
  address+=x;
  LCD_SendCommand(address);
}

void LCD_PutChar(unsigned char Data) {
  HAL_GPIO_WritePin(RS_Port,RS_Pin,1);
  LCD_SendCommand(Data);
  HAL_GPIO_WritePin(RS_Port,RS_Pin,0);
}

void LCD_Puts(char *s) {
  while (*s) {
    LCD_PutChar(*s);
    s++;
  }
}