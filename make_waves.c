#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave_header.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264
#endif

int main(int argc, char ** argv)
{
	int i, j, k;
	FILE* fout;
	wave_header* header; 
	float twopi = 2 * M_PI;
	int step = 0;
	int blockframes = 256;
	short *audioblock;
	int end;
	int sample_rate, channels, bits_per_sample, data_size;
	float dur, freq;

	header = (wave_header *) malloc(sizeof(wave_header));
	audioblock = (short *) malloc(sizeof(short) * blockframes);
	fout = fopen("test.wav", "wb");
	dur = 100;
	freq = 440;
	sample_rate = 44100;
	channels = 1;
	bits_per_sample = 16;
	end = (int) (dur * sample_rate);
	data_size = end * sizeof(short) * channels;
	update_header(header, sample_rate, bits_per_sample, channels, data_size);
	printf("%d\n", header->sample_rate);
	
	//Write to file
	fwrite(header, 1, sizeof(wave_header), fout);
	for (i = 0; i < dur; i++) {
		for (k = 0; k < sample_rate; k += blockframes) {
			for (j = 0; j < blockframes; j++, step++) {
				audioblock[j] = 16000 * sin(step * twopi * freq/sample_rate);
			}
			fwrite(audioblock, sizeof(short), blockframes, fout);
		}
		freq = freq * 2/3;
		if (freq < 100) freq = 880;
	}

	free(audioblock);
	free(header);
	fclose(fout);
	return 0;
}

