#include "cpu.h"
#include "dispatch.h"
#include <stdio.h>
#include <stdlib.h>

void inst_Ldi(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = opB;
}

void inst_Prn(struct cpu *cpu, unsigned char opA)
{
  printf("%d\n", cpu->registers[opA]);
}

void alu_Push(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[SP]--;
  int val = cpu->registers[opA];
  cpu->ram[cpu->registers[SP]] = val;
}

void alu_Pop(struct cpu *cpu, unsigned char opA)
{
  int val = cpu->ram[cpu->registers[SP]];
  cpu->registers[opA] = val;
  cpu->registers[SP]++;
}

void alu_Mult(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] *= cpu->registers[opB];
}

void alu_Div(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  if (cpu->registers[opB] != 0) {
    // alu_Div(cpu, opA, opB);
    cpu->registers[opA] = cpu->registers[opA] / cpu->registers[opB];
  } else {
    fprintf(stderr, "DIV: can't divide by 0\n");
    exit(1);
  }
}

void alu_Add(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] += cpu->registers[opB];
}

void alu_Sub(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] -= cpu->registers[opB];
}

void alu_And(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] & cpu->registers[opB];
}

void alu_Inc(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] += 1;
}

void alu_Dec(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] -= 1;
}

void alu_Xor(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] ^ cpu->registers[opB];
}

void alu_Or(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] | cpu->registers[opB];
}

void alu_Mod(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] % cpu->registers[opB];
}

void alu_Not(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] = ~cpu->registers[opA];
}

void alu_Cmp(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  unsigned char tempFL = 0;
  if (cpu->registers[opA] == cpu->registers[opB]) {
    // printf("E\n");
    cpu->FL = tempFL | 0b00000001;
  } else if (cpu->registers[opA] < cpu->registers[opB]) {
    // printf("L\n");
    cpu->FL = tempFL | 0b00000100;
  } else if (cpu->registers[opA] > cpu->registers[opB]) {
    // printf("G\n");
    cpu->FL = tempFL | 0b00000010;
  } else {
    cpu->FL = tempFL;
  }
}

void inst_Call(struct cpu *cpu) 
{
  cpu->registers[SP]--;
  cpu->ram[cpu->registers[SP]] = cpu->PC + 2;
  cpu->PC = cpu->registers[cpu->ram[cpu->PC + 1]];
}

void inst_Jeq(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  if (cpu->FL == 1) {
    cpu->PC = cpu->registers[opA];
  } else {

    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Jle(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  if (cpu->FL == 4 || cpu->FL == 1) {
    cpu->PC = cpu->registers[opA];
  } else {
    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Jge(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  if (cpu->FL == 2 || cpu->FL == 1) {
    cpu->PC = cpu->registers[opA];
  } else {
    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Jgt(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  if (cpu->FL == 2) {
    cpu->PC = cpu->registers[opA];
  } else {
    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Jlt(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  if (cpu->FL == 4) {
    cpu->PC = cpu->registers[opA];
  } else {
    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Jmp(struct cpu *cpu, unsigned char opA)
{
  cpu->PC = cpu->registers[opA];
}

void inst_Jne(struct cpu *cpu, unsigned char opA, unsigned char operands)
{
  unsigned char temp = cpu->FL << 7;
  temp = temp >> 7;

  if (temp == 0) {
    cpu->PC = cpu->registers[opA];
  } else {
    cpu->PC = cpu->PC + operands + 1;
  }
}

void inst_Ld(struct cpu *cpu, unsigned char opA, unsigned char opB, unsigned char operands)
{
  cpu->registers[opA] = cpu->registers[opB];
  cpu->PC = cpu->PC + operands + 1;
}

void inst_Ret(struct cpu *cpu)
{
  unsigned char return_addr = cpu->ram[cpu->registers[SP]];
  cpu->registers[SP]++;
  cpu->PC = return_addr;
}

void alu_Shl(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = (cpu->registers[opA] << opB);
}

void alu_Shr(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = (cpu->registers[opA] >> opB);
}