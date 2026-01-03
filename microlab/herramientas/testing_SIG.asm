JMP seguir

seguir:
SET R0, 0xFF

siguiente:
SIG R0
JC siguiente

halt:
JMP halt
