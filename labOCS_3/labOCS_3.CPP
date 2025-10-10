#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>

int main(){
    clrscr();
    int graph_driver;
    int graph_mode;
    int graph_error_code;
    graph_driver = DETECT;

    initgraph(&graph_driver, &graph_mode, "c:\\bgi");
    graph_error_code = graphresult();
    if(graph_error_code != grOk){
        cprintf("%c",graph_error_code);
        getch();
        return 255;
    }

    int left = 60,
        top = 30,
        right = 600,
        bottom = 400;

    setviewport(left, top, right, bottom, 1);

    // Параметры отображения
    double x_min = 0;      // Начало: pi/2
    double x_max = 12*M_PI;     // Конец: 12pi
    double x_range = x_max - x_min;
    
    int graph_width = right - left - 80;
    int centerY = (bottom-top)/2;

    setcolor(WHITE);
    // Горизонтальная ось X
    line(40, centerY, graph_width + 40, centerY);
    // Вертикальная ось Y
    line(40, 30, 40, bottom-top - 20);

    // Деления на оси X с шагом pi/2
    setcolor(7); // Светло-серый
    for(double x_val = x_min; x_val <= x_max; x_val += M_PI/2){
        // Преобразуем математическое значение x в экранную координату
        double screen_x = 40 + ((x_val - x_min) / x_range) * graph_width;
        
        // Рисуем деление
        line(screen_x, centerY - 5, screen_x, centerY + 5);
        
        // Подписи делений (только для целых pi)
        if(fmod(x_val, M_PI) < 0.001) {
            char label[10];
            int pi_multiplier = (int)(x_val / M_PI + 0.5);
            if(pi_multiplier == 1) {
                sprintf(label, "pi");
            } 
            else if (pi_multiplier != 0){
                sprintf(label, "%dpi", pi_multiplier);
            }
            else{
                continue;
            }
            outtextxy(screen_x - 8, centerY + 10, label);
        }
    }

    // Деления на оси Y
    setcolor(7);
    for(int y_val = -150; y_val <= 150; y_val += 25){
        int screen_y = centerY - y_val;
        if(screen_y >= 30 && screen_y <= bottom-top - 20){
            line(35, screen_y, 45, screen_y);
            char label[10];
            sprintf(label, "%4d", y_val/25);
            outtextxy(0, screen_y, label);
        }
    }

    // Подписи осей
    outtextxy(graph_width + 30, centerY - 15, "X");
    outtextxy(45, 25, "Y");

    // Рисуем функцию
    setcolor(YELLOW);
    double prev_screen_x = 0, prev_screen_y = 0;
    int first_point = 1;

    double max_y = pow(sin(M_PI/2/2), 3) - sqrt(M_PI/2);
    for(double math_x = x_min; math_x <= x_max; math_x += 0.05){
	// Вычисляем значение функции
	double math_y = pow(sin(math_x/2), 3) - sqrt(math_x);

	// Преобразуем математические координаты в экранные
	double screen_x = 40 + ((math_x - x_min) / x_range) * graph_width;
	double screen_y = centerY - math_y * 25;

	// Рисуем линию от предыдущей точки
	    if(!first_point && math_x >= M_PI/2) {
	    line(prev_screen_x, prev_screen_y, screen_x, screen_y);
	    //считаем максимальныое
	    if (math_y > max_y){
		max_y = math_y;
	    }
	}



	prev_screen_x = screen_x;
	prev_screen_y = screen_y;
	first_point = 0;
    }


    // Заголовок графика
    setcolor(WHITE);
    outtextxy((right-left)/2 - 100, 15, "y = sin(x/2)^3 - sqrt(x)");

    // Окно с макс знач функции
    char s[10];
    sprintf(s, "max y : %lf", max_y);
    setcolor(WHITE);
    rectangle( right-210, top-5, right-60, top+15);
    floodfill( right-209, top-4, WHITE);
    setcolor(BLACK);
    outtextxy(right-200, top, s);
    

    getch();
    closegraph();
    return 0;
}