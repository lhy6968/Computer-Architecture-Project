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

    reg [31:0]gr[31:0];//[31:0]for 32bit MIPS processor
    reg [15:0]pc = 32'h00000000;

    reg [31:0]instrD;
    reg [31:0]instrE;
    reg [31:0]instrM;
    reg [31:0]instrW;

    reg [31:0]reg_A = 0;
    reg [31:0]reg_B = 0;
    reg [31:0]reg_C = 0;
    reg [31:0]reg_C1 = 0;

    reg [31:0]pcBranch = 0;

    reg [5:0]opcode = 0;
    reg [5:0]func = 0;

    reg [2:0] reg_zonE = 0;
    reg [2:0] reg_zonM = 0;

    reg regWriteD = 0;
    reg regWriteE = 0;
    reg regWriteM = 0;
    reg regWriteW = 0;

    reg regDstD = 0;
    reg regDstE = 0;
    reg regDstM = 0;
    reg regDstW = 0;

    reg [3:0]alu_ctrD;
    reg [3:0]alu_ctrE;

    reg alu_srcD = 0;
    reg alu_srcE = 0;

    reg overflow_signD= 0;
    reg overflow_signE= 0;

    reg reg_jumpD= 0;
    reg reg_jumpE= 0;
    reg reg_jumpM= 0;
    reg reg_jumpW= 0;

    reg data_jumpD= 0;
    reg data_jumpE= 0;
    reg data_jumpM= 0;
    reg data_jumpW= 0;

    reg memToRegD= 0;
    reg memToRegE= 0;
    reg memToRegM= 0;
    reg memToRegW= 0; 

    reg memWriteD= 0;
    reg memWriteE= 0;
    reg memWriteM= 0;

    reg pcSrcM= 0;

    reg branchD= 0;
    reg branchE= 0;
    reg branchM= 0;
    
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

