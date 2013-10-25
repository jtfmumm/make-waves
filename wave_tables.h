float* normalize_table(float* table, int length)
{
	int i;
	int max = 0;
	for (i = 0; i < length; i++) {
		if (table[i] > max) max = table[i];
	}
	for (i = 0; i < length; i++) {
		table[i] /= max;
	}
	return table;
}

void fourier_table(float* table, int harmonics, int length, float* amps, float offset)
{
	int i, k;
	float fourier_sum = 0;
	float w;
	for (i = 0; i < length; i++) {
		fourier_sum = 0;
	    for (k = 0; k < harmonics; k++) {
			w = i * (k + 1) * 2 * M_PI / length;
			fourier_sum += (amps[k] * cos(w + offset));
		}
		table[i] = fourier_sum;
	}
	normalize_table(table, 1024);
}

void populate_sin_table(float* table, int length)
{
	int i;
	for (i = 0; i < length; i++) {
		table[i] = sin(i * (M_PI * 2)/length);
	}
}

void populate_square_table(float* table, int harmonics, int length)
{
	int k;
	float amps[length];
	float offset = -(M_PI / 2);
	for (k = 0; k < length; k++) {
		if (k % 2 == 0) {
			amps[k] = 0;
		}
		else {
			amps[k] = 1 / (k + 1);
		}
	}
	fourier_table(table, harmonics, length, amps, offset);
}
 
void populate_saw_table(float* table, int harmonics, int length)
{
	int k;
	float amps[length];
	float offset = -(M_PI / 2);
	for (k = 0; k < length; k++) {
	    amps[k] = 1 / (k + 1);
	}
	fourier_table(table, harmonics, length, amps, offset);
}

void populate_pulse_table(float* table, int harmonics, int length)
{
	int k;
	float amps[length];
	float offset = -(M_PI / 2);
	for (k = 0; k < length; k++) {
	    amps[k] = 1;
	}
	fourier_table(table, harmonics, length, amps, offset);
}

void osc(short* output, float* table, float freq, float amp, float* index, int sample_rate, SFILE* this_sfile)
{
	int length = this_sfile->table_length;
	int vector_size = this_sfile->vector_size;
	float increment = freq * length / sample_rate;
	int i;
	for (i = 0; i < vector_size; i++) {
		output[i] = amp * table[(int) *index];
		*index += increment;
		while (*index >= length) *index -= length;
		while (*index < 0) *index += length;
	}
}

