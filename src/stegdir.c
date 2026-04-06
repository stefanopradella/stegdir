#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "stegdir.h"


int main(int argc, char *argv[]) {
	
	/* Input checks */
	if (argc < 4) {
    	fprintf(stderr, "Usage: \t%s encode <input_file> <output_path>\n"
							   "\t%s decode <input_path> <output_file>\n", argv[0], argv[0]);
        return 1;
    }

	
	/* Check if the input/output arguments already exist */
    struct stat st[2];
	
	for (int i=0; i<2; i++) {
		if (stat(argv[i+2], &st[i]) == -1) {
			/* If file/folder does not exist, mark by setting st_mode to zero */
			st[i].st_mode = 0;
		}
	}

	char* mode = argv[1];
	int retval = 0;

	if (strcmp(mode, "encode") == 0) {
		char *inputFileName = argv[2];
      	char *outputRootDirectory = argv[3];
        
		if (st[1].st_mode != 0){
			printf("Destination folder already exists\n");
			return 1;
		} else if (!S_ISREG(st[0].st_mode)){
			printf("Source file is not a valid file type\n");
			return 1;
		}

		int inputFileDescriptor = open(inputFileName, O_RDONLY);
		if (inputFileDescriptor == -1) {
			perror("Error opening input file");
			return 1;
		}

		retval = stegdir_encode(inputFileDescriptor, outputRootDirectory);

		close(inputFileDescriptor);

	} else if (strcmp(mode, "decode") == 0) {
	
        	char *inputRootDirectory = argv[2];
			char *outputFileName = argv[3];
			
			if (!S_ISDIR(st[0].st_mode)){
				printf("Source folder does not exist\n");
				return 1;
			} else if (st[1].st_mode != 0){
				printf("Destination file already exists\n");
				return 1;
			}

			int outputFileDescriptor = open(outputFileName, O_RDWR | O_CREAT, 0644);
			if (outputFileDescriptor == -1) {
				perror("Error opening input file");
				return 1;
			}

			retval = stegdir_decode(inputRootDirectory, outputFileDescriptor);
			
			close(outputFileDescriptor);

	} else {
		printf("Error: unrecognized mode");
		return 1;
	}

	if (retval) {
	    /* TODO properly handle errors inside decode/encode functions */
		printf("Error executing encode/decode");
		return 1;
	}

	return 0;
}
