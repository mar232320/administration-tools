#include <windows.h>
#include <wincred.h>
#include <string.h>
#include <stdio.h>

inline static void dispf(char *x, char *buf)
{
	if (buf)
		printf(x, buf);
}

inline static void dispblob(char *blob, int siz)
{
	int i;
	for (i = 0; i < siz; i++)
		if (blob[i])
			printf("%c", blob[i]);
	puts("");
}

void readcred(char *name)
{
	PCREDENTIALA pc;
	if (CredRead(name, 1, 0, &pc))
	{
		dispf("Name = %s\n", pc->TargetName);
		dispf("Username = %s\n", pc->UserName);
		printf("Credential content = ");
		dispblob(pc->CredentialBlob, pc->CredentialBlobSize);
	}
	else
		printf("Failed to get credential %s\n", name);
}

void writecred(char *name, char *username, char *val)
{
	PCREDENTIALA pc;
	pc = malloc(sizeof(CREDENTIALA));
	memset(pc, 0, sizeof(CREDENTIALA));
	pc->Type = 1;
	pc->TargetName = name;
	pc->CredentialBlob = val;
	pc->CredentialBlobSize = strlen(val);
	pc->Persist = 3;
	pc->UserName = username;
	if (CredWrite(pc, 0))
		printf("Successfully written credential %s\n", name);
	else
		printf("Failed to write credential %s\n", name);
	free(pc);
}

void deletecred(char *name)
{
	if (CredDelete(name, 1, 0))
		printf("Successfully deleted credential %s\n", name);
	else
		printf("Failed to delete credential %s\n", name);
}

int main(int argc, char ** argv)
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s read <name> - read credential\n", argv[0]);
		printf("%s write <name> <username> <value> - write credential\n", argv[0]);
		printf("%s delete <name> - delete credential\n", argv[0]);
		exit(0);
	}
	
	if (strcmp(argv[1], "read") == 0)
		readcred(argv[2]);
	else if (strcmp(argv[1], "write") == 0)
		writecred(argv[2], argv[3], argv[4]);
	else if (strcmp(argv[1], "delete") == 0)
		deletecred(argv[2]);
	else
		puts("[ERROR] Invalid command!");
	
	return 0;
}