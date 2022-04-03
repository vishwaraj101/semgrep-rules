// Marco Ivaldi <raptor@0xdeadbeef.info>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFSIZE 256

int bad1(char *string)
{
	char buf[BUFSIZE];

	strncpy(buf, string, BUFSIZE);
	// ruleid: raptor-off-by-one
	buf[BUFSIZE] = '\0';
}

int good1(char *string)
{
	char buf[BUFSIZE];

	strncpy(buf, string, BUFSIZE);
	// ok: raptor-off-by-one
	buf[BUFSIZE - 1] = '\0';
}

int bad2(char *string)
{
	char firstname[20];
	char lastname[20];
	char fullname[40];

	fullname[0] = '\0';

	// ruleid: raptor-off-by-one
	strncat(fullname, firstname, 20);
}

int good2(char *string)
{
	char firstname[20];
	char lastname[20];
	char fullname[40];

	fullname[0] = '\0';

	// ok: raptor-off-by-one
	strncat(fullname, firstname, sizeof(fullname) - strlen(fullname) - 1);
}

int bad3(char *string)
{
	char filename[BUFSIZE];

	// ruleid: raptor-off-by-one
	for (int i = 0; i <= BUFSIZE; i++) {
		char c = getc();
		if (c == 'EOF') {
			filename[i] = '\0';
		}
		filename[i] = getc(stdin);
	}
}

int good3(char *string)
{
	char filename[BUFSIZE];

	// ok: raptor-off-by-one
	for (int i = 0; i < BUFSIZE; i++) {
		char c = getc();
		if (c == 'EOF') {
			filename[i] = '\0';
		}
		filename[i] = getc(stdin);
	}
}

int processRawStr(uint8_t *s, size_t sz) 
{
	uint8_t buf[1024];
	memset(buf, 0x0, sizeof(buf));
	memcpy(buf, s, sizeof(buf));
	// ruleid: raptor-off-by-one
	buf[sizeof(buf)] = '\0';
	// ...
}

int main() 
{
	printf("Hello, World!");
	return 0;
}
