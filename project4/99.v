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
    reg signed[31:0] reg_A;
    reg signed[31:0] reg_B;
    reg signed[31:0]reg_C;
    reg signed[31:0]reg_C1;

    reg [5:0]opcode;
    reg [5:0]functcode;
    reg [2:0] reg_zon = 3'b000;
    reg [3:0]alu_ctr;
    reg alu_src;
    reg overflow_sign;
    reg_jump;

//define all the alu control from 4'b0

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
        //pc
        pc <= pc + 32'h00000004;
        //Use if sentences to implement the multiplexier
    end

//combinational logic
always @(pc)
    begin
        instr = i_datain;
        //About Project 3
        //control unit
        opcode = instr[31:26];
        func = instr[5:0];
        reg_C = 0;
        re_zon = 3'b000;
        overflow_sign = 0;
        reg_jump = 0;
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
end
endcase
//addu
case(func)
6'b100001:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 0;
end
endcase
//sub
case(func)
6'b100010:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 1;
end
endcase
//subu
case(func)
6'b100011:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 0;
end
endcase

//and
case(func)
6'b100100:
begin
alu_src = 0;
alu_ctr = 4'b0010;
end
endcase

//nor
case(func)
6'b100111:
begin
alu_src = 0;
alu_ctr = 4'b0011;
end
endcase

//or
case(func)
6'b100101:
begin
alu_src = 0;
alu_ctr = 4'b0100;
end
endcase

//xor
case(func)
6'b100110:
begin
alu_src = 0;
alu_ctr = 4'b0101;
end
endcase

//slt
case(func)
6'b101010:
begin
alu_src = 0;
alu_ctr = 4'b1001;
end
endcase

//sll
case(func)
6'b000000:
begin
alu_src = 1;
alu_ctr = 4'b0110;
end
endcase

//sllv
case(func)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0110;
end
endcase

//srl
case(func)
6'b000010:
begin
alu_src = 1;
alu_ctr = 4'b0111;
end
endcase

//srlv
case(func)
6'b000110:
begin
alu_src = 0;
alu_ctr = 4'b0111;
end
endcase

//sra
case(func)
6'b000011:
begin
alu_src = 1;
alu_ctr = 4'b1000;
end
endcase

//srav
case(func)
6'b000111:
begin
alu_src = 0;
alu_ctr = 4'b1000;
end
endcase
//jr
case(func)
6'b001000:
begin
alu_src = 0;
alu_ctr = 4'b1011;
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
end
endcase

//addiu
case(opcode)
6'b001001:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 0;

end
endcase

//andi
case(opcode)
6'b001100:
begin
alu_src = 1;
alu_ctr = 4'b0010;
end
endcase

//ori
case(opcode)
6'b001101:
begin
alu_src = 1;
alu_ctr = 4'b0100;
end
endcase

//beq
case(opcode)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b0001;
end
endcase

//bne
case(opcode)
6'b000101:
begin
alu_src = 0;
alu_ctr = 4'b0001;
end
endcase

//lw
case(opcode)
6'b100011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
end
endcase

//sw
case(opcode)
6'b101011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
end
endcase

//j
case(opcode)
6'b000010:
begin
alu_src = 0;
alu_ctr = 4'b1010;
end
endcase

//jal
case(opcode)
6'b000011:
begin
alu_src = 0;
alu_ctr = 4'b1100;
end
endcase
end
      
//alu part
case(alu_ctr)
alu_add:
begin
    reg_A = gr1;
    if  (alu_src == 1)
    begin
    reg_B = {{16{i_datain[15]}},i_datain[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr2;
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
    reg_A = gr1;
    reg_B = gr2;
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
    reg_A = gr1;
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr2;
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
    reg_A = gr1;
    reg_B = gr2;
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
    reg_A = gr1;
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr2;
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
    reg_A = gr1;
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr2;
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
    reg_A = gr1;
    if (alu_src == 1)
    begin
    reg_B = {{16{i_datain[15]}},i_datain[15:0]};  //sign extenstion
    end
    else
    begin
    reg_B = gr2;
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
    reg_A = gr2;
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr1;
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
    reg_A = gr2;
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr1;
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
    reg_A = gr2;
    if (alu_src == 1) 
    begin
    reg_B = i_datain[10:6];
    end 
    else 
    begin
    reg_B = gr1;
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
    reg_jump = 1;
end

alu_jr:
begin
    reg_jump = 1;
end

alu_jal:
begin
    reg_jump = 1;
end
endcase
end

        //reg_C1(Result)
        //lw, add, etc.
        if (opcode == 6'b100011)
        begin
            reg_C1 = d_datain[31:0];
        end
        //add, etc.
        else if (opcode == 6'b000000)
            reg_C1 = reg_C;
        
        //write back to general registers
        if (opcode == 6'b100011)
            gr[instr[20:16]] = reg_C1;
        else if (opcode == 6'b000000)
            gr[instr[15:11]] = reg_C1;
        //Use the RegWrite(Output of Ctrl Unit) to select.

    end


endmodule