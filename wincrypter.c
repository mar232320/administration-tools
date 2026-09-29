#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	DATA_BLOB pdat;
	DATA_BLOB odat;
	DATA_BLOB pwd;
	FILE *f;
	char *fcont;
	char *password;
	char *command[2];
	long long fsz;
	int i;
	short bsetpass;
	short blocal;
	if (argc < 4)
	{
		printf("%s <command> [-p password] [--local] <infile> <outfile>\n", argv[0]);
		puts("<command> - encrypt for encryption | decrypt for decryption");
		puts("[-p password] - optionally provide password for additional entropy");
		puts("[--local] - bind encryption to local machine instead of current user - anyone on this computer can decrypt the file");
		exit(0);
	}
	command[0] = "decrypt";
	command[1] = "encrypt";
	if (strcmp(argv[1], command[0]) && strcmp(argv[1], command[1]))
	{
		puts("invalid command");
		exit(1);
	}
	bsetpass = 0;
	blocal = 0;
	for (i = 1; i < argc; i++)
		if (strcmp(argv[i], "-p") == 0)
		{
			bsetpass = 1;
			password = argv[i + 1];
		}
		else if (strcmp(argv[i], "--local") == 0)
			blocal = 1;
	if (bsetpass)
	{
		pwd.pbData = password;
		pwd.cbData = strlen(password);
	}
	f = fopen(argv[argc - 2], "rb");
	fseek(f, 0, 2);
	fsz = ftell(f);
	fseek(f, 0, 0);
	fcont = malloc(fsz);
	fread(fcont, fsz, 1, f);
	fclose(f);
	pdat.pbData = fcont;
	pdat.cbData = fsz;
	if (strcmp(argv[1], command[0]) == 0)
	{
		if (!CryptUnprotectData(&pdat, NULL, bsetpass ? &pwd : NULL, NULL, NULL, blocal ? 4 : 0, &odat))
			puts("[ERROR] decryption error");
	}
	else
	{
		if (!CryptProtectData(&pdat, NULL, bsetpass ? &pwd : NULL, NULL, NULL, blocal ? 4 : 0, &odat))
			puts("[ERROR] encryption error");
	}
	f = fopen(argv[argc - 1], "wb");
	fwrite(odat.pbData, odat.cbData, 1, f);
	fclose(f);
	free(fcont);
	return 0;
}