@256
D=A
@SP
M=D
@1015
D=A
@LCL
M=D
@1527
D=A
@ARG
M=D
@3000
D=A
@THIS
M=D
@3010
D=A
@THAT
M=D
@5
D=A
@R5
M=D
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@EQ_if_9
D;JEQ
D=0
@EQ_end_9
0;JMP
(EQ_if_9)
D=-1
(EQ_end_9)
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@EQ_if_12
D;JEQ
D=0
@EQ_end_12
0;JMP
(EQ_if_12)
D=-1
(EQ_end_12)
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@EQ_if_15
D;JEQ
D=0
@EQ_end_15
0;JMP
(EQ_if_15)
D=-1
(EQ_end_15)
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@LT_if_18
D;JLT
D=0
@LT_end_18
0;JMP
(LT_if_18)
D=-1
(LT_end_18)
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@LT_if_21
D;JLT
D=0
@LT_end_21
0;JMP
(LT_if_21)
D=-1
(LT_end_21)
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@LT_if_24
D;JLT
D=0
@LT_end_24
0;JMP
(LT_if_24)
D=-1
(LT_end_24)
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@GT_if_27
D;JGT
D=0
@GT_end_27
0;JMP
(GT_if_27)
D=-1
(GT_end_27)
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@GT_if_30
D;JGT
D=0
@GT_end_30
0;JMP
(GT_if_30)
D=-1
(GT_end_30)
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
D=M-D
@GT_if_33
D;JGT
D=0
@GT_end_33
0;JMP
(GT_if_33)
D=-1
(GT_end_33)
@SP
A=M
M=D
@SP
M=M+1
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M+D
@SP
M=M+1
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M-D
@SP
M=M+1
@SP
AM=M-1
M=-M
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M&D
@SP
M=M+1
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M|D
@SP
M=M+1
@SP
AM=M-1
M=!M
@SP
M=M+1
@LCL
D=M
@0
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@10
D=A
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@1
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
@SP
AM=M-1
M=M+D
@SP
M=M+1
@LCL
D=M
@1
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
