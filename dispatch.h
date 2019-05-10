
#ifndef _DISPATCH_H_
#define _DISPATCH_H_

void inst_LDI(struct cpu *cpu, unsigned char opA, unsigned char opB);
void inst_PRN(struct cpu *cpu, unsigned char opA);
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

#endif