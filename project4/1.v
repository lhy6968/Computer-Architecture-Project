`timescale 1ns/1ps

module CPU(
    input wire clock,
    input wire start,
    input [31:0] i_datain,
    input wire [31:0] d_datain,
    output wire [31:0] d_dataout
    );

    reg [31:0]gr[7:0];//[31:0]for 32bit MIPS processor
    reg [15:0]pc = 32'h00000000;
    reg nf,zf,cf;
    reg state,next_state;
    reg dw;
    reg[15:0]pc = 16'h0000;
    reg[31:0]y_forboard;
    reg[31:0]id_ir;
    reg[31:0]wb_ir;
    reg[31:0]ex_ir;
    reg[31:0]mem_ir;
    reg[31:0]smdr = 0;
    reg[31:0]smdr1 = 0;
    

    reg [31:0]instr;
    reg signed [31:0] reg_A;
    reg signed [31:0] reg_B;
    reg signed [31:0] reg_C;
    reg signed [31:0] reg_C1;
    reg signed [31:0] ALUo;
    reg[31:0]dataout;

    reg [5:0]opcode;
    reg [5:0]functcode;

parameter
lw = 5'b00000
sw = 5'b00001
add = 5'b00010
sub = 5'b00011
addu = 5'b00100
sub = 5'b00101
addi = 5'b00110
addiu = 5'b00111
and = 5'b01000
or = 5'b01001
nor = 5'b01010
xor = 5'b01011
andi = 5'b01100
ori = 5'b01101
sll = 5'b01110
srl = 5'b01111
sra = 5'b10000
sllv = 5'b10001
srlv = 5'b10010
srav = 5'b10011
beq = 5'b10100
bne = 5'b10101
slt = 5'b10110
j = 5'b10111
jr = 5'b11000
jal = 5'b11001


//CPU control
always @(start)
    begin
        //zero register
        gr[0] = 32'h0000_0000;
    end

//fetch
always @(posedge clock)
    begin
    instr = i_datain;
    dataout = 32'bxxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx;
    //pc
    pc <= pc + 32'h00000004;
    end

//decode
always @(posedge clock)
    begin
    opcode = instr[31:26];
    functcode = instr[5:0];
    reg_A = gr[i_datain[25:21]];
    reg_B = i_datain[15:0];

    end

//execute
always @(posedge clock)
    begin

    end


//memory
always @(posedge clock)
    begin

    end

//writeback
always @(posedge clock)
    begin


    end



