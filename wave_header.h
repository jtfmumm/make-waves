typedef struct header_wave {
	int RIFF; //"RIFF" chunk
	int file_size; //Size of whole file in bytes (minus 8)
	int WAVE; //"WAVE"
	int FMT; //"fmt " chunk. Remember trailing " "... value should be "fmt "
	int format_size; // Size of format chunk (16 in this case)
	short format_type; // 1 for PCM (pulse code modulation)
	short channels; // Number of channels
	int sample_rate; // e.g. 44100
	int byterate; // (sample_rate * bits_per_sample * channels) / 8
	short block_align; // (bits_per_sample * channels) / 8 
	short bits_per_sample; // e.g. 8 for 8-bit, 16 for 16-bit
	int DATA; // "data" chunk
	int data_size; // Size of data section of file in bytes
} wave_header;

static char RIFF_LIST[4] = {'R','I','F','F'};
static char WAVE_LIST[4] = {'W','A','V','E'};
static char FMT_LIST[4] = {'f','m','t',' '};
static char DATA_LIST[4] = {'d','a','t','a'};

void update_header(wave_header* header, int sample_rate, short bits_per_sample, short channels, int data_size) 
{
	header->RIFF = (*(long *) RIFF_LIST); //"RIFF" chunk
	header->file_size = data_size + sizeof(wave_header) - 8; //Size of whole file in bytes (minus 8)
	header->WAVE = (*(long *) WAVE_LIST); //"WAVE"
	header->FMT = (*(long *) FMT_LIST); //"fmt " chunk. Remember trailing " "... value should be "fmt "
	header->format_size = 16; // Size of format chunk (16 in this case)
	header->format_type = 1; // 1 for PCM (pulse code modulation)
	header->channels = channels; // Number of channels
	header->sample_rate = sample_rate; // e.g. 44100
	header->byterate = (sample_rate * bits_per_sample * channels) / 8; // (sample_rate * bits_per_sample * channels) / 8
	header->block_align = (bits_per_sample * channels) / 8; // (bits_per_sample * channels) / 8 
	header->bits_per_sample = bits_per_sample; // e.g. 8 for 8-bit, 16 for 16-bit
	header->DATA = (*(long *) DATA_LIST); // "data" chunk
	header->data_size = data_size; // Size of data section of file in bytes
}