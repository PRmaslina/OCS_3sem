#include<conio.h>
#include<dos.h>

void scroll (int direction, char l_row, char l_col, char r_row, char r_col, char attr){
	union REGS r;
	if (direction){
		r.h.al= 1;
		r.h.ah=direction;
	}
	else{
		r.h.al=0;
		r.h.ah=6;
	}
	r.h.ch =  l_row;
	r.h.cl= l_col;
	r.h.dh = r_row;
	r.h.dl= r_col;
	r.h.bh=attr;
	int86(0x10,&r,&r);
}


int main(){
	clrscr();
	unsigned char
		lx = 25,
		ly = 12,
		rx = 55,
		ry = 23;
	//window(lx,ly,rx,ry);
	unsigned char
		textColor = WHITE,
		backColor = BLACK;
	char input = '0';
	textbackground(backColor);
	textcolor(textColor);
	window(lx,ly,rx,ry);
	const char* colorENG[] = {"BLACK","BLUE","GREEN","CYAN","RED","MAGENTA","BROWN","LIGHTGRAY","DARKGRAY","LIGHTBLUE","LIGHTGREEN","LIGHTCYAN","LIGHTRED","LIGHTMAGENTA","YELLOW","WHITE"};
	//const char* colorRUS[] = {"ЧЁРНЫЙ","СИНИЙ","ЗЕЛЁНЫЙ","БИРЮЗОВЫЙ","КРАСНЫЙ","ПУРПУРНЫЙ","КОРИЧНЕВЫЙ","СВЕТЛО-СЕРЫЙ","ТЁМНО-СЕРЫЙ","СВЕТЛО-СИНИЙ","СВЕТЛО-ЗЕЛЁНЫЙ","СВЕТЛО-БИРЮЗОВЫЙ","СВЕТЛО-КРАСНЫЙ","СВЕТЛО-ПУРПУРНЫЙ","ЖЁЛТЫЙ","БЕЛЫЙ"};
	const char* colorRUS[] = {"CHERNYI","SINII","ZELENYI","BIRYUZOVYI","KRASNYI","PURPURNYI","KORICHNEVYI","SVETLO-SERYI","TYOMNO-SERYI","SVETLO-SINII","SVETLO-ZELENYI","SVETLO-BIRYUZOVYI","SVETLO-KRASNYI","SVETLO-PURPURNYI","ZHYOLTYI","BELYI"};

	for(int i = 0; i < 16; i++){
		//sleep(2);
		for(int j = 0; j < 16; j++){
			sleep(1);
			textbackground(i);
			textcolor(j);
			cprintf("%s %s\n\r",colorENG[i],colorRUS[j]);
		}
	}

	do{
		input = getch();
		if(input == 0x48){
			scroll(7,ly-1,lx-1,ry+1,rx+1, 0x07);
		}
		else if(input == 0x50){
			scroll(6,ly-1,lx-1,ry+1,rx+1, 0x07);
		}
	}while (input != 0x0D);
	return 0;
}