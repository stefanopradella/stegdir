#define URLMODE_ENCODING 1

int stegdir_encode(int inputFileDescriptor, char* outputFolderName);
int stegdir_decode(char* inputFolderName, int outputFileDescriptor);
