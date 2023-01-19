module alu(i_datain,gr1,gr2,c,zon,hi,lo);

//define the input and output
output signed[31:0] c;
output signed[2:0]zon;
output signed[31:0] hi;
output signed[31:0] lo;
input signed[31:0] i_datain,gr1,gr2;

//define variables
reg[5:0] opcode, func;

reg[32:0] transfer =33'b1_0000_0000_0000_0000_0000_0000_0000_0000;

reg signed[31:0] reg_C;
reg [2:0] reg_zon = 3'b000;
reg signed[31:0]reg_A,reg_B;
reg unsigned[31:0]reg_Au, reg_Bu;
reg[63:0]reg_hilo;
integer index;
reg[3:0] alu_ctr;
reg alu_src;
reg overflow_sign;

parameter gr0 = 32'h0000_0000;

//define all the alu control from 4'b0

//add,addi,lw,sw,addu,addiu
parameter alu_add = 4'b0000;
//sub,subu
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
//beq,bne
parameter alu_beq = 4'b1010;
//slt,slti
parameter alu_slt = 4'b1011;
//sltu,sltiu
parameter alu_sltu = 4'b1100;
//sll,sllv
parameter alu_sll = 4'b1101;
//srl,srlv
parameter alu_srl = 4'b1110;
//sra,srav
parameter alu_sra = 4'b1111;

always @(i_datain,gr1,gr2)
begin

//initialize the zon flag registers to 3'b000
reg_hilo = 0;
reg_zon = 3'b000;
opcode = i_datain[31:26];
func = i_datain[5:0];

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
reg_A = gr1;
reg_B = gr2;
end
endcase
//addu
case(func)
6'b100001:
begin
alu_src = 0;
alu_ctr = 4'b0000;
overflow_sign = 0;
reg_A = gr1;
reg_B = gr2;
end
endcase
//sub
case(func)
6'b100010:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 1;
reg_A = gr1;
reg_B = gr2;
end
endcase
//subu
case(func)
6'b100011:
begin
alu_src = 0;
alu_ctr = 4'b0001;
overflow_sign = 0;
reg_A = gr1;
reg_B = gr2;
end
endcase
//mult
case(func)
6'b011000:
begin
alu_src = 0;
alu_ctr = 4'b0010;
reg_A = gr1;
reg_B = gr2;
end
endcase

//multu
case(func)
6'b011001:
begin
alu_src = 0;
alu_ctr = 4'b0011;
reg_A = gr1;
reg_B = gr2;
end
endcase

//div
case(func)
6'b011010:
begin
alu_src = 0;
alu_ctr = 4'b0100;
reg_A = gr1;
reg_B = gr2;
end
endcase

//divu
case(func)
6'b011011:
begin
alu_src = 0;
alu_ctr = 4'b0101;
reg_A = gr1;
reg_B = gr2;
end
endcase

//and
case(func)
6'b100100:
begin
alu_src = 0;
alu_ctr = 4'b0110;
reg_A = gr1;
reg_B = gr2;
end
endcase

//nor
case(func)
6'b100111:
begin
alu_src = 0;
alu_ctr = 4'b0111;
reg_A = gr1;
reg_B = gr2;
end
endcase

//or
case(func)
6'b100101:
begin
alu_src = 0;
alu_ctr = 4'b1000;
reg_A = gr1;
reg_B = gr2;
end
endcase

//xor
case(func)
6'b100110:
begin
alu_src = 0;
alu_ctr = 4'b1001;
reg_A = gr1;
reg_B = gr2;
end
endcase

//slt
case(func)
6'b101010:
begin
alu_src = 0;
alu_ctr = 4'b1011;
reg_A = gr1;
reg_B = gr2;
end
endcase

//sltu
case(func)
6'b101011:
begin
alu_src = 0;
alu_ctr = 4'b1100;
reg_A = gr1;
reg_B = gr2;
end
endcase

//sll
case(func)
6'b000000:
begin
alu_src = 1;
alu_ctr = 4'b1101;
reg_A = gr2;
reg_B = i_datain[10:6];
end
endcase

