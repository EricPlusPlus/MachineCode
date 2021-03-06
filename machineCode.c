#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];

void convertToBinary(FILE* output_file) {
	char outputBuffer[BUFFER_SIZE * 8]; 

	int i = 0;
	for(i = 0; i < BUFFER_SIZE; i++) {

		int j = 0;
		for (j = 0; j < 8; j++) {
			char binary_char = ((buffer[i] >> j) & 1) + '0';

			outputBuffer[(i * 8) + j] = binary_char;
		}
	}

	fwrite(outputBuffer, sizeof(char), BUFFER_SIZE * 8, output_file);
}

int main(int argc, char* argv[]) {
	if (argc <= 1) return 0;

	FILE *input_file;
	input_file = fopen(argv[1], "r");

	if (input_file == NULL) {
		printf("File not found!\n");
		return 0;
	}

	FILE *output_file;
	
	if (argc >= 3) {
		output_file = fopen(argv[2], "w");
	}
	else {
		output_file = fopen("machine_code.txt", "w");
	}

	printf("Converting to machine code...\n");
	fseek(input_file, 0, SEEK_END);

	const size_t num_bytes = ftell(input_file);

	fseek(input_file, 0, SEEK_SET);
	size_t chunk = 0;

    while ((chunk = fread(buffer, sizeof(char), BUFFER_SIZE, input_file)) == BUFFER_SIZE) {
		convertToBinary(output_file);
	}

	int i = 0;
	char *lastBuff = malloc(chunk * 8 * sizeof(char));

	for (i = 0; i < chunk; i++) {

		int j = 0;
		for (j = 0; j < 8; j++) {
			char binary_char = ((buffer[i] >> j) & 1) + '0';

			lastBuff[(i * 8) + j] = binary_char;
		}
	}

	fwrite(lastBuff, sizeof(char), chunk * 8, output_file);
	free(lastBuff);
    
    printf("Successfully converted to machine code.\n");
	fclose(input_file);
	fclose(output_file);
	
	return 0;
}
