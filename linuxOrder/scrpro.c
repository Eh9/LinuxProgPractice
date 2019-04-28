#include<curses.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int 	a = 7;					//x step
	int	b = 7;					//y step	
	int	x = 0;					//x start
	int	y = 0;					//y start
	char 	strShow[] = "i am your father";		//show welcome
	char 	blkShow[] = "                ";		//blank


	initscr();
	clear();
	for(; x >= 0 && x < LINES && y >= 0 && y < COLS; x += a, y += b){
		if(x > 0 && x < LINES && y > 0 && y < COLS){
			move(x - a, y - b);
			addstr(blkShow);
			refresh();
		}
		move(x, y);
		if(x % 2 == 1)
			standout();
		addstr(strShow);
		if(x % 2 == 1)
			standend();
		refresh();
		sleep(1);
		if(x + a >= LINES || x + a <= 0)
			a = -a;
		if(y + b >= COLS || y + b <= 0)
		       	b = -b;	
	}
	refresh();
	getch();
	endwin();
	return 0;
}