//sllv
case(func)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b1101;
reg_A = gr2;
reg_B = gr1;
end
endcase

//srl
case(func)
6'b000010:
begin
alu_src = 1;
alu_ctr = 4'b1110;
reg_A = gr2;
reg_B = i_datain[10:6];
end
endcase

//srlv
case(func)
6'b000110:
begin
alu_src = 0;
alu_ctr = 4'b1110;
reg_A = gr2;
reg_B = gr1;
end
endcase

//sra
case(func)
6'b000011:
begin
alu_src = 1;
alu_ctr = 4'b1111;
reg_A = gr2;
reg_B = i_datain[10:6];
end
endcase

//srav
case(func)
6'b000111:
begin
alu_src = 0;
alu_ctr = 4'b1111;
reg_A = gr2;
reg_B = gr1;
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
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{reg_B[15]}},reg_B[15:0]};
end
endcase

//addiu
case(opcode)
6'b001001:
begin
alu_src = 1;
alu_ctr = 4'b0000;
overflow_sign = 0;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{reg_B[15]}},reg_B[15:0]};

end
endcase

//andi
case(opcode)
6'b001100:
begin
alu_src = 1;
alu_ctr = 4'b0110;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{1'b0}},reg_B[15:0]};
end
endcase

//ori
case(opcode)
6'b001101:
begin
alu_src = 1;
alu_ctr = 4'b1000;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{1'b0}},reg_B[15:0]};
end
endcase

//xori
case(opcode)
6'b001110:
begin
alu_src = 1;
alu_ctr = 4'b1001;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{1'b0}},reg_B[15:0]};
end
endcase

//beq
case(opcode)
6'b000100:
begin
alu_src = 0;
alu_ctr = 4'b1010;
reg_A = gr1;
reg_B = gr2;
end
endcase

//bne
case(opcode)
6'b000101:
begin
alu_src = 0;
alu_ctr = 4'b1010;
reg_A = gr1;
reg_B = gr2;
end
endcase

//slti
case(opcode)
6'b001010:
begin
alu_src = 1;
alu_ctr = 4'b1011;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{reg_B[15]}},reg_B[15:0]};
end
endcase

//sltiu
case(opcode)
6'b001011:
begin
alu_src = 1;
alu_ctr = 4'b1100;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{1'b0}},reg_B[15:0]};
end
endcase

//lw
case(opcode)
6'b100011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{reg_B[15]}},reg_B[15:0]};
end
endcase

//sw
case(opcode)
6'b101011:
begin
alu_src = 1;
alu_ctr = 4'b0000;
reg_A = gr1;
reg_B = i_datain[15:0];
reg_B = {{16{reg_B[15]}},reg_B[15:0]};
end
endcase

end

