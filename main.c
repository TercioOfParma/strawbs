#include <curses.h>/*simply curses.h for windows */
#include <stdlib.h>
#include <time.h>


typedef struct{
	int x,y;
	char display;
	int score;
	int colour;


}entity;

void wait(unsigned int seconds){
	clock_t derp;
	derp = clock() + seconds * CLOCKS_PER_SEC;
	while(clock() < derp){
	}

}

void init(){
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	nodelay(stdscr, TRUE);//makes the getch() not delay

}
int deinit(){
	refresh();
	endwin();
	exit(0);
	return 0;

}
void movep(entity *e){
	int takeinp;
	takeinp = getch();

	switch(takeinp){
		
		case KEY_LEFT:
			mvaddch(e->y, e->x, ' ');
			e->x--;
			break;
		case KEY_RIGHT:
			mvaddch(e->y, e->x, ' ');
			e->x++;
			break;
		case KEY_UP:
			mvaddch(e->y, e->x, ' ');
			e->y--;
			break;
		case KEY_DOWN:
			mvaddch(e->y, e->x, ' ');
			e->y++;
			break;
		case KEY_F(1):
			deinit();
			break;
		case 27:
			deinit();
			break;
			
			
		default:
			break;


	}




}
void draw(entity *play){
	int s = play->colour;
	
	init_pair(11, s, COLOR_BLACK);
	attron(COLOR_PAIR(11));
	mvaddch(play->y, play->x, play->display);
	attroff(COLOR_PAIR(11));
}
void drawf(entity *e){
	int i = 0;
	while( i < 10){
		int d = e->colour;
		if (e->colour == 0){
			attron(A_STANDOUT);
			attron(COLOR_BLACK);
			mvaddch(e->y, e->x, e->display);
			attroff(A_STANDOUT);
			attroff(COLOR_BLACK);
		
		}
		else{
			init_pair(i,d, COLOR_BLACK);
			attron(COLOR_PAIR(i));
			mvaddch(e->y, e->x, e->display);
			attroff(COLOR_PAIR(i));
		}
		i++;
		e++;
	}
}



void definestats(entity *f){
	srand(time(NULL));
	int i = 0;
	while(i < 10){
		f->x = rand() % 80;
		f->y = rand() % 21 + 4;
		f->display = '%';
		f->colour = rand() % 8;	
		f->score = rand() % 10 + 1;
		i++;
		f++;
	}

}

void collision(entity *f, entity *e){//f is fruit, e is player
	int i = 0;
	int counter = 0;
	entity *derp = &f;//maintains the address of the pointer
	while(i < 10){
		if(f->x == e->x && f->y == e->y){
			e->score += f->score;
			f->x = 1000;//i know its hacky but i have no idea how to make linked lists
			f->y = 1000;
			f->display = ' ';
			 
		
		}
		if(f->x == 1000){
			counter++;
		}
		if(counter == 10){
			
			definestats(derp);//passed to function so it redefines the array from index 0
		
		}
		else{}
		i++;
		f++;
	
	
	}


}




int main(){
	clock_t timelim;
	init();
	printw("Strawb catcher version 1\n");
	printw("\t\tPress F1 or ESC to quit");
	entity p;
	p.x = 10;
	p.y = 20;
	p.display = '@';
	p.score = 0;
	p.colour = 2;
	entity *playerptr = &p;
	entity fr[10];
	entity *fruitpointer = &fr;
	int i;
	definestats(fruitpointer);
	timelim = clock();
	int escape;
	
	while(1 == 1){
		int score = p.score;
		int o = 0;
		mvprintw(0,30,"Score : %d", score);
		movep(playerptr);
		draw(playerptr);
		collision(fruitpointer, playerptr);
		drawf(fruitpointer);
		timelim = clock() - timelim;
		escape = ((int)timelim)/CLOCKS_PER_SEC;
		mvprintw(0, 60,"Seconds : %d", ((int)timelim)/CLOCKS_PER_SEC);
		if(escape > 30){
		
			int d = 0;
			int displayscore = p.score;
			
			clear();
			mvprintw(10, 20, "Congratulations, you have scored %d points\n", displayscore);
			refresh();
			wait(10);
			deinit();
			}
	}
	



}