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

reg[32:0] reg_C;
reg[2:0] reg_zon = 3'b000;
reg[31:0]reg_A,reg_B;
reg[63:0]reg_hilo;
integer index;
reg[4:0] alu_code;
reg alusrc;

parameter gr0 = 32'h0000_0000;

//define all the alu control from 5'b0

//add,addi,lw,sw
parameter alu_add = 5'b00000;

//add addiu
parameter alu_addu = 5'b00001;

//sub
parameter alu_sub = 5'b00010;

//subu
parameter alu_subu = 5'b00011;

//mult
parameter alu_mult = 5'b00100;

//multu
parameter alu_multu = 5'b00101;

//div
parameter alu_div = 5'b00110;

//divu
parameter alu_divu = 5'b00111;

//and,andi
parameter alu_and = 5'b01000;

//nor
parameter alu_nor = 5'b01001;

//or,ori
parameter alu_or = 5'b01010;

//xor,xori
parameter alu_xor = 5'b01011;

//beq
parameter alu_beq = 5'b01100;

//bne
parameter alu_bne = 5'b01101;

//slt,slti
parameter alu_slt = 5'b01110;

//sltu,sltiu
parameter alu_sltu = 5'b01111;

//sll,sllv
parameter alu_sll = 5'b10000;

//srl,srlv
parameter alu_srl = 5'b10001;

//sra,srav
parameter alu_sra = 5'b10010;

always @(gr1,gr2,i_datain)
begin

//store the input gr1,gr2 in reg_A and reg_B
//initialize the zon flag registers to 3'b000
reg_hilo = 0;
reg_zon = 3'b000;
reg_A = gr1;
opcode = i_data[31:26];
func = i_data[5:0];

