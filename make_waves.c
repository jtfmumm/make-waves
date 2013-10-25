#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sf_output.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264
#endif

int SR = 44100; 

int main(int argc, char ** argv)
{
	int i, j;
	SFILE* sfout = malloc(sizeof(SFILE));
	float twopi = 2 * M_PI;
	int step = 1;
	//int blockframes = 256;
	int end;
	float dur, freq;

	//init_sfile(SFILE, name, sample rate, channels, bits-per-sample, vector size)
	init_sfile(sfout, "test2.wav", SR, 1, 16, 256);

	dur = 10;
	freq = 220;
	end = (int) (dur * SR);
	sfout->data_size = end * sizeof(short) * sfout->channels;
	printf("%s\n", "Creating wave file...");
	
	//Write to file
	for (i = 0; i < end; i += sfout->vector_size) {
		for (j = 0; j < sfout->vector_size; j++, step++) {
			sfout->buffer[j] = 16000 * sin(step * twopi * freq/SR);
		}
		sfwrite(sfout);
	}

	sfclose(sfout);
	free(sfout->buffer);
	free(sfout->header);
	free(sfout);
	return 0;
}
