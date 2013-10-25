float* populate_sin_table(float* table, int length)
{
	int i;
	for (i = 0; i < length; i++) {
		table[i] = sin(i * (M_PI * 2)/length);
	}
	return table;
}
 
float osc(float* table, float freq, float amp, float* index, int sample_rate, int length)
{
	float output;
	output = amp * table[(int) *index];
	*index += freq * length / sample_rate;
	while (*index >= length) *index -= length;
	while (*index < 0) *index += length;
	return output;
}

