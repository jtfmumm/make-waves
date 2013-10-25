#include "wave_header.h"

//

typedef struct sound_file {
	char* name; //Name of file
	FILE* sfout; //The file pointer
	wave_header* header; //Header information
	int sample_rate; 
	int channels;
	int vector_size; //Write in chunks (vectors)
	short* buffer; //Buffer for each stage of writing
	int data_size; //Size of data section of file in bytes
	int bits_per_sample; //For header
} SFILE;

void init_sfile(SFILE* this_sfile, char* name, int sample_rate, int channels, int bits_per_sample, int vector_size)
{
	this_sfile->header = malloc(sizeof(wave_header));
	this_sfile->name = name;
	this_sfile->sample_rate = sample_rate;
	this_sfile->channels = channels;
	this_sfile->vector_size = vector_size;
	this_sfile->sfout = fopen(this_sfile->name, "wb");
	this_sfile->buffer = malloc(sizeof(short) * this_sfile->vector_size);
	this_sfile->bits_per_sample = bits_per_sample; //8 for 8-bit, 16 for 16-bit, etc.

	//Write header for file (to be overwritten later once data_size is known)
	update_header(this_sfile->header, this_sfile->sample_rate, this_sfile->bits_per_sample, this_sfile->channels, 0 /*to be overwritten by datasize*/);
	fwrite(this_sfile->header, 1, sizeof(wave_header), this_sfile->sfout);
}

void sfwrite(SFILE* this_sfile)
{
	//the sizeof(short) hard codes 16 bits-per-sample
	fwrite(this_sfile->buffer, sizeof(short), this_sfile->vector_size, this_sfile->sfout);
}

void sfclose(SFILE* this_sfile)
{
	//Overwrite data_size slot in header, then close file
	fclose(this_sfile->sfout);
	fopen(this_sfile->name, "r+"); //Prepare to overwrite beginning of file (hence r+)
	update_header(this_sfile->header, this_sfile->sample_rate, this_sfile->bits_per_sample, this_sfile->channels, this_sfile->data_size);
	fwrite(this_sfile->header, 1, sizeof(wave_header), this_sfile->sfout);
	fclose(this_sfile->sfout);
}

