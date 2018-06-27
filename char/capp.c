#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, ret;	
	char buf[64];
	char rdbuf[64];

	fd = open(argv[1], O_RDWR);
	if(fd < 0) {
		perror("Open Failed");
		return -1;
	}
 
	scanf("%s", buf);

	ret = write(fd, buf, strlen(buf));	
	if(ret < 0) {
		perror("write failed\n");
		return -1;
	}
	
	printf("Write succes : %d bytes\n", ret);

	ret = read(fd, rdbuf, 64);
	if(ret < 0) {
		perror("read failed\n");
		return -1;
	}
	printf("Read succes : %d bytes Data: %s\n", ret, rdbuf);

	close(fd);
	return 0;
}
