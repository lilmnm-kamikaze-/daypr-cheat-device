//Mips.h
#define S 0
#define T 1
#define D 2
unsigned char mipsNum[16];
unsigned char *mipsRegisterArray[]={"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"};

void mipsRegister(unsigned int a_opcode, unsigned char a_slot, unsigned char a_more)
{
  a_opcode=(a_opcode>>(6+(5*(3-a_slot)))) & 0x1F;
  strcat(buffer, mipsRegisterArray[a_opcode]);
  
  if(a_more) strcat(buffer, ", ");
}

void mipsNibble(unsigned int a_opcode, unsigned char a_slot, unsigned char a_more)
{
  a_opcode=(a_opcode>>(6+(5*(3-a_slot)))) & 0x1F;
  sprintf(mipsNum, "$%X", a_opcode);
  strcat(buffer, mipsNum);
  
  if(a_more) strcat(buffer, ", ");
}

void mipsImm(unsigned int a_opcode, unsigned char a_slot, unsigned char a_more)
{
  if(a_slot)
  {
    a_opcode&=0x3FFFFFF;
    sprintf(mipsNum, "$%08X", ((a_opcode<<2)));
  }
  else 
  {
    a_opcode&=0xFFFF;
    sprintf(mipsNum, "$%04X", a_opcode);
  }
  strcat(buffer, mipsNum);
  
  if(a_more) strcat(buffer, ", ");
}


