
#ifndef _DISPATCH_H_
#define _DISPATCH_H_

void inst_Ldi(struct cpu *cpu, unsigned char opA, unsigned char opB);
void inst_Prn(struct cpu *cpu, unsigned char opA);
void alu_Push(struct cpu *cpu, unsigned char opA);
void alu_Pop(struct cpu *cpu, unsigned char opA);
void alu_Mult(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Div(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Add(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Sub(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_And(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Inc(struct cpu *cpu, unsigned char opA);
void alu_Dec(struct cpu *cpu, unsigned char opA);
void alu_Xor(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Or(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Mod(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Not(struct cpu *cpu, unsigned char opA);
void alu_Cmp(struct cpu *cpu, unsigned char opA, unsigned char opB);
void inst_Call(struct cpu *cpu);
void inst_Jeq(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Jle(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Jge(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Jgt(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Jlt(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Jmp(struct cpu *cpu, unsigned char opA);
void inst_Jne(struct cpu *cpu, unsigned char opA, unsigned char operands);
void inst_Ld(struct cpu *cpu, unsigned char opA, unsigned char opB, unsigned char operands);
void inst_Ret(struct cpu *cpu);
void alu_Shl(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Shr(struct cpu *cpu, unsigned char opA, unsigned char opB);

#endif