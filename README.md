# administration-tools
A collection of tools helping administration and management of Windows and Linux workstations

**Programs:**

credman: Program used to read, write and delete credentials stored on machine by Windows Credential Manager

wincrypter: Program used to encrypt and decrypt files with Windows Data Protection API (DPAPI) Encrypted data could be decrypted only on the same computer (and by the same user if the --local option is not set)
Encryption keys are stored locally. Program uses **crypt32** library - must be compiled with `-l crypt32`

If you receive encryption or decryption error, ensure that you have provided the right password. Also check if you are decrypting the files on the same machine (and by the same user if `--local` option is not used)

portman: Program used to determine used ports on a machine. Lists TCP and UDP ports separately. Used to check which ports are used by running services. Program uses **WinSock2** library - must be compiled with
`-l ws2_32`

All programs could be build with compilation script: `compile.ps1`
