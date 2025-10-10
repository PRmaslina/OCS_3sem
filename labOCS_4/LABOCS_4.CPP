#include <iostream.h>
#include <dos.h>
#include <conio.h>

void drawWindow(int lx, int ly, int rx, int ry){
	for(int x1 = lx; x1 < rx; x1++){
		gotoxy(x1,ly); cprintf("-");
		gotoxy(x1,ry); cprintf("-");
	}
	for(int y1 = ly; y1 <= ry; y1++){
		gotoxy(lx,y1); cprintf("|");
		gotoxy(rx,y1); cprintf("|");
	}
}

int bios_getkey_raw() {
    union REGS in, out;
    in.h.ah = 0x00;
    int86(0x16, &in, &out);
    return (out.x.ax);
}

int main() {
    clrscr();
    int lx = 20,
	ly = 10,
	rx = 40,
	ry = 20,
	x = 0,
	y = 0;
    drawWindow(lx,ly,rx,ry);
    x = lx + (rx - lx)/2;
    y = ly + (ry - ly)/2;
    gotoxy(x,y);
    cprintf("*");
    int a = 1;
    while (a == 1) {
	int ax = bios_getkey_raw();
	int al = ax & 0xFF;
	int ah = (ax >> 8) & 0xFF; // scan code

	if (al == 0x00) {

	    if (ah == 0x85 || ah == 0x57 || ah == 0x43) { // F11
		if (x - 1 > lx) {
		    gotoxy(x, y); putch(' ');
		    x = x - 1;
		    gotoxy(x, y); putch('*');
		}
	    } else if (ah == 0x86 || ah == 0x58 || ah == 0x44) { // F12
		if (x + 1 < rx) {
		    gotoxy(x, y); putch(' ');
		    x = x + 1;
		    gotoxy(x, y); putch('*');
		}
	    }
	} else {
	    if (al == 27) { // Esc
		break;
	    }
	    // игнор остальных
	}
    }

    gotoxy(x, y); putch(' ');
    gotoxy(1,1);
    return 0;
}