void mipsDecode(unsigned int a_opcode)
{
  //Handle opcode
  switch((a_opcode & 0xFC000000) >> 26)
  {
    case 0x00:
      switch(a_opcode & 0x3F)
      {
        case 0x00:
          if(a_opcode == 0)
          {
            sprintf(buffer, "nop      ");
/*NOOP -- no operation
Description: Performs no operation.
Operation: advance_pc (4);
Syntax: noop
Encoding: 0000 0000 0000 0000 0000 0000 0000 0000*/
          }
          else
          {
            sprintf(buffer, "sll      ");
            mipsRegister(a_opcode, 2, 1);
            mipsRegister(a_opcode, 1, 1);
            mipsNibble(a_opcode, 3, 0);
/*SLL -- Shift left logical
Description: Shifts a register value left by the shift amount listed in the instruction and places the result in a third register. Zeroes are shifted in.
Operation: $d = $t << h; advance_pc (4);
Syntax: sll $d, $t, h
Encoding: 0000 00ss ssst tttt dddd dhhh hh00 0000*/
          }
          break;
          
        case 0x02:
          sprintf(buffer, "srl      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 1, 1);
          mipsNibble(a_opcode, 3, 0);
/*SRL -- Shift right logical
Description: Shifts a register value right by the shift amount (shamt) and places the value in the destination register. Zeroes are shifted in.
Operation: $d = $t >> h; advance_pc (4);
Syntax: srl $d, $t, h
Encoding: 0000 00-- ---t tttt dddd dhhh hh00 0010*/
          break;

        case 0x03:
          sprintf(buffer, "sra      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 1, 1);
          mipsNibble(a_opcode, 3, 0);
/*SRA -- Shift right arithmetic
Description: Shifts a register value right by the shift amount (shamt) and places the value in the destination register. The sign bit is shifted in.
Operation: $d = $t >> h; advance_pc (4);
Syntax: sra $d, $t, h
Encoding: 0000 00-- ---t tttt dddd dhhh hh00 0011*/
          break;
          
        case 0x04:
          sprintf(buffer, "sllv     ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 1, 1);
          mipsRegister(a_opcode, 0, 0);
/*SLLV -- Shift left logical variable
Description: Shifts a register value left by the value in a second register and places the result in a third register. Zeroes are shifted in.
Operation: $d = $t << $s; advance_pc (4);
Syntax: sllv $d, $t, $s
Encoding: 0000 00ss ssst tttt dddd d--- --00 0100*/
          break;
    
        case 0x06:
          sprintf(buffer, "srlv     ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 1, 1);
          mipsRegister(a_opcode, 0, 0);
/*SRLV -- Shift right logical variable
Description: Shifts a register value right by the amount specified in $s and places the value in the destination register. Zeroes are shifted in.
Operation: $d = $t >> $s; advance_pc (4);
Syntax: srlv $d, $t, $s
Encoding: 0000 00ss ssst tttt dddd d000 0000 0110*/
          break;
          
        case 0x08:
          sprintf(buffer, "jr       ");
          mipsRegister(a_opcode, 0, 0);
/*JR -- Jump register
Description: Jump to the address contained in register $s
Operation: PC = nPC; nPC = $s;
Syntax: jr $s
Encoding: 0000 00ss sss0 0000 0000 0000 0000 1000*/
          break;
          
        case 0x0C:
          sprintf(buffer, "syscall  ");
/*SYSCALL -- System call
Description: Generates a software interrupt.
Operation: advance_pc (4);
Syntax: syscall
Encoding: 0000 00-- ---- ---- ---- ---- --00 1100*/
          break;
          
        case 0x10:
          sprintf(buffer, "mfhi     ");
          mipsRegister(a_opcode, 2, 0);
/*MFHI -- Move from HI
Description: The contents of register HI are moved to the specified register.
Operation: $d = $HI; advance_pc (4);
Syntax: mfhi $d
Encoding: 0000 0000 0000 0000 dddd d000 0001 0000*/
          break;
          
        case 0x12:
          sprintf(buffer, "mflo     ");
          mipsRegister(a_opcode, 2, 0);
/*MFLO -- Move from LO
Description: The contents of register LO are moved to the specified register.
Operation: $d = $LO; advance_pc (4);
Syntax: mflo $d
Encoding: 0000 0000 0000 0000 dddd d000 0001 0010*/
          break;
          
        case 0x18:
          sprintf(buffer, "mult     ");
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*MULT -- Multiply
Description: Multiplies $s by $t and stores the result in $LO.
Operation: $LO = $s * $t; advance_pc (4);
Syntax: mult $s, $t
Encoding: 0000 00ss ssst tttt 0000 0000 0001 1000*/
          break;
          
        case 0x19:
          sprintf(buffer, "multu    ");
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*MULTU -- Multiply unsigned
Description: Multiplies $s by $t and stores the result in $LO.
Operation: $LO = $s * $t; advance_pc (4);
Syntax: multu $s, $t
Encoding: 0000 00ss ssst tttt 0000 0000 0001 1001*/
          break;
          
        case 0x1A:
          sprintf(buffer, "div      ");
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*DIV -- Divide
Description: Divides $s by $t and stores the quotient in $LO and the remainder in $HI
Operation: $LO = $s / $t; $HI = $s % $t; advance_pc (4);
Syntax: div $s, $t
Encoding: 0000 00ss ssst tttt 0000 0000 0001 1010*/
          break;
          
        case 0x1B:
          sprintf(buffer, "divu     ");
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*DIVU -- Divide unsigned
Description: Divides $s by $t and stores the quotient in $LO and the remainder in $HI
Operation: $LO = $s / $t; $HI = $s % $t; advance_pc (4);
Syntax: divu $s, $t
Encoding: 0000 00ss ssst tttt 0000 0000 0001 1011*/
          break;
          
        case 0x20:
          sprintf(buffer, "add      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*ADD -- Add
Description: Adds two registers and stores the result in a register
Operation: $d = $s + $t; advance_pc (4);
Syntax: add $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0000 */
          break;
          
        case 0x21:
          sprintf(buffer, "addu     ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*ADDU -- Add unsigned
Description: Adds two registers and stores the result in a register
Operation: $d = $s + $t; advance_pc (4);
Syntax: addu $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0001*/
          break;
          
        case 0x22:
          sprintf(buffer, "sub      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*SUB -- Subtract
Description: Subtracts two registers and stores the result in a register
Operation: $d = $s - $t; advance_pc (4);
Syntax: sub $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0010*/
          break;
          
        case 0x23:
          sprintf(buffer, "subu     ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*SUBU -- Subtract unsigned
Description: Subtracts two registers and stores the result in a register
Operation: $d = $s - $t; advance_pc (4);
Syntax: subu $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0011*/
          break;
          
        case 0x24:
          sprintf(buffer, "and      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*AND -- Bitwise and
Description: Bitwise ands two registers and stores the result in a register
Operation: $d = $s & $t; advance_pc (4);
Syntax: and $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0100*/
          break;
          
        case 0x25:
          sprintf(buffer, "or       ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*OR -- Bitwise or
Description: Bitwise logical ors two registers and stores the result in a register
Operation: $d = $s | $t; advance_pc (4);
Syntax: or $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 0101*/
          break;
          
        case 0x26:
          sprintf(buffer, "xor      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*The syscall instruction is described in more detail on the System Calls page.
XOR -- Bitwise exclusive or
Description: Exclusive ors two registers and stores the result in a register
Operation: $d = $s ^ $t; advance_pc (4);
Syntax: xor $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d--- --10 0110*/
          break;
          
        case 0x2A:
          sprintf(buffer, "slt      ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*SLT -- Set on less than (signed)
Description: If $s is less than $t, $d is set to one. It gets zero otherwise.
Operation: if $s < $t $d = 1; advance_pc (4); else $d = 0; advance_pc (4);
Syntax: slt $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 1010*/
          break;
          
        case 0x2B:
          sprintf(buffer, "sltu     ");
          mipsRegister(a_opcode, 2, 1);
          mipsRegister(a_opcode, 0, 1);
          mipsRegister(a_opcode, 1, 0);
/*SLTU -- Set on less than unsigned
Description: If $s is less than $t, $d is set to one. It gets zero otherwise.
Operation: if $s < $t $d = 1; advance_pc (4); else $d = 0; advance_pc (4);
Syntax: sltu $d, $s, $t
Encoding: 0000 00ss ssst tttt dddd d000 0010 1011*/
          break;
        default:
          sprintf(buffer, "???      ");
      }
      break;
      
    case 0x01:
      switch((a_opcode & 0x1F0000) >> 16)
      {
          case 0x00:
            sprintf(buffer, "bltz     ");
            mipsRegister(a_opcode, S, 1);
            mipsImm(a_opcode, 0, 0);
/*BLTZ -- Branch on less than zero
Description: Branches if the register is less than zero
Operation: if $s < 0 advance_pc (offset << 2)); else advance_pc (4);
Syntax: bltz $s, offset
Encoding: 0000 01ss sss0 0000 iiii iiii iiii iiii*/
            break;
            
          case 0x01:
            sprintf(buffer, "bgez     ");
            mipsRegister(a_opcode, S, 1);
            mipsImm(a_opcode, 0, 0);
/*BGEZ -- Branch on greater than or equal to zero
Description: Branches if the register is greater than or equal to zero
Operation: if $s >= 0 advance_pc (offset << 2)); else advance_pc (4);
Syntax: bgez $s, offset
Encoding: 0000 01ss sss0 0001 iiii iiii iiii iiii*/
            break;
          case 0x10:
            sprintf(buffer, "bltzal   ");
            mipsRegister(a_opcode, S, 1);
            mipsImm(a_opcode, 0, 0);
/*BLTZAL -- Branch on less than zero and link
Description: Branches if the register is less than zero and saves the return address in $31
Operation: if $s < 0 $31 = PC + 8 (or nPC + 4); advance_pc (offset << 2)); else advance_pc (4);
Syntax: bltzal $s, offset
Encoding: 0000 01ss sss1 0000 iiii iiii iiii iiii*/
            break;
            
          case 0x11:
            sprintf(buffer, "bgezal   ");
            mipsRegister(a_opcode, S, 1);
            mipsImm(a_opcode, 0, 0);
/*BGEZAL -- Branch on greater than or equal to zero and link
Description: Branches if the register is greater than or equal to zero and saves the return address in $31
Operation: if $s >= 0 $31 = PC + 8 (or nPC + 4); advance_pc (offset << 2)); else advance_pc (4);
Syntax: bgezal $s, offset
Encoding: 0000 01ss sss1 0001 iiii iiii iiii iiii*/
            break;
          default:
            sprintf(buffer, "???      ");
      }
      break;
      
    case 0x02:
      sprintf(buffer, "j        ");
      mipsImm(a_opcode, 1, 0);
/*J -- Jump
Description: Jumps to the calculated address
Operation: PC = nPC; nPC = (PC & 0xf0000000) | (target << 2);
Syntax: j target
Encoding: 0000 10ii iiii iiii iiii iiii iiii iiii*/
      break;
      
    case 0x03:
      sprintf(buffer, "jal      ");
      mipsImm(a_opcode, 1, 0);
/*JAL -- Jump and link
Description: Jumps to the calculated address and stores the return address in $31
Operation: $31 = PC + 8 (or nPC + 4); PC = nPC; nPC = (PC & 0xf0000000) | (target << 2);
Syntax: jal target
Encoding: 0000 11ii iiii iiii iiii iiii iiii iiii*/
      break;
      
    case 0x04:
      sprintf(buffer, "beq      ");
      mipsRegister(a_opcode, S, 1);
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
/*BEQ -- Branch on equal
Description: Branches if the two registers are equal
Operation: if $s == $t advance_pc (offset << 2)); else advance_pc (4);
Syntax: beq $s, $t, offset
Encoding: 0001 00ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x05:
      sprintf(buffer, "bne      ");
      mipsRegister(a_opcode, S, 1);
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
/*BNE -- Branch on not equal
Description: Branches if the two registers are not equal
Operation: if $s != $t advance_pc (offset << 2)); else advance_pc (4);
Syntax: bne $s, $t, offset
Encoding: 0001 01ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x06:
      sprintf(buffer, "blez     ");  
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*BLEZ -- Branch on less than or equal to zero
Description: Branches if the register is less than or equal to zero
Operation: if $s <= 0 advance_pc (offset << 2)); else advance_pc (4);
Syntax: blez $s, offset
Encoding: 0001 10ss sss0 0000 iiii iiii iiii iiii*/
      break;
      
    case 0x07:
      sprintf(buffer, "bgtz     ");
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*BGTZ -- Branch on greater than zero
Description: Branches if the register is greater than zero
Operation: if $s > 0 advance_pc (offset << 2)); else advance_pc (4);
Syntax: bgtz $s, offset
Encoding: 0001 11ss sss0 0000 iiii iiii iiii iiii*/
      break;
      
    case 0x08:
      sprintf(buffer, "addi     ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*ADDI -- Add immediate
Description: Adds a register and a signed immediate value and stores the result in a register
Operation: $t = $s + imm; advance_pc (4);
Syntax: addi $t, $s, imm
Encoding: 0010 00ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x09:
      sprintf(buffer, "addiu    ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*ADDIU -- Add immediate unsigned
Description: Adds a register and an unsigned immediate value and stores the result in a register
Operation: $t = $s + imm; advance_pc (4);
Syntax: addiu $t, $s, imm
Encoding: 0010 01ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0A:
      sprintf(buffer, "slti     ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*SLTI -- Set on less than immediate (signed)
Description: If $s is less than immediate, $t is set to one. It gets zero otherwise.
Operation: if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
Syntax: slti $t, $s, imm
Encoding: 0010 10ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0B:
      sprintf(buffer, "sltiu    ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*SLTIU -- Set on less than immediate unsigned
Description: If $s is less than the unsigned immediate, $t is set to one. It gets zero otherwise.
Operation: if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
Syntax: sltiu $t, $s, imm
Encoding: 0010 11ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0C:
      sprintf(buffer, "andi     ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*ANDI -- Bitwise and immediate
Description: Bitwise ands a register and an immediate value and stores the result in a register
Operation: $t = $s & imm; advance_pc (4);
Syntax: andi $t, $s, imm
Encoding: 0011 00ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0D:
      sprintf(buffer, "ori      ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*ORI -- Bitwise or immediate
Description: Bitwise ors a register and an immediate value and stores the result in a register
Operation: $t = $s | imm; advance_pc (4);
Syntax: ori $t, $s, imm
Encoding: 0011 01ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0E:
      sprintf(buffer, "xori     ");
      mipsRegister(a_opcode, T, 1);
      mipsRegister(a_opcode, S, 1);
      mipsImm(a_opcode, 0, 0);
/*XORI -- Bitwise exclusive or immediate
Description: Bitwise exclusive ors a register and an immediate value and stores the result in a register
Operation: $t = $s ^ imm; advance_pc (4);
Syntax: xori $t, $s, imm
Encoding: 0011 10ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x0F:
      sprintf(buffer, "lui      ");
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
/*LUI -- Load upper immediate
Description: The immediate value is shifted left 16 bits and stored in the register. The lower 16 bits are zeroes.
Operation: $t = (imm << 16); advance_pc (4);
Syntax: lui $t, imm
Encoding: 0011 11-- ---t tttt iiii iiii iiii iiii*/
      break;
      
    case 0x20:
      sprintf(buffer, "lb       ");
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
      strcat(buffer, "(");
      mipsRegister(a_opcode, S, 0);
      strcat(buffer, ")");
/*LB -- Load byte
Description: A byte is loaded into a register from the specified address.
Operation: $t = MEM[$s + offset]; advance_pc (4);
Syntax: lb $t, offset($s)
Encoding: 1000 00ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x23:
      sprintf(buffer, "lw       ");
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
      strcat(buffer, "(");
      mipsRegister(a_opcode, S, 0);
      strcat(buffer, ")");
/*LW -- Load word
Description: A word is loaded into a register from the specified address.
Operation: $t = MEM[$s + offset]; advance_pc (4);
Syntax: lw $t, offset($s)
Encoding: 1000 11ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x28:
      sprintf(buffer, "sb       ");
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
      strcat(buffer, "(");
      mipsRegister(a_opcode, S, 0);
      strcat(buffer, ")");
/*SB -- Store byte
Description: The least significant byte of $t is stored at the specified address.
Operation: MEM[$s + offset] = (0xff & $t); advance_pc (4);
Syntax: sb $t, offset($s)
Encoding: 1010 00ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    case 0x2B:
      sprintf(buffer, "sw       ");
      mipsRegister(a_opcode, T, 1);
      mipsImm(a_opcode, 0, 0);
      strcat(buffer, "(");
      mipsRegister(a_opcode, S, 0);
      strcat(buffer, ")");
/*SW -- Store word
Description: The contents of $t is stored at the specified address.
Operation: MEM[$s + offset] = $t; advance_pc (4);
Syntax: sw $t, offset($s)
Encoding: 1010 11ss ssst tttt iiii iiii iiii iiii*/
      break;
      
    default:
      sprintf(buffer, "???      ");
  }
}


