# administration-tools
A collection of tools helping administration and management of Windows and Linux workstations

**Programs:**

wincrypter: Program used to encrypt and decrypt files with Windows Data Protection API (DPAPI) Encrypted data could be decrypted only on the same computer (and by the same user if the --local option is not set)
Encryption keys are stored locally. Program uses **crypt32** library - must be compiled with `-l crypt32`

portman: Program used to determine used ports on a machine. Lists TCP and UDP ports separately. Used to check which ports are used by running services. Program uses **WinSock2** library - must be compiled with
`-l ws2_32`

All programs could be build with compilation script: `compile.ps1`
