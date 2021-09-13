#include<htc.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XTAL_FREQ 20e6
#define rs RD6
#define en RD7
#define r0 RC0
#define r1 RC1
#define r2 RC2
#define r3 RC3
#define c0 RC4
#define c1 RC5
#define c2 RC6
#define c3 RC7

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void disp_num(float num);
void disp_res(float res,short round);
void disp_str(char disp[], short clear);
void lcdinit();
char scan_key(void);
float division(int k2, float Curr);



void lcdinit() {
	__delay_ms(400);	lcdcmd(0x30);	__delay_ms(400);	lcdcmd(0x30);
	__delay_ms(400);	lcdcmd(0x30);	__delay_ms(400);	lcdcmd(0x38);
	lcdcmd(0x0F);	lcdcmd(0x01);	lcdcmd(0x06);	lcdcmd(0x80);
}

void main(void)
{
	float EURO, DOLAR, FUNT, FRANK, FORINT, HRYWNA, JEN, JUAN, KORONA, LEJ,
		LEW, LIRA, PESO, RAND, REAL, RINGGIT, RUBEL, RUPIA, SZEKEL, WON;

	EURO = 4.58;
	DOLAR = 3.92;
	FUNT = 5.34;
	FRANK = 4.28;
	FORINT = 1.3;
	HRYWNA = 0.14;
	JEN = 3.58;
	JUAN = 0.6;
	KORONA = 0.17;
	LEJ = 0.92;
	LEW = 2.34;
	LIRA = 0.45;
	PESO = 0.49;
	RAND = 0.25;
	REAL = 0.72;
	RINGGIT = 0.92;
	RUBEL = 0.05;
	RUPIA = 5.27;
	SZEKEL = 1.21;
	WON = 0.33;


	TRISC = 0xF0;        //Rows Output, Coulombs Input
	TRISB = 0x00;        //Port-B as Output
	TRISD6 = 0;          //Port-D PIN-6 as Output
	TRISD7 = 0;          //Port-D PIN-7 as Output
	__delay_ms(400);

	int k2 = 0, k1 = 0, round=0;
	char key[4];
	memset(key, 0, 4);
	char ke[4];
	memset(ke, 0, 4);
	char format[3];
	memset(format, 0, 3);
	int i = 0;
	float res = 0.0;
	lcdinit();        //Initializing Lcd

	while (1) {
		disp_str("ENTER VALUE=", 1);
		do {
			ke[i] = scan_key();
			i++;
		} while (ke[i - 1] != '=');
		k2 = atoi(ke);
		lcdcmd(0x01);    //Clear Lcd

		disp_str("CURRENCY= ", 1);
		i = 0;
		do {
			key[i] = scan_key();
			i++;
		} while (key[i - 1] != '=');
		k1 = atoi(key);
		lcdcmd(0x01);    //Clear Lcd
		
		disp_str("ROUND= ", 1);
		i = 0;
		do {
			format[i] = scan_key();
			i++;
		} while (key[i - 1] != '=');
		round = atoi(format);
		lcdcmd(0x01);    //Clear Lcd

		//lcdcmd(0x82);     //Start displying data on lcd at position Row=1 Coulomb=3

		disp_str("***RESULT***", 1);

		lcdcmd(0xC0);   //Jump to second Line of Lcd
		disp_num(k2);
		disp_str("PLN", 1);
		lcddata('=');

		switch (k1)
		{
		case 0:
			res = division(k2, EURO);
			disp_res(res,round);
			disp_str("EUR", 0);
			break;
		case 1:
			res = division(k2, DOLAR);
			disp_res(res,round);
			disp_str("USD", 0);
			break;
		case 2:
			res = division(k2, FUNT);
			disp_res(res, round);
			disp_str("GBP", 0);
			break;
		case 3:
			res = division(k2, FRANK);
			disp_res(res, round);
			disp_str("CHF", 0);
			break;
		case 4:
			res = division(k2, FORINT);
			disp_res(res, round);
			disp_str("HUF", 0);
			break;
		case 5:
			res = division(k2, HRYWNA);
			disp_res(res, round);
			disp_str("UAH", 0);
			break;
		case 6:
			res = division(k2, JEN);
			disp_res(res, round);
			disp_str("JPY", 0);
			break;
		case 7:
			res = division(k2, JUAN);
			disp_res(res, round);
			disp_str("CNY", 0);
			break;
		case 8:
			res = division(k2, KORONA);
			disp_res(res, round);
			disp_str("CZK", 0);
			break;
		case 9:
			res = division(k2, LEJ);
			disp_res(res, round);
			disp_str("RON", 0);
			break;
		case 10:
			res = division(k2, LEW);
			disp_res(res, round);
			disp_str("BGN", 0);
			break;
		case 11:
			res = division(k2, LIRA);
			disp_res(res, round);
			disp_str("TRY", 0);
			break;
		case 12:
			res = division(k2, PESO);
			disp_res(res, round);
			disp_str("ARS", 0);
			break;
		case 13:
			res = division(k2, RAND);
			disp_res(res, round);
			disp_str("ZAR", 0);
			break;
		case 14:
			res = division(k2, REAL);
			disp_res(res, round);
			disp_str("BRL", 0);
			break;
		case 15:
			res = division(k2, RINGGIT);
			disp_res(res, round);
			disp_str("MYR", 0);
			break;
		case 16:
			res = division(k2, RUBEL);
			disp_res(res, round);
			disp_str("RUB", 0);
			break;
		case 17:
			res = division(k2, RUPIA);
			disp_res(res, round);
			disp_str("INR", 0);
			break;
		case 18:
			res = division(k2, SZEKEL);
			disp_res(res, round);
			disp_str("ILS", 0);
			break;
		case 19:
			res = division(k2, WON);
			disp_res(res, round);
			disp_str("KRW", 0);
			break;
		}
	}
}