always @(posedge clock)
begin
if ((reg_jumpM==0)&&(pcSrcM==0)&&(data_jumpM==0)&&(i_datain!=0))
begin
pc <= pc + 32'h00000004;
end
else if (data_jumpM == 1)
begin
pc <= instrM[25:0];
end
else if (reg_jumpM == 1)
begin
pc <=gr[instrM[25:21]];
end
else if (pcSrcM == 1)
begin
pcBranch <= instrM[15:0];
pcBranch <= pcBranch << 2;
pcBranch <= {{16{pcBranch[15]}},pcBranch[15:0]};
pc <= pc + pcBranch;
end
end
//decode part
always @(posedge clock)
begin
instrD <= i_datain;
opcode <= instrD[31:26];
func <= instrD[5:0];
//control unit
if (opcode == 6'b000000)
begin
case(func)
//add
6'b100000:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0000;
overflow_signD <= 1;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//addu
6'b100001:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0000;
overflow_signD <= 0;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//sub
6'b100010:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0001;
overflow_signD <= 1;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//subu
6'b100011:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0001;
overflow_signD <= 0;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//and
6'b100100:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0010;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//nor
6'b100111:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0011;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//or
6'b100101:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0100;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//xor
6'b100110:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0101;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//slt
6'b101010:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b1001;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//sll
6'b000000:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0110;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//sllv
6'b000100:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0110;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//srl
6'b000010:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0111;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//srlv
6'b000110:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0111;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//sra
6'b000011:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b1000;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//srav
6'b000111:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b1000;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 1;
end
//jr
6'b001000:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b1011;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 1;
regWriteD <= 0;
reg_jumpD <= 1;
end
endcase
end
else
begin
case(opcode)
//addi
6'b001000:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0000;
overflow_signD <= 1;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 1;
end
//addiu
6'b001001:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0000;
overflow_signD <= 0;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 1;
end
//andi
6'b001100:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0010;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 1;
end
//ori
6'b001101:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0100;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 1;
end
//beq
6'b000100:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0001;
branchD <= 1;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 0;
end
//bne
6'b000101:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b0001;
branchD <= 1;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 0;
end
//lw
6'b100011:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0000;
branchD <= 0;
memToRegD <= 1;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 1;
end
//sw
6'b101011:
begin
alu_srcD <= 1;
alu_ctrD <= 4'b0000;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 0;
end
//j
6'b000010:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b1010;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 0;
data_jumpD <= 1;
end
//jal
6'b000011:
begin
alu_srcD <= 0;
alu_ctrD <= 4'b1100;
branchD <= 0;
memToRegD <= 0;
memWriteD <= 0;
regDstD <= 0;
regWriteD <= 0;
data_jumpD <= 1;
gr[31] <= pc;
end
endcase
end
instrE <= instrD;
regWriteE <= regWriteD;
memToRegE <= memToRegD;
memWriteE <= memWriteD;
branchE <= branchD;
alu_ctrE <= alu_ctrD;
alu_srcE <= alu_srcD;
regDstE <= regDstD;
reg_jumpE <= reg_jumpD;
data_jumpE <= data_jumpD;
overflow_signE <= overflow_signD;
end
//execute
always @(posedge clock)
begin
//alu part
case(alu_ctrE)
alu_add:
begin
    reg_A = gr[instrE[25:21]];
    if  (alu_srcE == 1)
    begin
    reg_B = {{16{instrE[15]}},instrE[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr[instrE[20:16]];
    end
    reg_C = reg_A + reg_B;
    //overflow flag
    if ((overflow_signE==1)&&(reg_A[31]^reg_B[31] == 0) && (reg_A[31]!= reg_C[31] ))
    begin
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
    reg_zonE[1] = 1'b1;
    end
    else
    begin
        reg_zonE[1] = 1'b0;
    end
    //zero flag
    if (reg_C==0)
    begin
        reg_zonE[2] = 1'b1;
    end
end

alu_sub:
begin
    reg_A = gr[instrE[25:21]];
    reg_B = gr[instrE[20:16]];
    reg_C = reg_A - reg_B;
    if ((overflow_signE == 1)&& (reg_A[31]^reg_B[31] == 1) && (reg_B[31] == reg_C[31]))
    begin
    reg_zonE[1] = 1'b1;
    end
    else
    begin
    reg_zonE[1] = 1'b0;
    end
    //zero flag
    if (reg_C == 0) 
    begin
    reg_zonE[2] = 1'b1;
    end
    // negative flag 
    if(reg_C[31] == 1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_and:
begin
    reg_A = gr[instrE[25:21]];
    if (alu_srcE == 1)
    begin
    reg_B = {{16{1'b0}},instrE[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[instrE[20:16]];
    end
    reg_C = reg_A & reg_B;
    //zero flag
    if (reg_C == 0)
    begin
    reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_nor:
begin
    reg_A = gr[instrE[25:21]];
    reg_B = gr[instrE[20:16]];
    reg_C = ~(reg_A | reg_B);
    //zero flag
    if (reg_C == 0) 
    begin
        reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_or:
begin
    reg_A = gr[instrE[25:21]];
    if (alu_srcE == 1)
    begin
    reg_B = {{16{1'b0}},instrE[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[instrE[20:16]];
    end
    reg_C = reg_A | reg_B;
    //zero flag
    if (reg_C == 0) 
    begin
        reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_xor:
begin
    reg_A = gr[instrE[25:21]];
    if (alu_srcE == 1)
    begin
    reg_B = {{16{1'b0}},instrE[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr[instrE[20:16]];
    end
    reg_C = (reg_A ^ reg_B);
    //zero flag
    if (reg_C == 0) 
    begin
        reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_slt:
begin
    reg_A = gr[instrE[25:21]];
    if (alu_srcE == 1)
    begin
    reg_B = {{16{instrE[15]}},instrE[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr[instrE[20:16]];
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
        reg_zonE[2] = 1'b1;
    end
end

alu_sll:
begin
    reg_A = gr[instrE[20:16]];
    if (alu_srcE == 1) 
    begin
    reg_B = instrE[10:6];
    end 
    else 
    begin
    reg_B = gr[instrE[25:21]];
    end
    reg_C = reg_A << reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_srl:
begin
    reg_A = gr[instrE[20:16]];
    if (alu_srcE == 1) 
    begin
    reg_B = instrE[10:6];
    end 
    else 
    begin
    reg_B = gr[instrE[25:21]];
    end
    reg_C = reg_A >> reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_sra:
begin
    reg_A = gr[instrE[20:16]];
    if (alu_srcE == 1) 
    begin
    reg_B = instrE[10:6];
    end 
    else 
    begin
    reg_B = gr[instrE[25:21]];
    end
    reg_C = reg_A >>> reg_B;
     //zero flag
    if (reg_C == 0) 
    begin
    reg_zonE[2] = 1'b1;
    end
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zonE[0] = 1'b1;
    end
end

alu_j:
begin
    reg_C = 0;
end

alu_jr:
begin
    reg_C = 0;
end

alu_jal:
begin
    reg_C = 0;
end
endcase
regWriteM <= regWriteE;
memToRegM <= memToRegE;
memWriteM <= memWriteE;
branchM <= branchE;
reg_zonM <= reg_zonE;
regDstM <= regDstE;
instrM <= instrE;
reg_jumpM <= reg_jumpE;
data_jumpM <= data_jumpE;
end

always @(posedge clock)
begin

if ((branchM==1)&&(reg_zonM[2]==1'b1))
begin
pcSrcM = 1;
end
else
begin
pcSrcM = 0;
end
if (memToRegM==1)
begin
reg_C1 = d_datain[31:0];
end
else
begin
reg_C1 = reg_C;
end
regWriteW <= regWriteM;
memToRegW <= memToRegM;
regDstW <= regDstM;
end  
always @(posedge clock)
begin

instrW <= instrM;
if ((regWriteW==1)&&(regDstW==1))
begin
gr[instrW[15:11]] = reg_C1;
end
else if ((regWriteW==1)&&(regDstW==0))
begin
gr[instrW[20:16]] = reg_C1;
end
if ((regWriteW==1)&&(memToRegW==1))
begin
gr[instrW[20:16]] = d_datain;
end
end
endmodule