//alu part
case(alu_ctr)
alu_add:
begin
    if  (overflow_sign == 1)
    begin
    reg_C = {1'b0,reg_A[31:0]}+{1'b0,reg_B[31:0]};
    //overflow flag
    if (reg_C[31]^reg_A[31]^reg_B[31]^reg_C[32])
    begin
        reg_zon[1] = 1'b1;
    end
    end
    else
    begin
    reg_C = reg_A + reg_B;
    end
    //zero flag
    if (reg_C[31:0]==0)
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
    if (overflow_sign == 1)
    begin
    reg_C = {1'b0,reg_A[31:0]}-{1'b0,reg_B[31:0]};
    // over flow flag
    if (reg_C[31]^reg_A[31]^reg_B[31]^reg_C[32]) 
    begin
        reg_zon[1] = 1'b1;
    end
    end
    else
    begin
    reg_C = reg_A-reg_B;
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
    // handle the negative flag
    if(reg_B[31]^reg_A[31])
    begin
        reg_zon[0] = 1'b1;
    end

    if(reg_B[31] == 1'b1)
    begin
        reg_B = (transfer - reg_B);
    end
    if(reg_A[31] == 1'b1)
    begin
        reg_A = (transfer - reg_A);
    end

    reg_hilo = reg_A*reg_B;
    
    if (reg_zon[0] == 1'b1) 
    begin
        reg_hilo = {transfer,transfer} - transfer -reg_hilo;
    end
    if (reg_hilo[63]==1) 
    begin
        reg_zon[0] = 1; //negative flag
    end
    if (reg_hilo == 0) 
    begin
        reg_zon[2] = 0; //zero  flag
    end
end

alu_multu:
begin
    reg_hilo = reg_A*reg_B;
    if (reg_hilo == 0) 
    begin
        reg_zon[2] = 1'b1;
    end
    
    // handle the flags  
    if (reg_hilo == 0) begin
        reg_zon[2] = 0; //zero  flag
    end

    if (reg_hilo[63]==1'b1) begin
        reg_zon[0] = 1; //negative flag
    end
end

alu_div:
begin
    if (reg_A[31]==1'b0)   //a is positive
    begin
        if ( reg_B[31] == 1'b0) // b is also positive
        begin
            reg_hilo = {reg_A/reg_B,reg_A%reg_B};
        end

        if (reg_B[31] == 1'b1)  // b is negative
        begin
            reg_B = transfer-reg_B;
            if (reg_A%reg_B == 0) 
            begin
                reg_hilo[63:32] = {transfer - reg_A/reg_B};
                reg_hilo[31:0]  = reg_A%reg_B;
            end 
            else 
            begin
                reg_hilo[63:32] = transfer - reg_A/reg_B-1;
                reg_hilo[31:0] = transfer - reg_B + reg_A%reg_B;
            end
            
        end
    end 
    if (reg_A[31]==1'b1 ) // A is negative 
   
    begin
        if ( reg_B[31] == 1'b1) // B is also negative
        
        begin
            reg_B = transfer-reg_B;
            reg_A = transfer-reg_A;
            reg_hilo = { reg_A/reg_B,reg_A%reg_B};
        end


        if (reg_B[31] == 1'b0 )  // B is positive
        begin
            reg_A = transfer-reg_A;
            if (reg_A%reg_B == 0) 
            begin
                reg_hilo[63:32] = {transfer - reg_A/reg_B};
                reg_hilo[31:0]  = reg_A%reg_B;
            end 
        
            else 
            begin
                reg_hilo[63:32] = transfer - reg_A/reg_B-1;
                reg_hilo[31:0] = reg_B - reg_A%reg_B;
            end
        end
    end
    // handle the flags  
    if (reg_hilo == 0) begin
        reg_zon[2] = 0; //zero  flag
    end
    if (reg_hilo[63]==1'b1) begin
        reg_zon[0] = 1; //negative flag
    end
end

alu_divu:
begin
    reg_hilo = {reg_A/reg_B,reg_A%reg_B};
     if (reg_hilo == 0) begin
        reg_zon[2] = 0; //zero  flag
    end
    if (reg_hilo[63]==1'b1) begin
        reg_zon[0] = 1; //negative flag
    end
end

alu_and:
begin
    reg_C = reg_A & reg_B;

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

alu_nor:
begin
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
    reg_C = (reg_A ^ reg_B);

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

alu_beq:
begin
    if (reg_A - reg_B == 0)
    begin
    reg_zon[2] = 1'b1;
    end
end

alu_slt:
begin
    if (reg_A <reg_B) 
    begin
        reg_C = 1'b1;
    end
    else
    begin
    reg_C = 1'b0;
    end    
    // handle the zero flag
    reg_zon = (reg_C == 0)? 3'b001 : 3'b000; 

end

alu_sltu:
begin
    reg_C = (reg_A[31:0]<reg_B[31:0]) ? 1'b1:1'b0;
    //handle the zero flag
    reg_zon = (reg_C == 1)? 3'b000 : 3'b100;
end

alu_sll:
begin
    reg_C = reg_A << reg_B;
end

alu_srl:
begin
    reg_C = reg_A >> reg_B;

    //zero flag
    if (reg_C[31:0]==0)
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
    reg_C = reg_A >>> reg_B;

  //zero flag
    if (reg_C[31:0]==0)
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

assign hi = reg_hilo[63:32];
assign lo = reg_hilo[31:0];
assign c = reg_C[31:0];
assign zon = reg_zon;

endmodule
