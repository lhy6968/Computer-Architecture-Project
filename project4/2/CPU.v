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

    reg [31:0]pcBranch;

    reg [5:0]opcode;
    reg [5:0]func;
    reg [2:0] reg_zon;
    reg regWrite;
    reg regDst;
    reg [3:0]alu_ctr;
    reg alu_src;
    reg overflow_sign;
    reg reg_jump;
    reg data_jump;
    reg memToReg;
    reg memWrite;
    reg pcSrc;
    reg branch;
    
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
if ((reg_jump==0)&&(pcSrc==0)&&(data_jump==0))
begin
pc <= pc + 32'h00000004;
end
else if (data_jump == 1)
begin
pc <= i_datain[25:0];
end
else if (reg_jump == 1)
begin
pc <=gr[i_datain[25:21]];
end
else if (pcSrc == 1)
begin
pcBranch = i_datain[15:0];
pcBranch = pcBranch << 2;
pcBranch = {{16{pcBranch[15]}},pcBranch[15:0]};
pc <= pc + pcBranch;
end
end

//combinational logic
always @(posedge clock)
begin
instr = i_datain;
opcode = instr[31:26];
func = instr[5:0];
reg_C = 0;
reg_C1 = 0;
reg_zon = 3'b000;
overflow_sign = 0;
reg_jump = 0;
data_jump = 0;
regWrite = 0;
regDst = 0;
alu_ctr = 0;
alu_src = 0;
overflow_sign = 0;
reg_jump = 0;
data_jump = 0;
memToReg = 0;
memWrite = 0;
pcSrc = 0;
branch = 0;

//control unit
if (opcode == 6'b000000)
begin
case(func)
//add
6'b100000:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 1;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//addu
6'b100001:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 0;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//sub
6'b100010:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 1;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//subu
6'b100011:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 0;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//and
6'b100100:
begin
alu_src = 0;
alu_ctr = 4'b0010;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//nor
6'b100111:
begin
alu_src = 0;
alu_ctr = 4'b0011;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//or
6'b100101:
begin
alu_src = 0;
alu_ctr = 4'b0100;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//xor
6'b100110:
begin
alu_src = 0;
alu_ctr = 4'b0101;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//slt
6'b101010:
begin
alu_src = 0;
alu_ctr = 4'b1001;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//sll
6'b000000:
begin
alu_src = 1;
alu_ctr = 4'b0110;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//sllv
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0110;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//srl
6'b000010:
begin
alu_src = 1;
alu_ctr = 4'b0111;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//srlv
6'b000110:
begin
alu_src = 0;
alu_ctr = 4'b0111;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//sra
6'b000011:
begin
alu_src = 1;
alu_ctr = 4'b1000;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//srav
6'b000111:
begin
alu_src = 0;
alu_ctr = 4'b1000;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 1;
end
//jr
6'b001000:
begin
alu_src = 0;
alu_ctr = 4'b1011;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 1;
regWrite = 0;
reg_jump = 1;
end
endcase
end
else
begin
case(opcode)
//addi
6'b001000:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 1;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 1;
end
//addiu
6'b001001:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 0;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 1;
end
//andi
6'b001100:
begin
alu_src = 1;
alu_ctr = 4'b0010;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 1;
end
//ori
6'b001101:
begin
alu_src = 1;
alu_ctr = 4'b0100;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 1;
end
//beq
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0001;
branch = 1;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 0;
end
//bne
6'b000101:
begin
alu_src = 0;
alu_ctr = 4'b0001;
branch = 1;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 0;
end
//lw
6'b100011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
branch = 0;
memToReg = 1;
memWrite = 0;
regDst = 0;
regWrite = 1;
end
//sw
6'b101011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 0;
end
//j
6'b000010:
begin
alu_src = 0;
alu_ctr = 4'b1010;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 0;
data_jump = 1;
end
//jal
6'b000011:
begin
alu_src = 0;
alu_ctr = 4'b1100;
branch = 0;
memToReg = 0;
memWrite = 0;
regDst = 0;
regWrite = 0;
data_jump = 1;
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
    data_jump = 1;
end

alu_jr:
begin
    reg_jump = 1;
end

alu_jal:
begin
    data_jump = 1;
end
endcase

if ((branch==1)&&(reg_zon[2]==1'b1))
begin
pcSrc = 1;
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
if ((regWrite==1)&&(regDst==1))
begin
gr[i_datain[15:11]] = reg_C1;
end
else if ((regWrite==1)&&(regDst==0))
begin
gr[i_datain[20:16]] = reg_C1;
end
if ((regWrite==1)&&(memToReg==1))
begin
gr[i_datain[20:16]] = d_datain;
end
end
endmodule