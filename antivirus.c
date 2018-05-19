#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	
	if (argc < 4) { 
		printf("Usage: host port dir [dir]\n");
		return 0;
	}
	int port;
	int r = sscanf(argv[2], "%d", &port);
	if(!r){
		printf("Port must be integer\n");
		return 2;
	}

	return 0;
}