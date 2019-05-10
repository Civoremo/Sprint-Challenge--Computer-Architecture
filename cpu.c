#include "cpu.h"
#include "dispatch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argCount, char *filename)
{
  FILE *fp;
  char line[1024];
  int address = 0;

  if (argCount != 2) {
    fprintf(stderr, "usage: ls8 filename\n");
  }

  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "cpu: error opening file\n");
    exit(2);
  }

  while (fgets(line, 1024, fp) != NULL) {
    char *endptr;

    unsigned int val = strtoul(line, &endptr, 2);

    if (endptr == line) {
      continue;
    }

    cpu->ram[address] = val;
    address++;
  }
  fclose(fp);
}

// RAM read
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) {
  return cpu->ram[address];
}

// RAM write
void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) {
  cpu->ram[address] = value;
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_PUSH:
      alu_Push(cpu, regA);
      break;

    case ALU_POP:
    alu_Pop(cpu, regA);
      break;

    case ALU_MUL:
      alu_Mult(cpu, regA, regB);
      break;

    case ALU_DIV:
        alu_Div(cpu, regA, regB);
      break;

    case ALU_ADD:
      alu_Add(cpu, regA, regB);
      break;

    case ALU_SUB:
        alu_Sub(cpu, regA, regB);
      break;

    case ALU_AND:
      alu_And(cpu, regA, regB);
      break;

    case ALU_INC:
      alu_Inc(cpu, regA);
      break;

    case ALU_DEC:
      alu_Dec(cpu, regA);
      break;

    case ALU_XOR:
      alu_Xor(cpu, regA, regB);
      break;

    case ALU_OR:
      alu_Or(cpu, regA, regB);
      break;

    case ALU_MOD:
      alu_Mod(cpu, regA, regB);
      break;

    case ALU_NOT:
      alu_Not(cpu, regA);
      break;

    case ALU_CMP:
      alu_Cmp(cpu, regA, regB);
      break;

    case ALU_SHL:
      alu_Shl(cpu, regA, regB);
      break;

    case ALU_SHR:
      alu_Shr(cpu, regA, regB);
      break;

    default:
      printf("ALU default\n");
      break;
  }
}

void trace(struct cpu *cpu)
{
    printf("%02X | ", cpu->PC);

    printf("%02X %02X %02X |",
        cpu_ram_read(cpu, cpu->PC),
        cpu_ram_read(cpu, cpu->PC + 1),
        cpu_ram_read(cpu, cpu->PC + 2));

    for (int i = 0; i < 8; i++) {
        printf(" %02X", cpu->registers[i]);
    }

    printf("\n");
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    unsigned char current_inst = cpu_ram_read(cpu, cpu->PC);
    unsigned char operandA = cpu_ram_read(cpu, (cpu->PC + 1));
    unsigned char operandB = cpu_ram_read(cpu, (cpu->PC + 2));
    unsigned char operands = current_inst >> 6;

    // trace(cpu);
    
    switch (current_inst) {
      case HLT:
        running = 0;
        break;

      case LDI:
        inst_Ldi(cpu, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case PRN:
        inst_Prn(cpu, operandA);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case PUSH:
        alu(cpu, ALU_PUSH, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case POP:
        alu(cpu, ALU_POP, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case AND:
        alu(cpu, ALU_AND, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case CALL:
        inst_Call(cpu);
        break;

      case CMP:
        alu(cpu, ALU_CMP, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case DEC:
        alu(cpu, ALU_DEC, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case DIV:
        alu(cpu, ALU_DIV, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case INC:
        alu(cpu, ALU_INC, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case IRET:
        break;

      case JEQ:
        inst_Jeq(cpu, operandA, operands);
        break;

      case JGE:
        inst_Jge(cpu, operandA, operands);
        break;

      case JGT:
        inst_Jgt(cpu, operandA, operands);
        break;

      case JLE:
        inst_Jle(cpu, operandA, operands);
        break;

      case JLT:
        inst_Jlt(cpu, operandA, operands);
        break;

      case JMP:
        inst_Jmp(cpu, operandA);
        break;

      case JNE:
        inst_Jne(cpu, operandA, operands);
        break;

      case LD:
        inst_Ld(cpu, operandA, operandB, operands);
        break;

      case MOD:
        alu(cpu, ALU_MOD, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case NOP:
        cpu->PC = cpu->PC + operands + 1;
        break;

      case NOT:
        alu(cpu, ALU_NOT, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case OR:
        alu(cpu, ALU_OR, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case RET:
        inst_Ret(cpu);
        break;

      case SHL:
        alu(cpu, ALU_SHL, operandA, operandB);
        break;

      case SHR:
        alu(cpu, ALU_SHR, operandA, operandB);
        break;

      case ST:
        cpu->ram[operandA] = cpu->ram[operandB];
        cpu->PC = cpu->PC + operands + 1;
        break;

      case SUB:
        alu(cpu, ALU_SUB, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case XOR:
        alu(cpu, ALU_XOR, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case PRA:
        printf("%c", cpu->ram[cpu->registers[operandA]]);
        cpu->PC = cpu->PC + operands + 1;
        break;

      default:
        printf("DEFAULT\n");
        break;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  memset(cpu->registers, 0, sizeof(cpu->registers));
  cpu->registers[SP] = 0xF4;
  cpu->PC = 0;
  cpu->FL = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
