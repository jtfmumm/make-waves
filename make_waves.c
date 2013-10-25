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
	int i; //j, k;
	SFILE* sfout = malloc(sizeof(SFILE));
	float sin_table[1024];
	float square_table[1024];
	float saw_table[1024];
	float pulse_table[1024];
	populate_sin_table(sin_table, 1024);
	populate_square_table(square_table, 8, 1024);
	populate_saw_table(saw_table, 8, 1024);
	populate_pulse_table(pulse_table, 8, 1024);
	float index = 0;
	float index2 = 0;
	int step = 1;
	int end;
	float dur, freq;
	short* control = malloc(sizeof(short) * 256); //A control buffer

	//init_sfile(SFILE, name, sample rate, channels, bits-per-sample, vector size, wavetable length)
	init_sfile(sfout, "test2.wav", SR, 1, 16, 256, 1024);

	dur = 10000;
	freq = 440;
	end = (int) (dur * SR);
	sfout->data_size = end * sizeof(short) * sfout->channels;
	printf("%s\n", "Creating wave file...");
	
	//Write to file
	for (i = 0; i < dur; i++, step++) {
		osc(sfout->buffer, square_table, freq, 16000, &index, SR, sfout);
		sfwrite(sfout);
	}

	//(int)(osc(&control, sin_table, 440, 4000, &index2, 200, sfout))

	for (i = 0; i < 1024; i++) printf("%f--", square_table[i]);
	sfclose(sfout);
	free(sfout->buffer);
	free(sfout->header);
	free(sfout);
	return 0;
}
	