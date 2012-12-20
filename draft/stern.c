/* MEDVEDx64, 2012.12.12 */

#include <SDL/SDL_gfxPrimitives.h>
#include <stdio.h>
#include <string.h>

SDL_Surface * screen = NULL;

unsigned char col_r = 0;
unsigned char col_g = 0;
unsigned char col_b = 0;
unsigned char col_a = 0;

int offset_x = 0;
int offset_y = 0;

#define NIL_CHECK if(screen != NULL)

int updateVideoMode(unsigned int w,
					unsigned int h, char bpp)
{
	SDL_Surface * old_screen = screen;
	screen = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(screen == NULL)
	{
		fprintf(stderr, "Failed to set video mode\n");
		return 1;
	}

	if(old_screen != NULL)
		SDL_FreeSurface(old_screen);

	return 0;
}

#define MAX_ARGS 8
#define CONTINUE_		do                  	\
	{											\
		SDL_Flip(screen);						\
		continue;								\
	}											\
	while (0)


int main(void)
{
	fprintf(stderr, "Stern Visualization Language basic layer implementation\n0.0.1 2012.12.12\n");

	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "SDL initialization error: %s\n", SDL_GetError());
		return 1;
	}

	updateVideoMode(320, 240, 32);
	SDL_WM_SetCaption("SVL Implementation 0.0.1", 0);

	while(!feof(stdin))
	{
		char buf[0x1000];
		memset(&buf, 0, 0x1000);
		buf[0] = fgetc(stdin);
		if(buf[0] == '~')
		{
			int args[MAX_ARGS];
			char buff[0x1000];
			char *dummy = fgets(buff, 0x1000, stdin);
			int res = sscanf(
				buff, "%s %d %d %d %d %d %d %d %d\n",
				buf, &args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6], &args[7]
			);

			if(!strcasecmp(buf, "color") && (res-1) >= 4)
			{
				col_r = args[0];
				col_g = args[1];
				col_b = args[2];
				col_a = args[3];
				CONTINUE_;
			}

			if(!strcasecmp(buf, "screen") && (res-1) >= 2)
			{
				updateVideoMode(args[0], args[1], 32);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "clear"))
			{
				updateVideoMode(screen->w, screen->h, 32);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "offset") && (res-1) >= 2)
			{
				offset_x = args[0];
				offset_y = args[1];
				CONTINUE_;
			}

			if(!strcasecmp(buf, "write"))
			{
				NIL_CHECK SDL_SaveBMP(screen, "stern.bmp");
				CONTINUE_;
			}

			if(!strcasecmp(buf, "pixel") && (res-1) >= 2)
			{
				NIL_CHECK pixelRGBA(screen, args[0]+offset_x, args[1]+offset_y, col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "line") && (res-1) >= 4)
			{
				NIL_CHECK lineRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2]+offset_x, args[3]+offset_y, col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "rect") && (res-1) >= 4)
			{
				NIL_CHECK rectangleRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2]+offset_x, args[3]+offset_y, col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "box") && (res-1) >= 4)
			{
				NIL_CHECK boxRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2]+offset_x, args[3]+offset_y, col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "circle") && (res-1) >= 3)
			{
				NIL_CHECK circleRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "filledcircle") && (res-1) >= 3)
			{
				NIL_CHECK filledCircleRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "ellipse") && (res-1) >= 4)
			{
				NIL_CHECK ellipseRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], args[3], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "filledellipse") && (res-1) >= 4)
			{
				NIL_CHECK filledEllipseRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], args[3], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "pie") && (res-1) >= 5)
			{
				NIL_CHECK pieRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], args[3], args[4], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "filledpie") && (res-1) >= 5)
			{
				NIL_CHECK filledPieRGBA(screen, args[0]+offset_x, args[1]+offset_y, args[2], args[3], args[4], col_r, col_g, col_b, col_a);
				CONTINUE_;
			}

			if(!strcasecmp(buf, "quit")) break;
		}

		NIL_CHECK SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}