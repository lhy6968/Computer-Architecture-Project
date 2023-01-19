module alu(i_datain,gr1,gr2,c,zon,hi,lo);

//define the input and output
output signed[31:0] c;
output signed[2:0]zon;
output signed[31:0] hi;
output signed[31:0] lo;
input signed[31:0] i_datain,gr1,gr2;

//define variables
reg[5:0] opcode, func;

reg signed[31:0] reg_C;
reg [2:0] reg_zon = 3'b000;
reg signed[31:0]reg_A,reg_B;
reg unsigned[31:0]reg_Au, reg_Bu;
reg[63:0]reg_hilo;
reg[3:0] alu_ctr;
reg alu_src;
reg overflow_sign;
reg signed[31:0] reg_hi,reg_lo;

parameter gr0 = 32'h0000_0000;

//define all the alu control from 4'b0

//add,addi,lw,sw,addu,addiu
parameter alu_add = 4'b0000;
//sub,subu,beq,bne
parameter alu_sub = 4'b0001;
//mult
parameter alu_mult = 4'b0010;
//multu
parameter alu_multu = 4'b0011;
//div
parameter alu_div = 4'b0100;
//divu
parameter alu_divu = 4'b0101;
//and,andi
parameter alu_and = 4'b0110;
//nor
parameter alu_nor = 4'b0111;
//or,ori
parameter alu_or = 4'b1000;
//xor,xori
parameter alu_xor = 4'b1001;
//slt,slti
parameter alu_slt = 4'b1010;
//sltu,sltiu
parameter alu_sltu = 4'b1011;
//sll,sllv
parameter alu_sll = 4'b1100;
//srl,srlv
parameter alu_srl = 4'b1101;
//sra,srav
parameter alu_sra = 4'b1110;

always @(i_datain,gr1,gr2)
begin

//initialize the zon flag registers to 3'b000
reg_C = gr0;
reg_hilo = 0;
reg_hi = gr0;
reg_lo = gr0;
reg_zon = 3'b000;
opcode = i_datain[31:26];
func = i_datain[5:0];
overflow_sign = 0;

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
//mult
case(func)
6'b011000:
begin
alu_src = 0;
alu_ctr = 4'b0010;
end
endcase

//multu
case(func)
6'b011001:
begin
alu_src = 0;
alu_ctr = 4'b0011;
end
endcase

//div
case(func)
6'b011010:
begin
alu_src = 0;
alu_ctr = 4'b0100;
overflow_sign = 1;
end
endcase

//divu
case(func)
6'b011011:
begin
alu_src = 0;
alu_ctr = 4'b0101;
overflow_sign = 1;
end
endcase

//and
case(func)
6'b100100:
begin
alu_src = 0;
alu_ctr = 4'b0110;
end
endcase

//nor
case(func)
6'b100111:
begin
alu_src = 0;
alu_ctr = 4'b0111;
end
endcase

//or
case(func)
6'b100101:
begin
alu_src = 0;
alu_ctr = 4'b1000;
end
endcase

//xor
case(func)
6'b100110:
begin
alu_src = 0;
alu_ctr = 4'b1001;
end
endcase

//slt
case(func)
6'b101010:
begin
alu_src = 0;
alu_ctr = 4'b1010;
end
endcase

//sltu
case(func)
6'b101011:
begin
alu_src = 0;
alu_ctr = 4'b1011;
end
endcase

//sll
case(func)
6'b000000:
begin
alu_src = 1;
alu_ctr = 4'b1100;
end
endcase

//sllv
case(func)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b1100;
end
endcase

//srl
case(func)
6'b000010:
begin
alu_src = 1;
alu_ctr = 4'b1101;
end
endcase

//srlv
case(func)
6'b000110:
begin
alu_src = 0;
alu_ctr = 4'b1101;
end
endcase

//sra
case(func)
6'b000011:
begin
alu_src = 1;
alu_ctr = 4'b1110;
end
endcase

//srav
case(func)
6'b000111:
begin
alu_src = 0;
alu_ctr = 4'b1110;
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
alu_ctr = 4'b0110;
end
endcase

//ori
case(opcode)
6'b001101:
begin
alu_src = 1;
alu_ctr = 4'b1000;
end
endcase

//xori
case(opcode)
6'b001110:
begin
alu_src = 1;
alu_ctr = 4'b1001;
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

//slti
case(opcode)
6'b001010:
begin
alu_src = 1;
alu_ctr = 4'b1010;
end
endcase

//sltiu
case(opcode)
6'b001011:
begin
alu_src = 1;
alu_ctr = 4'b1011;
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
    //negative flag
    if (reg_C[31]==1'b1)
    begin
        reg_zon[0] = 1'b1;
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

alu_mult:
begin
    reg_A = gr1;
    reg_B = gr2;
    reg_hilo = reg_A * reg_B;
    reg_lo = reg_hilo[31:0];
    reg_hi = reg_hilo[63:32];
    if (reg_hilo == 0)
    begin
    reg_zon[2] = 1'b1;
    end
end

alu_multu:
begin
    reg_A = gr1;
    reg_B = gr2;
    reg_Au = gr1;
    reg_Bu = gr2;
    reg_hilo = reg_Au*reg_Bu;
    reg_lo = reg_hilo[31:0];
    reg_hi = reg_hilo[63:32];
    if (reg_hilo == 0) 
    begin
        reg_zon[2] = 1'b1;
    end
end

alu_div:
begin
    reg_A = gr1;
    reg_B = gr2;
    reg_lo = reg_A / reg_B;
    reg_hi = reg_A - ((reg_A/reg_B)*reg_B);
    if (reg_B == 0)
    begin
        reg_zon[1] = 1'b1;
    end
    else
    begin
        reg_zon[1] = 1'b0;
    end
end

alu_divu:
begin
    reg_A = gr1;
    reg_B = gr2;
    reg_Au = gr1;
    reg_Bu = gr2;
    reg_lo = reg_Au  / reg_Bu ;
    reg_hi = reg_Au  - ((reg_Au/reg_Bu)*reg_Bu);
    if (reg_B == 0)
    begin
        reg_zon[1] = 1'b1;
    end
    else
    begin
        reg_zon[1] = 1'b0;
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

alu_sltu:
begin
    reg_A = gr1;
    reg_Au = gr1;
    if (alu_src == 1)
    begin
    reg_B = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    reg_Bu = {{16{1'b0}},i_datain[15:0]};  //zero extenstion
    end
    else
    begin
    reg_B = gr2;
    reg_Bu = gr2;
    end
    if (reg_Au <reg_Bu) 
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

endcase

end
assign hi = reg_hi[31:0];
assign lo = reg_lo[31:0];
assign c = reg_C[31:0];
assign zon = reg_zon;

endmodule
