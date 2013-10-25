#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave_header.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264
#endif

int SR = 44100; 

float fourier_series(int, int, float(*)(int), float(*)(int));
float saw_fourier_amp(int);
float square_fourier_amp(int);
float triangle_fourier_amp(int);
float pulse_fourier_amp(int);
float standard_fourier_offset(int);

int main(int argc, char ** argv)
{
	int i, j;
	FILE* fout;
	wave_header* header; 
	float twopi = 2 * M_PI;
	int step = 1;
	int blockframes = 256;
	short *audioblock;
	int end;
	int sample_rate, channels, bits_per_sample, data_size;
	float dur, freq;

	header = (wave_header *) malloc(sizeof(wave_header));
	audioblock = (short *) malloc(sizeof(short) * blockframes);
	fout = fopen("test.wav", "wb");
	dur = 10;
	freq = 220;
	sample_rate = SR;
	channels = 1;
	bits_per_sample = 16;
	end = (int) (dur * sample_rate);
	data_size = end * sizeof(short) * channels;
	update_header(header, sample_rate, bits_per_sample, channels, data_size);
	printf("%s\n", "Creating wave file...");
	
	//Write to file
	fwrite(header, 1, sizeof(wave_header), fout);
	for (i = 0; i < end; i += blockframes) {
		for (j = 0; j < blockframes; j++, step++) {
			//audioblock[j] = 16000 * sin(step * twopi * freq/SR);
			audioblock[j] = 16000 * fourier_series(freq, step, &triangle_fourier_amp, &standard_fourier_offset); 
		}
		fwrite(audioblock, sizeof(short), blockframes, fout);
	}

	free(audioblock);
	free(header);
	fclose(fout);
	return 0;
}

float fourier_series(int freq, int step, float (*amp_func_ptr)(int), float (*offset_func_ptr)(int)) 
{
	int k;
	float amp, offset;
	float fourier_sum = 0;
	int harmonics = 8;
	short max_freq = (short) (SR / 2);	//Max frequency
    for (k = 1; k <= harmonics; k++) {
		amp = amp_func_ptr(k);
		offset = offset_func_ptr(k);
		//fourier_sum += sin(k);
		if ((k * freq) <= max_freq)
			fourier_sum += (amp * cos((k * freq * step) + offset));
	}
	return fourier_sum;
}

float saw_fourier_amp(int k)
{
	return 1 / k;
}

float square_fourier_amp(int k)
{
	if (k % 2 == 0)
		return 0;
	else
		return 1 / k;
}

float triangle_fourier_amp(int k)
{
	if (k % 2 == 0)
		return 0;
	else
		return 1 / (k * k);
}

float pulse_fourier_amp(int k)
{
	return 1;
}

float standard_fourier_offset(int k)
{
	return -(M_PI / 2);
}
