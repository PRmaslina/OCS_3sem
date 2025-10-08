#include <iostream>

using namespace std;

void cellInt(unsigned long intNumber) {
    unsigned long mask = 1;
    mask <<= sizeof(long) * 8 - 1;
    for (long i = 1; i < sizeof(long) * 8 + 1; ++i, mask >>= 1) {
        cout << mask & intNumber ? '1' : '0';
        if (i == 1 || i % 8 == 0) {
            attron(COLOR_PAIR(2));
            cout << " ");
        }
    }
    cout <<  "\n\n" );
    attron(COLOR_PAIR(4));
    refresh();
}

void cellDoub(int doubCellInArrInt[]) {

    unsigned int mask, elCount = 0;
    attron(COLOR_PAIR(1));
    for (int j = 0; j < sizeof(double) / sizeof(int); ++j) {
        mask = 1;
        mask <<= 31;
        for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
            mask& doubCellInArrInt[sizeof(double) / sizeof(int) - 1 - j] ? '1' : '0';
            elCount++;
            if (elCount == (sizeof(double) / 8) * 12) {
                attron(COLOR_PAIR(3));
                cout << " ");
            }
            else if (elCount == 1) {
                attron(COLOR_PAIR(2));
                cout << " ");
            }
        }
    }
    cout <<  "\n\n");
    attron(COLOR_PAIR(4));
    refresh();
}

int main()
{
    setlocale(0, "");
    initscr();
    if (has_colors() == FALSE){
        endwin();
        cout << "Your terminal does not support color\n)";
        return 1;
    }
    start_color();
    init_pair(1,COLOR_RED, COLOR_BLACK);
    init_pair(2,COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_BLUE, COLOR_BLACK);
    init_pair(4,COLOR_WHITE, COLOR_BLACK);
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
    setlocale(0, "");

    cout << "int: %ld bytes\n", sizeof(int));
    cout << "short int: %ld bytes\n" , sizeof(short int));
    cout << "long int: %ld bytes\n", sizeof(long int));
    cout << "float: %ld bytes\n" , sizeof(float));
    cout << "double: %ld bytes\n" , sizeof(double));
    cout << "long double: %ld bytes\n" , sizeof(long double));
    cout << "char : %ld bytes\n", sizeof(char));
    cout << "bool: %ld bytes\n", sizeof(bool));

    cout << "\nEnter variable unsigned long: ");
    refresh();
    scanw("%ld",&intNumber);
    cout << "\n");
    cellInt(intNumber);

    do{
        cout <<  "Change bit? (Y/n): ");
        refresh();
        scanw("%c",&input);
        if (input != 'n'){
            cout <<  "\nBit place (right to left): ");
            refresh();
            scanw("%i",&bitID);
            cout <<  "\nBit value: ");
            refresh();
            scanw("%i",&bitValue);
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
            cout << "\n");
            cellInt(intNumber);
            cout << "Result number: %ld \n\n", intNumber);
            refresh();
        }
    } while (input != 'n');

    cout <<  "\nEnter variable double: ");
    refresh();
    scanw("%lf",&doubNumber);
    cout << "\n");
    cellDoub(doubCellInArrInt);
    do {
        cout << "Change bit? (Y/n): ");
        refresh();
        scanw("%c",&input);
        if (input != 'n') {
            cout <<  "\nnBit place (right to left): ");
            refresh();
            scanw("%i",&bitID);
            cout <<  "\nBit value: ");
            refresh();
            scanw("%i",&bitValue);
            if (bitID < 32) {
                maskBitID[0] = 0;
                maskBitID[1] = 1;
                maskBitID[1] <<= bitID;
            }
            else {
                maskBitID[0] = 1;
                maskBitID[1] = 0;
                maskBitID[0] <<= bitID - 32;
            }
            if (bitValue == 1) {
                if (((doubCellInArrInt[1] ^ maskBitID[0]) + (doubCellInArrInt[0] ^ maskBitID[1])) > doubCellInArrInt[0]+ doubCellInArrInt[1]) {
                    doubCellInArrInt[1] ^= maskBitID[0];
                    doubCellInArrInt[0] ^= maskBitID[1];
                }
            }
            else {
                if (((doubCellInArrInt[1] ^ maskBitID[0]) + (doubCellInArrInt[0] ^ maskBitID[1])) < doubCellInArrInt[0] + doubCellInArrInt[1]) {
                    doubCellInArrInt[1] ^= maskBitID[0];
                    doubCellInArrInt[0] ^= maskBitID[1];
                }
            }
            cout << "\n");
            cellDoub(doubCellInArrInt);
            cout << "\nResult number: %f \n\n", doubNumber);
            refresh();
        }
    } while (input != 'n');

    endwin();
    return 0;
}