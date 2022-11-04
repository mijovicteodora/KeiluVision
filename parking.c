#include "display.h"

unsigned char trenutnoStanjeSoftP00 = 1;
unsigned char prethodnoStanjeHardP00 = 1;
unsigned char trenutnoStanjeHardP00 = 1;
unsigned char trenutnoStanjeSoftP00_zaMain = 1;
unsigned char prethodnoStanjeSoftP00_zaMain = 1;

unsigned char trenutnoStanjeSoftP01 = 1;
unsigned char prethodnoStanjeHardP01 = 1;
unsigned char trenutnoStanjeHardP01 = 1;
unsigned char trenutnoStanjeSoftP01_zaMain = 1;
unsigned char prethodnoStanjeSoftP01_zaMain = 1;

unsigned char trenutnoStanjeSoftP02 = 1;
unsigned char prethodnoStanjeHardP02 = 1;
unsigned char trenutnoStanjeHardP02 = 1;
unsigned char trenutnoStanjeSoftP02_zaMain = 1;
unsigned char prethodnoStanjeSoftP02_zaMain = 1;

unsigned char trenutnoStanjeSoftP03 = 1;
unsigned char prethodnoStanjeHardP03 = 1;
unsigned char trenutnoStanjeHardP03 = 1;
unsigned char trenutnoStanjeSoftP03_zaMain = 1;
unsigned char prethodnoStanjeSoftP03_zaMain = 1;

unsigned char brPonavljanjaP00 = 0;
unsigned char brPonavljanjaP01 = 0;
unsigned char brPonavljanjaP02 = 0;
unsigned char brPonavljanjaP03 = 0;

unsigned char* greska = "Greska!\r\n";
unsigned char* greska1 = "Prekoracenje!\r\n";

unsigned char* pok;
unsigned char pok1[8];
unsigned char pok2[8];

unsigned char brojacPrekida1 = 0;
unsigned char status = 0;
char buffer_it = 0; 
char buffer[20];

int i = 0;
int j;

unsigned char slob = 15;

unsigned char ulaz = 0;
unsigned char izlaz = 0;
unsigned char rampa = 0;
unsigned char motor = 0;  

void parsiraj_poruku()
{
	if (buffer[0] == '(' && buffer[1] == 'I' && buffer[2] == 'Z' && buffer[3] == 'L' && buffer[4] == 'A' && buffer[5] == 'Z' && buffer[6] == ')')
	{
		i = 0;

		while(buffer[i+1] != ')')
		{
			i++;
		}
		if(i > 8)
		{
			pok = greska1;
		} 
		else
		{
			i = 0;
			j = 1;

			while(buffer[j] != ')')
			{
				pok1[i] = buffer[j];
				i++;
				j++;
			}

			pok1[i] = '\n';
			pok = pok1;

			izlaz = 1;
		}

		clearDisplay();
		writeLine(pok1);	
	}
	else if (buffer[0] == '(' && buffer[1] == 'U' && buffer[2] == 'L' && buffer[3] == 'A' && buffer[4] == 'Z' && buffer[5] == ')' )
	{
		i = 0;

		while(buffer[i+1] != ')')
		{
			i++;
		}

		if(i > 8)
		{
			pok = greska1;
		} 
		else
		{
			i = 0;
			j = 1;

			while(buffer[j] != ')')
			{
				pok2[i] = buffer[j];
				i++;
				j++;
			}

		    pok2[i] = '\n';
			pok = pok2;

			ulaz = 1;
		}

		//newLine();
		clearDisplay();
		writeLine(pok2);	
	}
	else if (buffer[0] == '(' && buffer[1] == 'S' && buffer[2] == 'T' && buffer[3] == ')')
	{
		i = 0;

		while(buffer[i+1] != ')')
		{
			i++;
		}

		if(i > 8)
		{
			pok = greska1;
		}
		else if (slob > 15 || slob < 0)
		{
			pok = greska;
		}
		else if (slob == 15)
		{
			pok = "S: 15\r\n";
		}
		else if (slob == 14)
		{
			pok = "S: 14\r\n";
		}
		else if (slob == 13)
		{
			pok = "S: 13\r\n";
		}
		else if (slob == 12)
		{
			pok = "S: 12\r\n";
		}
		else if (slob == 11)
		{
			pok = "S: 11\r\n";
		}
		if (slob == 10)
		{
			pok = "S: 10\r\n";
		}
		else if (slob == 9)
		{
			pok = "S: 9\r\n";
		}
		else if (slob == 8)
		{
			pok = "S: 8\r\n";
		}
		else if (slob == 7)
		{
			pok = "S: 7\r\n";
		}
		else if (slob == 6)
		{
			pok = "S: 6\r\n";
		}
		else if (slob == 5)
		{
			pok = "S: 5\r\n";
		}
		else if (slob == 4)
		{
			pok = "S: 4\r\n";
		}
		else if (slob == 3)
		{
			pok = "S: 3\r\n";
		}
		else if (slob == 2)
		{
			pok = "S: 2\r\n";
		}
		else if (slob == 1)
		{
			pok = "S: 1\r\n";
		}
		else if (slob == 0)
		{
			pok = "S: 0\r\n";
		}  

		//newLine();
		clearDisplay();
		writeLine(pok);	
	}
	else if (buffer[0] == '(' && buffer[1] == 'C' && buffer[2] == 'L' && buffer[3] == 'R' && buffer[4] == ')')
	{
		clearDisplay();
		//pok = clr;
	}
	else if (buffer[0] == '(' && buffer[1] == 'I' && buffer[2] == 'N' && buffer[3] == 'I' && buffer[4] == 'T' && buffer[5] == ')')
	{
		initDisplay();
		//pok = init;
	}
	else
	{
		pok = greska;
	} 
	 
	 SBUF = *pok;

	 buffer[0] = '\0';
	 buffer_it = 0;
}

