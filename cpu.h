#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  // registers (array)
  // ram (array)
  unsigned char ram[256];
  unsigned char registers[8];
  unsigned char PC;
  unsigned char FL;
};

// ALU operations
enum alu_op {
	ALU_MUL, // done
	// Add more here
  ALU_PUSH, // done
  ALU_POP, // done
  ALU_ADD, // done
  ALU_DIV, // done
  ALU_SUB, // done
  ALU_INC, // done
  ALU_DEC, // done
  ALU_AND, // done
  ALU_LD,
  ALU_JMP,
  ALU_CMP,
  ALU_ST,
  ALU_OR, // done
  ALU_XOR, // done
  ALU_SHL,
  ALU_SHR,
  ALU_INT,
  ALU_MOD, // done
  ALU_NOT, // done
  ALU_JEQ,
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010 // X Set the value of a register to an integer.
#define HLT  0b00000001 // X Halt the CPU (and exit the emulator).
#define PRN  0b01000111 // X Print numeric value stored in the given register.
// TODO: more instructions here. These can be used in cpu_run().
#define SP 7 // stack pointer
#define ADD  0b10100000 // X Add the value in two registers and store the result in registerA.
#define AND  0b10101000 // X Bitwise-AND the values in registerA and registerB, then store the result in registerA.
#define CALL 0b01010000 // X Calls a subroutine (function) at the address stored in the register.
#define CMP  0b10100111 // X Compare the values in two registers.
#define DEC  0b01100110 // X Decrement (subtract 1 from) the value in the given register.
#define DIV  0b10100011 // X Divide the value in the first register by the value in the second, storing the result in registerA.
#define INC  0b01100101 // X Increment (add 1 to) the value in the given register.
#define INT  0b01010010 // Issue the interrupt number stored in the given register.
#define IRET 0b00010011 // Return from an interrupt handler.
#define JEQ  0b01010101 // X If equal flag is set (true), jump to the address stored in the given register.
#define JGE  0b01011010 // X If greater-than flag or equal flag is set (true), jump to the address stored in the given register.
#define JGT  0b01010111 // X If greater-than flag is set (true), jump to the address stored in the given register.
#define JLE  0b01011001 // X If less-than flag or equal flag is set (true), jump to the address stored in the given register.
#define JLT  0b01011000 // X If less-than flag is set (true), jump to the address stored in the given register.
#define JMP  0b01010100 // X Jump to the address stored in the given register. Set the PC to the address stored in the given register.
#define JNE  0b01010110 // X If E flag is clear (false, 0), jump to the address stored in the given register.
#define LD   0b10000011 // X Loads registerA with the value at the memory address stored in registerB.
#define MOD  0b10100100 // X Divide the value in the first register by the value in the second, storing the remainder of the result in registerA.
#define MUL  0b10100010 // X Multiply the values in two registers together and store the result in registerA.
#define NOP  0b00000000 // No operation. Do nothing for this instruction.
#define NOT  0b01101001 // X Perform a bitwise-NOT on the value in a register.
#define OR   0b10101010 // X Perform a bitwise-OR between the values in registerA and registerB, storing the result in registerA.
#define POP  0b01000110 // X Pop the value at the top of the stack into the given register.
#define PRA  0b01001000 // X Print alpha character value stored in the given register.
#define PUSH 0b01000101 // X Push the value in the given register on the stack.
#define RET  0b00010001 // Return from subroutine. Pop the value from the top of the stack and store it in the PC.
#define SHL  0b10101100 // X Shift the value in registerA left by the number of bits specified in registerB, filling the low bits with 0.
#define SHR  0b10101101 // X Shift the value in registerA right by the number of bits specified in registerB, filling the high bits with 0.
#define ST   0b10000100 // X Store value in registerB in the address stored in registerA.
#define SUB  0b10100001 // X Subtract the value in the second register from the first, storing the result in registerA.
#define XOR  0b10101011 // X Perform a bitwise-XOR between the values in registerA and registerB, storing the result in registerA.



// Function declarations

extern void cpu_load(struct cpu *cpu, int argCount, char *filename);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
