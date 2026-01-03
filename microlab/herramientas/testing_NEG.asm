JMP seguir

seguir:
SET R0, 0x34

siguiente:
NEG R0, 
JN siguiente

halt:
JMP halt
