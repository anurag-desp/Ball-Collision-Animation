#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>


#define WIDTH 25
#define HEIGHT 50
#define clear_screen() printf("\033[H\033[J")

int DEFAULT_DURATION = 5; // in seconds
char DEFAULT_BALL_SHAPE = 'O';
int DEFAULT_BALL_X_POS = 5;
int DEFAULT_BALL_Y_POS = 0;
int DURATION_PER_FRAME = 1000; // milliseconds
int DEFAULT_DURATION_OF_FRAMES = 10;


typedef struct Ball {
	char shape;
	int x_position;
	int y_position;
} Ball;


void fall_animation(Ball ball, int duration, int microseconds_per_frame) {
	clear_screen();

	char x_direction = 'R';
	char y_direction = 'D';

	for(int y = 0; y < duration; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(x == ball.x_position) {
				printf("%c", ball.shape);
				fflush(stdout);
				break;
			}
			else {
				printf(" ");
			}
		}
		if(x_direction == 'R') 
			ball.x_position++;
		else
			ball.x_position--;

		if(y_direction == 'D')
			ball.y_position++;
		else 
			ball.y_position--;

		if(ball.x_position >= WIDTH/2) {
			x_direction = 'L';
			ball.x_position -= 2;
		}
		else if(ball.x_position < 0) {
			x_direction = 'R';
			ball.x_position += 2;
		}

		if(ball.y_position > HEIGHT/2) {
			y_direction = 'U';
			ball.y_position -= 2;
		}
		else if(ball.y_position < 0) {
			ball.y_position += 2;
			y_direction = 'D';
		}

		clear_screen();
		usleep(microseconds_per_frame * DURATION_PER_FRAME);

		// as clear_screen() erases the
		// whole terminal. We need a way to 
		// go to the next y position for the
		// fall animation
		for(int k = 0; k < (ball.y_position); k++) {
			printf("\n");
		}	
	}
}
	
void set_ball(Ball *ball, char shape, int x_pos, int y_pos) {
	ball -> shape = shape;
	ball -> x_position = x_pos;
	ball -> y_position = y_pos;
}

int main(int argc, char **argv) {

	Ball ball;

	int DEFAULTS[] = {
		DEFAULT_DURATION,
		DEFAULT_DURATION_OF_FRAMES,
		DEFAULT_BALL_X_POS,
		DEFAULT_BALL_Y_POS
	};

	int duration,
		microseconds_per_frame,
	    ball_x_pos,
		ball_y_pos;
	char ball_shape = DEFAULT_BALL_SHAPE;
	
	for(int i = 1; i < argc; i++) {
		if(i > 4) break;
		DEFAULTS[i-1] = atoi(argv[i]);
	}

	duration = DEFAULTS[0]; // duration in seconds
	microseconds_per_frame = DEFAULTS[1];
	ball_x_pos = DEFAULTS[2];
	ball_y_pos = DEFAULTS[3];

	duration = 20 * duration; // 20 iterations take 1 second. 20 * duration iterations will take duration seconds

	set_ball(&ball, ball_shape, ball_x_pos, ball_y_pos);
	fall_animation(ball, duration, microseconds_per_frame);
	return 0;
}