//control unit
if (opcode == 6'b000000)
begin

//add
case(func)
6'b100000:
begin
alusrc = 0;
alu_code = 5'b00000;
end
endcase

//addu
case(func)
6'b100001:
begin
alusrc = 0;
alu_code = 5'b00001;
end
endcase

//sub
case(func)
6'b100010:
begin
alusrc = 0;
alu_code = 5'b00010;
end
endcase

//subu
case(func)
6'b100011:
begin
alusrc = 0;
alu_code = 5'b00011;
end
endcase

//mult
case(func)
6'b011000:
begin
alusrc = 0;
alu_code = 5'b00100;
end
endcase

//multu
case(func)
6'b011001:
begin
alusrc = 0;
alu_code = 5'b00101;
end
endcase

//div
case(func)
6'011010:
begin
alusrc = 0;
alu_code = 5'b00110;
end
endcase

//divu
case(func)
6'b011011:
begin
alusrc = 0;
alu_code = 5'b00111;
end
endcase

//and
case(func)
6'b100100:
begin
alusrc = 0;
alu_code = 5'b01000;
end
endcase

//nor
case(func)
6'b100111:
begin
alusrc = 0;
alu_code = 5'b01001;
end
endcase

//or
case(func)
6'b100101:
begin
alusrc = 0;
alu_code = 5'b01010;
end
endcase

//xor
case(func)
6'b100110:
begin
alusrc = 0;
alu_code = 5'b01011;
end
endcase

//slt
case(func)
6'b101010:
begin
alusrc = 0;
alu_code = 5'b01110;
end
endcase

//sltu
case(func)
6'b101011:
begin
alusrc = 0;
alu_code = 5'b01111;
end
endcase

//sll
case(func)
6'b000000:
begin
alusrc = 1;
alu_code = 5'b10000;
end
endcase

//sllv
case(func)
6'000100:
begin
alusrc = 0;
alu_code = 5'b10000;
end
endcase

//srl
case(func)
6'b000010:
begin
alusrc = 1;
alu_code = 5'b10001;
end
endcase

//srlv
case(func)
6'b000110:
begin
alusrc = 0;
alu_code = 5'b10001;
end
endcase

//sra
case(func)
6'b000011:
begin
alusrc = 1;
alu_code = 5'b10010;
end
endcase

//srav
case(func)
6'b000111:
begin
alusrc = 0;
alu_code = 5'b10010;
end
endcase

if (alusrc == 0)
begin
reg_B = gr2;
end

else
begin
reg_B = i_datain[10:6];
end

end

else
begin
//addi
case(opcode)
6'b001000:
begin
alusrc = 0;
alu_code = 5'b00000;
end
endcase

//addiu
case(opcode)
6'b001001:
begin
alusrc = 1;
alu_code = 5'b00001;
end
endcase

//andi
case(opcode)
6'b001100:
begin
alusrc = 1;
alu_code = 5'b01000;
end
endcase

//ori
case(opcode)
6'b001101:
begin
alusrc = 1;
alu_code = 5'b01010;
end
endcase

//xori
case(opcode)
6'b001110:
begin
alusrc = 1;
alu_code = 5'b01011;
end
endcase

//beq
case(opcode)
6'b000100:
begin
alusrc = 0;
alu_code = 5'b01100;
end
endcase

//bne
case(opcode)
6'b000101:
begin
alusrc = 0;
alu_code = 5'b01101;
end
endcase

//slti
case(opcode)
6'b001010:
begin
alusrc = 1;
alu_code = 5'b01110;
end
endcase

//sltiu
case(opcode)
6'b001011:
begin
alusrc = 1;
alu_code = 5'b01111;
end
endcase

//lw
case(opcode)
6'b100011:
begin
alusrc = 0;
alu_code = 5'b00000;
end
endcase

//sw
case(opcode)
6'b101011:
begin
alusrc = 0;
alu_code = 5'b00000;
end
endcase

if (alusrc = 0)
begin
reg_B = gr2;
end

else
begin
reg_B = i_datain[15:0];
end

end




case(alu_code)
alu_add:
begin
    reg_C = {1'b0,reg_A[31:0]}+{1'b0,reg_B[31:0]};
    //overflow flag
    if (reg_C[31]^reg_A[31]^reg_B[31]^reg_C[32])
    begin
        reg_zon[1] = 1'b1;
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

alu_addu:
begin
    reg_C = reg_A + reg_B;

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
    reg_C = {1'b0,reg_A[31:0]}-{1'b0,reg_B[31:0]};
    

    // over flow flag
    if (reg_C[31]^reg_A[31]^reg_B[31]^reg_C[32]) 
    begin
        reg_zon[1] = 1'b1;
    end

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end


    // negative flag 
    if(reg_C[31] == 1'b1)begin
        reg_zon[0] = 1'b1;
    end

end

alu_subu:
begin
    
    reg_C = {1'b0,reg_A[31:0]}-{1'b0,reg_B[31:0]};
    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end


    // negative flag 
    if(reg_C[31] == 1'b1)begin
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

    //handle the over flow flag
    if (reg_hilo[63:32] == 0) begin
        reg_zon[1] = 0;
    end else begin
        reg_zon[1] = 1;
    end

    if (reg_hilo[63]==1) begin
        reg_zon[0] = 1; //negative flag
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
end

alu_divu:
begin
    reg_hilo = {reg_A/reg_B,reg_A%reg_B};
end

alu_and:
begin
    reg_C = reg_A & reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

alu_nor:
begin
    reg_C = ~(reg_A | reg_B);

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

alu_or:
begin
    reg_C = reg_A | reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

alu_xor:
begin
    reg_C = (reg_A ^ reg_B);

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

alu_beq:
begin
    if (reg_A - reg_B == 0)
    begin
    reg_zon[2] = 1'b1;
    end
end

alu_bne:
begin
    if (reg_A - reg_B == 0)
    begin
    reg_zon[2] = 1'b1;
    end
end


alu_slt:
begin
    reg_zon = 3'b000;

    if (reg_A[31] <reg_B[31]) 
    begin
        reg_C = 1'b0;
    end

    if (reg_A[31] > reg_B[31]) 
    begin
        reg_C = 1'b1;
    end

    if (reg_A[31] == reg_B[31])
    begin
        reg_C = (reg_A[30:0]<reg_B[30:0]) ? 1'b1:1'b0;
    end
    // handle the zero flag
    reg_zon = (reg_C == 1)? 3'b000 : 3'b100; 

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
end

//alu_sra:
//begin
   // reg_C = {reg_B{reg_A[31]},reg_A>>reg_B};    
//end

endcase

end

assign hi = reg_hilo[63:32];
assign lo = reg_hilo[31:0];
assign c = reg_C[31:0];
assign zon = reg_zon;

endmodule;
