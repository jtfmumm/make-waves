#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264
#endif

#include "sf_output.h"
#include "wave_tables.h"

int SR = 44100; 

int main(int argc, char ** argv)
{
	int i, j, k;
	SFILE* sfout = malloc(sizeof(SFILE));
	float sin_table[1024];
	populate_sin_table(sin_table, 1024);
	float index = 0;
	float twopi = 2 * M_PI;
	int step = 1;
	//int blockframes = 256;
	int end;
	float dur, freq;
	float phase_angle = 0;

	//init_sfile(SFILE, name, sample rate, channels, bits-per-sample, vector size)
	init_sfile(sfout, "test2.wav", SR, 1, 16, 1024);

	dur = 10;
	freq = 440;
	end = (int) (dur * SR);
	sfout->data_size = end * sizeof(short) * sfout->channels;
	printf("%s\n", "Creating wave file...");
	
	//Write to file
	for (i = 0; i < end; i += sfout->vector_size) {
		for (j = 0; j < sfout->vector_size; j++, step++) {
			sfout->buffer[j] = osc(sin_table, freq, 16000, &index, SR, 1024);
		}
		sfwrite(sfout);
		//freq *= 1.24; //Produce watery vibrato
		//if (freq > 700) freq = 200;
	}

	sfclose(sfout);
	free(sfout->buffer);
	free(sfout->header);
	free(sfout);
	return 0;
}