void lcdcmd(unsigned char value)
{
	PORTB = value;
	rs = 0;
	en = 1;
	__delay_ms(100);
	en = 0;
	__delay_ms(100);
}
void lcddata(unsigned char value)
{
	PORTB = value;
	rs = 1;
	en = 1;
	__delay_ms(100);
	en = 0;
	__delay_ms(100);
}



char scan_key()
{
	unsigned char c = 's', d;
	while (c != 'a')
	{
		r0 = 1; r1 = 0; r2 = 0; r3 = 0;
		if (c0 == 1) { lcddata('7'); __delay_ms(500); d = '7'; c = 'a'; }
		if (c1 == 1) { lcddata('8'); __delay_ms(500); d = '8'; c = 'a'; }
		if (c2 == 1) { lcddata('9'); __delay_ms(500); d = '9'; c = 'a'; }
		if (c3 == 1) { lcddata('/'); __delay_ms(500); d = '/'; c = 'a'; }

		r0 = 0; r1 = 1; r2 = 0; r3 = 0;

		if (c0 == 1) { lcddata('4'); __delay_ms(500); d = '4'; c = 'a'; }
		if (c1 == 1) { lcddata('5'); __delay_ms(500); d = '5'; c = 'a'; }
		if (c2 == 1) { lcddata('6'); __delay_ms(500); d = '6'; c = 'a'; }
		if (c3 == 1) { lcddata('*'); __delay_ms(500); d = '*'; c = 'a'; }

		r0 = 0; r1 = 0; r2 = 1; r3 = 0;

		if (c0 == 1) { lcddata('1'); __delay_ms(500); d = '1'; c = 'a'; }
		if (c1 == 1) { lcddata('2'); __delay_ms(500); d = '2'; c = 'a'; }
		if (c2 == 1) { lcddata('3'); __delay_ms(500); d = '3'; c = 'a'; }
		if (c3 == 1) { lcddata('-'); __delay_ms(500); d = '-'; c = 'a'; }

		r0 = 0; r1 = 0; r2 = 0; r3 = 1;

		if (c1 == 1) { lcddata('0'); __delay_ms(500); d = '0'; c = 'a'; }
		if (c2 == 1) { lcddata('='); __delay_ms(500); d = '='; c = 'a'; }
		if (c3 == 1) { lcddata('+'); __delay_ms(500); d = '+'; c = 'a'; }
	}
	return d;
}

float division(int k2, float Curr) {
	return (float)k2 / Curr;
}

void disp_num(float num)            //displays calculated value on LCD
{
	unsigned char UnitDigit;  //It will contain unit digit of number
	unsigned char TenthDigit;  //It will contain 10th position digit of number
	unsigned char decimal;  //Contains Value after decimal digit 
	int j = 0, numb;

	j = (int)(num * 10);
	numb = (int)num;

	if (numb < 0)
	{
		numb = -1 * numb;  // Make number positive
		lcddata('-');	// Display a negative sign on LCD
	}

	TenthDigit = (numb / 10);	         // Findout Tenth Digit

	if (TenthDigit != 0)	         // If it is zero, then don't display
		lcddata(TenthDigit + 0x30);	 // Make Char of TenthDigit and then display it on LCD

	UnitDigit = numb - (TenthDigit * 10);

	lcddata(UnitDigit + 0x30);	 // Make Char of UnitDigit and then display it on LCD
	lcddata('.');
	decimal = (char)(j % 10);
	lcddata(decimal + 0x30);
	__delay_ms(200);
	//lcdcmd(0x01);
}

void disp_res(float res,short round) {
	short j = 0;
	char disp[8];
	memset(disp, 0, 8);
        if(round ==2){
	   sprintf(disp,"%.2f" , res);
	}
	else if(round == 3){
	   sprintf(disp,"%.3f" , res);
	}
	else if(round == 4){
	   sprintf(disp,"%.4f" , res);
	}
	else if(round == 5){
	   sprintf(disp,"%.5f" , res);
	}
	else{
	   sprintf(disp,"%.2f" , res);
	} 
        
	do {
		lcddata(disp[j]);
		j++;
	} while (disp[j] != '\0');
	__delay_ms(500);
}

void disp_str(char disp[], short clear) {
	int j = 0;
	do {
		lcddata(disp[j]);
		j++;
	} while (disp[j] != '\0');
	__delay_ms(500);
	if (clear == 0) {
		lcdcmd(0x01);
	}
}
