/* Exracts level information from the Dangerous Dave binary
*  Data is stored in levelx.dat
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL.h>

/* Level format structure */
struct dave_level {
	uint8_t path[256];
	uint8_t tiles[1000];
	uint8_t padding[24];
};

int main(int argc, char* argv[])
{
	const uint32_t level_addr = 0x26e0a;

	/* Allocate space for 10 game levels */
	struct dave_level level[10];

	/* Open EXE file and go to level data */
	FILE *fin;
	fin = fopen("DAVE.EXE","rb");
	fseek (fin, level_addr, SEEK_SET);

	/* Stream level data to memory and output files */
	FILE *fout;
	char file_num[4];
	char fname[12];
	uint32_t i,j,k;

	for (j=0; j<10; j++)
	{
		/* Make new file */
		fname[0]='\0';
		strcat(fname, "level");
		sprintf(&file_num[0], "%u", j);
		strcat(fname, file_num);
		strcat(fname, ".dat");

		fout = fopen(fname, "wb");

		/* Stream path data */
		for (i=0; i< sizeof(level[j].path); i++)
		{
			level[j].path[i] = fgetc(fin);
			fputc(level[j].path[i], fout);
		}

		/* Stream tile indices */
		for (i=0; i< sizeof(level[j].tiles); i++)
		{
			level[j].tiles[i] = fgetc(fin);
			fputc(level[j].tiles[i], fout);
		}

		/* Stream padding */
		for (i=0; i< sizeof(level[j].padding); i++)
		{
			level[j].padding[i] = fgetc(fin);
			fputc(level[j].padding[i], fout);
		}

		printf("Saving %s as level data", fname);
		fclose(fout);
	}
	fclose(fin);

	/* Load tileset */
	SDL_Surface *tiles[158];
	for (i=0; i<158; i++)
	{
		fname[0]='\0';
		strcat(fname, "tile");
		sprintf(&file_num[0], "%u", i);
		strcat(fname, file_num);
		strcat(fname, ".bmp");

		tiles[i] = SDL_LoadBMP(fname);
	}

	/* Create map of the world by level, row, and column */
	SDL_Surface *map;
	SDL_Rect dest;
	uint8_t tile_index;
	map = SDL_CreateRGBSurface(0, 1600, 1600, 32, 0, 0, 0, 0);
	for (k=0; k<10; k++)
	{
		for (j=0; j<10; j++)
		{
			for (i=0; i<100; i++)
			{
				tile_index = level[k].tiles[j*100+i];
				dest.x = i*16;
				dest.y = k*160+j*16;
				dest.w = 16;
				dest.h = 16;
				SDL_BlitSurface(tiles[tile_index], NULL, map, &dest);
			}
		}
	}
	SDL_SaveBMP(map, "map.bmp");

	return 0;
}
