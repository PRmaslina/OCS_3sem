#include<conio.h>
#include<dos.h>


void cellInt(unsigned long intNumber) {
    unsigned long mask = 1;
    mask <<= sizeof(long) * 8 - 1;
    for (long i = 1; i < sizeof(long) * 8 + 1; ++i, mask >>= 1) {
	if(mask & intNumber){
		cprintf("1");
	}
	else{
		cprintf("0");
	}
	if (i % 8 == 0) {
	    cprintf(" ");
	}
    }
    cprintf("\n\n\r");
}

void cellDoub(int doubCellInArrInt[]) {

    unsigned int mask, elCount = 0;
    for (int j = 0; j < sizeof(double) / sizeof(int); ++j) {
	mask = 1;
	mask <<= sizeof(mask) * 8 - 1;
	for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
	    if(mask& doubCellInArrInt[sizeof(double) / sizeof(int) - 1 - j]){
		cprintf("1");
	    }
	    else{
		cprintf("0");
	    }
	    elCount++;
	    if (elCount == (sizeof(double) / 8) * 12) {
		cprintf(" ");
	    }
	    else if (elCount == 1) {
		cprintf(" ");
	    }
	}
    }
    cprintf("\n\n\r");
}

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
		lx = 23,
		ly = 10,
		rx = 57,
		ry = 25;
	//window(lx,ly,rx,ry);
	unsigned char
		textColor = WHITE,
		backColor = BLACK;
	textbackground(backColor);
	textcolor(textColor);
	window(lx,ly,rx,ry);

    int bitID, bitValue;
    unsigned long intNumber;
    unsigned long maskLong;
    unsigned int maskBitID[2] = {0,0};
    char input;
    union {
	float floatNumber;
	int floatCellInInt;
    };
    union {
	double doubNumber;
	int doubCellInArrInt[sizeof(double) / sizeof(int)];
    };


    cprintf("int: %d bytes\n\r", sizeof(int));
    cprintf("short int: %d bytes\n\r", sizeof(short int));
    cprintf("long int: %d bytes\n\r", sizeof(long int));
    cprintf("float: %d bytes\n\r", sizeof(float));
    cprintf("double: %d bytes\n\r", sizeof(double));
    cprintf("long double: %d bytes\n\r", sizeof(long double));
    cprintf("char : %d bytes\n\r", sizeof(char));
    //cprintf(""bool: %ld bytes\n\r", sizeof(bool) << '\n\r';

    cprintf("\n\rEnter variable unsigned long: ");
    cscanf("%ld",&intNumber);
    getch();
    cellInt(intNumber);

	do{
	scroll (6, ly-1, lx-1, ry+1, rx+1, backColor);
	scroll (6, ly-1, lx-1, ry+1, rx+1, backColor);
	scroll (6, ly-1, lx-1, ry+1, rx+1, backColor);
	scroll (6, ly-1, lx-1, ry+1, rx+1, backColor);
	scroll (6, ly-1, lx-1, ry+1, rx+1, backColor);
	getch();
	scroll (7, ly-1, lx-1, ry+1, rx+1, 2);
	scroll (7, ly-1, lx-1, ry+1, rx+1, 2);
	scroll (7, ly-1, lx-1, ry+1, rx+1, 2);
	scroll (7, ly-1, lx-1, ry+1, rx+1, 2);
	scroll (7, ly-1, lx-1, ry+1, rx+1, 2);
	cprintf("Change bit? (Y/n): ");
	cscanf("%c",&input);
	if (input != 'n'){
	    cprintf("\n\rBit place (right to left): ");
	    cscanf("%d",&bitID);
	    getch();
	    cprintf("\n\rBit value: ");
	    cscanf("%d",&bitValue);
	    getch();
	    maskLong = 1;
	    maskLong <<= bitID;
	    if (bitValue == 1) {
		if ((intNumber ^ maskLong) > intNumber) {
		    intNumber ^= maskLong;
		}
	    }
	    else {
		if ((intNumber ^ maskLong) < intNumber) {
		    intNumber ^= maskLong;
		}
	    }
	    cprintf("\n\r");
	    cellInt(intNumber);
	    cprintf("Result number: %ld \n\r\n\r" ,intNumber);
	}
    } while (input != 'n');

    cprintf("\n\rEnter variable double: ");
    cscanf("%lf",&doubNumber);
    cprintf("\n\r");
    getch();
    cellDoub(doubCellInArrInt);
    input = 'a';
    do {
	cprintf("Change bit? (Y/n): ");
	cscanf("%c",&input);
	if (input != 'n') {
	    cprintf("\n\rBit place (right to left): ");
	    cscanf("%d",&bitID);
	    getch();
	    cprintf("\n\rBit value: ");
	    cscanf("%d",&bitValue);
	    getch();
	    maskBitID[bitID / (sizeof(int) * 8) + 1] = 1;
	    maskBitID[bitID / (sizeof(int) * 8) + 1] <<= bitID % (sizeof(int)*8);
	    if ( ( (doubCellInArrInt[(bitID / (sizeof(int) * 8))]) ^ maskBitID[bitID / (sizeof(int) * 8) + 1] ) > (doubCellInArrInt[(bitID / (sizeof(int) * 8))]) ){
		if (bitValue == 1){
		doubCellInArrInt[(bitID / (sizeof(int) * 8))] ^= maskBitID[bitID / (sizeof(int) * 8) + 1];
		}
	    }
	    else{
		if (bitValue == 0){
		doubCellInArrInt[(bitID / (sizeof(int) * 8))] ^= maskBitID[bitID / (sizeof(int) * 8) + 1];
		}
	    }
	    cprintf("\n\r");
	    cellDoub(doubCellInArrInt);
	    cprintf("\n\rResult number: %lf \n\r\n\r", doubNumber);

	}
    } while (input != 'n');

	getch();
	return 0;
}