0
2056
0
0
0
0
0
0
MOV SP, 4096
MOV BP, 4096
PUSH R0
CALL 2142
INT 10
PUSH BP
MOV BP, SP
ADD SP, 1
MOV R0, BP
ADD R0, -3
MOV R0, [R0]
MOV R1, 91
GE R0, R1
JZ R0, 2092
MOV R0, 91
MOV R1, 4096
MOV [R1], R0
JMP 2126
MOV R0, BP
ADD R0, -3
MOV R0, [R0]
MOV R1, 11
ADD R0, R1
PUSH R0
PUSH R0
CALL 2066
POP R0
POP R1
PUSH R0
PUSH R0
CALL 2066
POP R0
POP R1
MOV R1, 4096
MOV [R1], R0
MOV R0, 4096
MOV R0, [R0]
MOV R1, BP
SUB R1, 2
MOV [R1], R0
SUB SP, 1
POP BP
RET
PUSH BP
MOV BP, SP
ADD SP, 2
MOV R0, BP
ADD R0, 1
MOV R1, "Read"
PUSH R1
MOV R1, -1
PUSH R1
PUSH R0
PUSH R1
PUSH R1
CALL 0
POP R1
POP R1
POP R1
POP R1
POP R1
MOV R0, BP
ADD R0, 1
MOV R0, [R0]
PUSH R0
PUSH R0
CALL 2066
POP R0
POP R1
MOV R1, BP
ADD R1, 2
MOV [R1], R0
MOV R0, BP
ADD R0, 2
MOV R0, [R0]
MOV R1, "Write"
PUSH R1
MOV R1,-2
PUSH R1
PUSH R0
PUSH R1
PUSH R1
CALL 0
POP R1
POP R1
POP R1
POP R1
POP R1
MOV R0, 0
MOV R1, BP
SUB R1, 2
MOV [R1], R0
SUB SP, 2
POP BP
RET
