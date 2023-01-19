`timescale 1ns / 1ps

//This is an example for a single cycle cpu.
//You should:
//1. Extend the combinational logic part to construct a single cycle processor.(85%)
//2. Add more sequential logic to construct a pipeline processor.(100%)

module CPU(
    input wire clock,
    input wire start,
    input [31:0] i_datain,
    input wire [31:0] d_datain,
    output wire [31:0] d_dataout
    );

    reg [31:0]gr[7:0];//[31:0]for 32bit MIPS processor
    reg [15:0]pc = 32'h00000000;

    reg [31:0]instr;
    reg [31:0]reg_A;
    reg [31:0]reg_B;
    reg [31:0]reg_C;
    reg [31:0]reg_C1;

    reg [5:0]opcode;
    reg [5:0]func;
    reg [2:0] reg_zon = 3'b000;
    reg [1:0]regWrite = 2'b0;
    reg [1:0]regDst = 2'b0;
    reg [3:0]alu_ctr;
    reg alu_src;
    reg overflow_sign;
    reg reg_jump = 2'b00;
    reg [1:0]memToReg = 2'b0;
    reg[1:0]memWrite = 2'b0;
    reg pcSrc = 0;
    reg branch = 0;
    
//add,addi,lw,sw,addu,addiu
parameter alu_add = 4'b0000;
//sub,subu,beq,bne
parameter alu_sub = 4'b0001;
//and,andi
parameter alu_and = 4'b0010;
//nor
parameter alu_nor = 4'b0011;
//or,ori
parameter alu_or = 4'b0100;
//xor
parameter alu_xor = 4'b0101;
//sll,sllv
parameter alu_sll = 4'b0110;
//srl,srlv
parameter alu_srl = 4'b0111;
//sra,srav
parameter alu_sra = 4'b1000;
//slt
parameter alu_slt = 4'b1001;
//j
parameter alu_j = 4'b1010;
//jr
parameter alu_jr = 4'b1011;
//jal
parameter alu_jal = 4'b1100;

always @(start)
    begin
        gr[0] = 32'h0000_0000;
    end

//sequential logic
always @(posedge clock)
begin
if ((reg_jump==2'b00)&&(pcSrc==0))
begin
pc <= pc + 32'h00000004;
end
else if (reg_jump==2'b01)
begin
pc <= i_datain[25:0];
end
else if (reg_jump==2'b10)
begin
pc <=gr[i_datain[25:21]];
end
else if (pcSrc==1'b1)
begin
pc <= pc + reg_B;
end
end

//combinational logic
always @(posedge clock)
    begin
        instr = i_datain;
        //About Project 3
        //control unit
        opcode = instr[31:26];
        func = instr[5:0];
        reg_C = 0;
        reg_zon = 3'b000;
        overflow_sign = 0;
        reg_jump = 2'b00;
        //Please set the ALUControl with your own code.
//control unit
if (opcode == 6'b000000)
begin
//add
case(func)
6'b100000:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 1;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase
//addu
case(func)
6'b100001:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 0;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase
//sub
case(func)
6'b100010:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 1;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase
//subu
case(func)
6'b100011:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 0;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//and
case(func)
6'b100100:
begin
alu_src = 0;
alu_ctr = 4'b0010;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//nor
case(func)
6'b100111:
begin
alu_src = 0;
alu_ctr = 4'b0011;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//or
case(func)
6'b100101:
begin
alu_src = 0;
alu_ctr = 4'b0100;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//xor
case(func)
6'b100110:
begin
alu_src = 0;
alu_ctr = 4'b0101;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//slt
case(func)
6'b101010:
begin
alu_src = 0;
alu_ctr = 4'b1001;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//sll
case(func)
6'b000000:
begin
alu_src = 1;
alu_ctr = 4'b0110;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//sllv
case(func)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0110;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//srl
case(func)
6'b000010:
begin
alu_src = 1;
alu_ctr = 4'b0111;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//srlv
case(func)
6'b000110:
begin
alu_src = 0;
alu_ctr = 4'b0111;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//sra
case(func)
6'b000011:
begin
alu_src = 1;
alu_ctr = 4'b1000;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//srav
case(func)
6'b000111:
begin
alu_src = 0;
alu_ctr = 4'b1000;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b01;
regWrite = 2'b01;
end
endcase

//jr
case(func)
6'b001000:
begin
alu_src = 0;
alu_ctr = 4'b1011;
branch = 0;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
reg_jump = 2'b10;
end
endcase
end

else
begin
//addi
case(opcode)
6'b001000:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 1;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b00;
regWrite = 2'b01;
end
endcase

//addiu
case(opcode)
6'b001001:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 0;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b00;
regWrite = 2'b01;
end
endcase

//andi
case(opcode)
6'b001100:
begin
alu_src = 1;
alu_ctr = 4'b0010;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b00;
regWrite = 2'b01;
end
endcase

//ori
case(opcode)
6'b001101:
begin
alu_src = 1;
alu_ctr = 4'b0100;
branch = 0;
memToReg = 2'b00;
memWrite = 2'b00;
regDst = 2'b00;
regWrite = 2'b01;
end
endcase

//beq
case(opcode)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0001;
branch = 1;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
end
endcase

//bne
case(opcode)
6'b000101:
begin
alu_src = 0;
alu_ctr = 4'b0001;
branch = 1;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
end
endcase

//lw
case(opcode)
6'b100011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
branch = 0;
memToReg = 2'b01;
memWrite = 2'b00;
regDst = 2'b00;
regWrite = 2'b01;
end
endcase

//sw
case(opcode)
6'b101011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
branch = 1;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
end
endcase

//j
case(opcode)
6'b000010:
begin
alu_src = 0;
alu_ctr = 4'b1010;
branch = 0;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
reg_jump = 2'b01;
end
endcase

//jal
case(opcode)
6'b000011:
begin
alu_src = 0;
alu_ctr = 4'b1100;
branch = 0;
memToReg = 2'b10;
memWrite = 2'b00;
regDst = 2'b10;
regWrite = 2'b00;
reg_jump = 2'b01;
end
endcase
end

      
//alu part
case(alu_ctr)
alu_add:
begin
    reg_A = gr[i_datain[25:21]];
    if  (alu_src == 1)
    begin
    reg_B = {{16{i_datain[15]}},i_datain[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr[i_datain[20:16]];
    end
    reg_C = reg_A + reg_B;
    //overflow flag
    if ((overflow_sign==1)&&(reg_A[31]^reg_B[31] == 0) && (reg_A[31]!= reg_C[31] ))
    begin
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
    reg_zon[1] = 1'b1;
    end
    else
    begin
        reg_zon[1] = 1'b0;
    end
    //zero flag
    if (reg_C==0)
    begin
        reg_zon[2] = 1'b1;
    end
end

alu_sub:
begin
    reg_A = gr[i_datain[25:21]];
    reg_B = gr[i_datain[20:16]];
    reg_C = reg_A - reg_B;
    if ((overflow_sign == 1)&& (reg_A[31]^reg_B[31] == 1) && (reg_B[31] == reg_C[31]))
    begin
    reg_zon[1] = 1'b1;
    end
    else
    begin
    reg_zon[1] = 1'b0;
    end
    //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
    // negative flag 
    if(reg_C[31] == 1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_and:
begin
    reg_A = gr[i_datain[25:21]];
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[i_datain[20:16]];
    end
    reg_C = reg_A & reg_B;
    //zero flag
    if (reg_C == 0)
    begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_nor:
begin
    reg_A = gr[i_datain[25:21]];
    reg_B = gr[i_datain[20:16]];
    reg_C = ~(reg_A | reg_B);
    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_or:
begin
    reg_A = gr[i_datain[25:21]];
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[i_datain[20:16]];
    end
    reg_C = reg_A | reg_B;
    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_xor:
begin
    reg_A = gr[i_datain[25:21]];
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[i_datain[20:16]];
    end
    reg_C = (reg_A ^ reg_B);
    //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_slt:
begin
    reg_A = gr[i_datain[25:21]];
    if (alu_src == 1)
    begin
    reg_B = {{16{i_datain[15]}},i_datain[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr[i_datain[20:16]];
    end
    if (reg_A <reg_B) 
    begin
        reg_C = 1'b1;
    end
    else
    begin
    reg_C = 1'b0;
    end    
    //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
end

alu_sll:
begin
    reg_A = gr[i_datain[20:16]];
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr[i_datain[25:21]];
    end
    reg_C = reg_A << reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_srl:
begin
    reg_A = gr[i_datain[20:16]];
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr[i_datain[25:21]];
    end
    reg_C = reg_A >> reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_sra:
begin
    reg_A = gr[i_datain[20:16]];
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr[i_datain[25:21]];
    end
    reg_C = reg_A >>> reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zon[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
    end
end

alu_j:
begin
    reg_jump = 2'b01;
end

alu_jr:
begin
    reg_jump = 2'b10;
end

alu_jal:
begin
    reg_jump = 2'b01;
end


endcase

if ((branch==1)&&(reg_zon[2]==1'b1))
begin
pcSrc = 1'b1;
end

//reg_C1(Result)
//add
if ((opcode==6'b000000)&&(func==6'b100000))
begin
reg_C1 = reg_C;
end
//addu
else if ((opcode==6'b000000)&&(func==6'b100001))
begin
reg_C1 = reg_C;
end
//sub
else if ((opcode==6'b000000)&&(func==6'b100010))
begin
reg_C1 = reg_C;
end
//subu
else if ((opcode==6'b000000)&&(func==6'b100011))
begin
reg_C1 = reg_C;
end
//and
else if ((opcode==6'b000000)&&(func==6'b100100))
begin
reg_C1 = reg_C;
end
//or
else if ((opcode==6'b000000)&&(func==6'b100101))
begin
reg_C1 = reg_C;
end
//nor
else if ((opcode==6'b000000)&&(func==6'b100111))
begin
reg_C1 = reg_C;
end
//xor
else if ((opcode==6'b000000)&&(func==6'b100110))
begin
reg_C1 = reg_C;
end
//addi
else if (opcode==6'b001000)
begin
reg_C1 = reg_C;
end
//addiu
else if (opcode==6'b001001)
begin
reg_C1 = reg_C;
end
//andi
else if (opcode==6'b001100)
begin
reg_C1 = reg_C;
end
//ori
else if (opcode==6'b001101)
begin
reg_C1 = reg_C;
end
//lw
else if (opcode==6'b100011)
begin
reg_C1 = d_datain[31:0];
end
//sw
else if (opcode==6'b101011)
begin
reg_C1 = gr[instr[20:16]];
end
//sll
else if ((opcode==6'b000000)&&(func==6'b000000))
begin
reg_C1 = reg_C;
end
//sllv
else if ((opcode==6'b000000)&&(func==6'b000100))
begin
reg_C1 = reg_C;
end
//srl
else if ((opcode==6'b000000)&&(func==6'b000010))
begin
reg_C1 = reg_C;
end
//srlv
else if ((opcode==6'b000000)&&(func==6'b000110))
begin
reg_C1 = reg_C;
end
//sra
else if ((opcode==6'b000000)&&(func==6'b000011))
begin
reg_C1 = reg_C;
end
//srav
else if ((opcode==6'b000000)&&(func==000111))
begin
reg_C1 = reg_C;
end
//beq
else if ((opcode==6'b000100))
begin
reg_C1 = reg_C;
end
//bne
else if ((opcode==6'b000101))
begin
reg_C1 = reg_C;
end
//slt
else if ((opcode==6'b000000)&&(func==6'b101010))
begin
reg_C1 = reg_C;
end
//j
else if (opcode==6'b000010)
begin
reg_C1 = 0;
end
//jal
else if (opcode==6'b000011)
begin
reg_C1 = 0;
end
//jr
else if ((opcode==6'b000000)&&(func==6'b001000))
begin
reg_C1 = 0;
end     
        //write back to general registers
//        if (regWrite == 2'b01)
   //         gr[instr[15:11]] = reg_C1;
      //  else if (regWrite == 2'b10)
         //   gr[instr[20:16]] = reg_C1;
        //Use the RegWrite(Output of Ctrl Unit) to select.

//write back to general registers
        if (opcode == 6'b100011)
            gr[instr[20:16]] = reg_C1;
        else if (opcode == 6'b000000)
            gr[instr[15:11]] = reg_C1;
        //Use the RegWrite(Output of Ctrl Unit) to select.
   end
endmodule