#include<curses.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){
	int 	a = 7;					//x step
	int	b = 7;					//y step	
	int	x = 0;					//x start
	int	yleft = 0;					//y start
	char 	strShow[] = "i am your father";		//show welcome
	char 	blkShow[] = "                ";		//blank
	int 	yright = yleft + strlen(strShow);


	initscr();
	clear();
	for(; x >= 0 && x < LINES && yleft >= 0 && yright < COLS; x += a, yleft += b, yright += b){
		if(x > 0 && x < LINES && yleft > 0 && yright < COLS){
			move(x - a, yleft - b);
			addstr(blkShow);
			refresh();
		}
		move(x, yleft);
		if(x % 2 == 1)
			standout();
		addstr(strShow);
		if(x % 2 == 1)
			standend();
		refresh();
		sleep(1);
		if(x + a >= LINES || x + a <= 0)
			a = -a;
		if(yright + b >= COLS || yleft + b <= 0)
		       	b = -b;	
	}
	refresh();
	getch();
	endwin();
	return 0;
}