void serijska_interrupt(void) interrupt 4
{
	if(RI)
	{
		char prijem;

		RI = 0;

		prijem = SBUF;

		if (prijem == '(')
		{
			buffer_it = 0;
		}

		buffer[buffer_it] = prijem;

		if (prijem == ')')
		{
			parsiraj_poruku();
		}

		buffer_it = (buffer_it + 1) % 20;
	}

	if (TI)
	{
		TI = 0;

		pok++;

		if (*pok != '\0')
		{
			SBUF = *pok;
		}
	}
}

void prekid_timer1(void) interrupt 3
{	
	
	TH1 = 76;																		  
	TL1 = 1;
	
	brojacPrekida1++;

	if (brojacPrekida1 == 100)
	{	
		brojacPrekida1 = 0;
		status = 1;
	}

	//TASTER0
	trenutnoStanjeHardP00 = P0_0;
	if(prethodnoStanjeHardP00 == trenutnoStanjeHardP00)	 
	{
		brPonavljanjaP00++;
		if(brPonavljanjaP00 > 5-1)
		{
			trenutnoStanjeSoftP00 = trenutnoStanjeHardP00;
			brPonavljanjaP00 = 0;
		}
	}
	else
	{
		brPonavljanjaP00 = 0;
	}

	prethodnoStanjeHardP00 = trenutnoStanjeHardP00;


	//TASTER1
	trenutnoStanjeHardP01 = P0_1;
	if(prethodnoStanjeHardP01 == trenutnoStanjeHardP01)	 
	{
		brPonavljanjaP01++;

		if(brPonavljanjaP01 > 5-1)
		{
			trenutnoStanjeSoftP01 = trenutnoStanjeHardP01;
			brPonavljanjaP01 = 0;
		}
	}
	else
	{
		brPonavljanjaP01 = 0;
	}

	prethodnoStanjeHardP01 = trenutnoStanjeHardP01;


	//TASTER2
	trenutnoStanjeHardP02 = P0_2;
	if(prethodnoStanjeHardP02 == trenutnoStanjeHardP02)	 
	{
		brPonavljanjaP02++;
		if(brPonavljanjaP02 > 5-1)
		{
			trenutnoStanjeSoftP02 = trenutnoStanjeHardP02;
			brPonavljanjaP02 = 0;
		}
	}
	else
	{
		brPonavljanjaP02 = 0;
	}

	prethodnoStanjeHardP02 = trenutnoStanjeHardP02;


	//TASTER3
	trenutnoStanjeHardP03 = P0_3;
	if(prethodnoStanjeHardP03 == trenutnoStanjeHardP03)	 
	{
		brPonavljanjaP03++;
		if(brPonavljanjaP03 > 5-1)
		{
			trenutnoStanjeSoftP03 = trenutnoStanjeHardP03;
			brPonavljanjaP03 = 0;
		}
	}
	else
	{
		brPonavljanjaP03 = 0;
	}

	prethodnoStanjeHardP03 = trenutnoStanjeHardP03;
}

void main(void)
{
	P2 = 0xff;
	P0 = 0xff;

    PCON = 0x80;
	SCON = 0x50; 
	BDRCON = 0x1C;
	BRL = 253;

	EA = 1;
	ES = 1;
	TH1 = 76;						  
	TL1 = 1;
	TMOD = 0x10;
	ET1 = 1;
	TR1 = 1;

	brojacPrekida1 = 0;
	
   /*
	initDisplay();
	clearDisplay();
	writeLine(pok1);
	newLine();
	writeLine(pok2); */

	//potpatosni prekidaci
	//P0_0 je za ulaz
	//P0_1 je za izlaz

	while(1)
	{
		/*trenutnoStanjeSoftP00_zaMain = trenutnoStanjeSoftP00;
		trenutnoStanjeSoftP01_zaMain = trenutnoStanjeSoftP01;
		trenutnoStanjeSoftP02_zaMain = trenutnoStanjeSoftP02;
		trenutnoStanjeSoftP03_zaMain = trenutnoStanjeSoftP03; */

		if (P0_0 == 0 && motor == 0)	//pritisnut taster -> 0
		{
			ulaz = 1;
		}
		else if (P0_1 == 0 && motor == 0)
		{
	 		izlaz = 1;
		}

		if (P0_2 == 0)	//pritisnut taster -> 0
		{
			rampa = 1;	//podignuta rampa
			P2 = 0x00;
		}
		else if (P0_3 == 0)
		{
	 		rampa = 0;	//spustena rampa
			P2 = 0xFF;
		}

		if (status)
		{
			if (rampa == 0)
			{
				motor = 0; 	//rampa je spustena te motor treba iskljuciti
			}

			if (slob > 0 && ulaz) 
			{
				motor = 1;	//motor ukljucen
					
				if (rampa)
				{
					slob--;
					ulaz = 0;
				}	
			}
			else if (slob < 15 && izlaz)
			{
	 	 	  	motor = 1;	//motor ukljucen

				if (rampa)
				{   
					slob++;
					izlaz = 0;
				}
			}
			else 
			{
				P2 = 0xFF;
				rampa = 0;
				motor = 0;
			}

			status = 0;
		}	
	}	  
}