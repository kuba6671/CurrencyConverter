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
	float currency[20] = { 4.58, 3.92, 5.34, 4.28, 1.3, 0.14, 3.58, 0.6, 0.17,
	   0.92, 2.34, 0.45, 0.49, 0.25, 0.72, 0.92, 0.05, 5.27, 1.21, 0.33 };


	TRISC = 0xF0;        
	TRISB = 0x00;        
	TRISD6 = 0;          
	TRISD7 = 0;          
	__delay_ms(400);

	int k2 = 0, k1 = 0;
	short round;
	char mode, format;
	char key[4];
	memset(key, 0, 4);
	char ke[4];
	memset(ke, 0, 4);
	char integ[4];
	memset(integ, 0, 4);
	char frac[4];
	memset(frac, 0, 4);
	char edit_curr[8];
	memset(edit_curr, 0, 8);
	float new_curr=0.0;
	int i = 0;
	float res = 0.0;
	lcdinit();        //Initializing Lcd

	while (1) {
		disp_str("1=Edit currency", 1);
	        lcdcmd(0xC0);
	        disp_str("2=Calculator ", 1);
		mode = scan_key();
	        lcdcmd(0x01);
		if(mode == '2'){
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
		format = scan_key();
		round = atoi(format);
		lcdcmd(0x01);    //Clear Lcd

		disp_str("***RESULT***", 1);

		lcdcmd(0xC0);   //Jump to second Line of Lcd
		disp_num(k2);
		disp_str("PLN", 1);
		lcddata('=');
		
		res = division(k2, currency[k1]);
	        disp_res(res,round);

		switch (k1)
		{
		case 0:
			disp_str("EUR", 0);
			break;
		case 1:
			disp_str("USD", 0);
			break;
		case 2:
			disp_str("GBP", 0);
			break;
		case 3:
			disp_str("CHF", 0);
			break;
		case 4:
			disp_str("HUF", 0);
			break;
		case 5:
			disp_str("UAH", 0);
			break;
		case 6:
			disp_str("JPY", 0);
			break;
		case 7:
			disp_str("CNY", 0);
			break;
		case 8:
			disp_str("CZK", 0);
			break;
		case 9:
			disp_str("RON", 0);
			break;
		case 10:
			disp_str("BGN", 0);
			break;
		case 11:
			disp_str("TRY", 0);
			break;
		case 12:
			disp_str("ARS", 0);
			break;
		case 13:
			disp_str("ZAR", 0);
			break;
		case 14:
			disp_str("BRL", 0);
			break;
		case 15:
			disp_str("MYR", 0);
			break;
		case 16:
			disp_str("RUB", 0);
			break;
		case 17:
			disp_str("INR", 0);
			break;
		case 18:
			disp_str("ILS", 0);
			break;
		case 19:
			disp_str("KRW", 0);
			break;
		}
	     }
	     else if(mode == '1'){
		disp_str("CURRENCY= ", 1);
		i = 0;
		do {
			key[i] = scan_key();
			i++;
		} while (key[i - 1] != '=');
		k1 = atoi(key);
		memset(key, 0, 4);
		lcdcmd(0x01);    //Clear Lcd
		
		disp_str("ENTER INTGER", 1);
		lcdcmd(0xC0);
		disp_str("PART ", 1);
		i = 0;
		do {
			integ[i] = scan_key();
			i++;
		} while (integ[i - 1] != '=');
		lcdcmd(0x01);    //Clear Lcd
		
		disp_str("ENTER FRACTION", 1);
		lcdcmd(0xC0);
		disp_str("PART ", 1);
		i = 0;
		do {
			frac[i] = scan_key();
			i++;
		} while (frac[i - 1] != '=');
		lcdcmd(0x01);    //Clear Lcd
		i=0;

		for(i=0;i<4;i++){
		   if(integ[i]=='='){
			integ[i]=NULL;
		      }
		}
		strncat(edit_curr,integ,3);
		strncat(edit_curr,".",1);
		strncat(edit_curr,frac,3);
		
		new_curr = atof(edit_curr);
		
		currency[k1] = new_curr;
		i=0;
		
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

void disp_num(float num)            
{
	unsigned char UnitDigit;  
	unsigned char TenthDigit;  
	unsigned char decimal;  
	int j = 0, numb;

	j = (int)(num * 10);
	numb = (int)num;

	if (numb < 0)
	{
		numb = -1 * numb;  
		lcddata('-');	
	}

	TenthDigit = (numb / 10);	         

	if (TenthDigit != 0)	       
		lcddata(TenthDigit + 0x30);	

	UnitDigit = numb - (TenthDigit * 10);

	lcddata(UnitDigit + 0x30);	 
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
