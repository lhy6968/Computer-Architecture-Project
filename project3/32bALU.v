module alu(a,b,opcode,c,zon,hi,lo);
// define the input output 
output signed[31:0] hi;
output signed [31:0] lo;
output signed[31:0] c;
output signed[2:0] zon;
input signed[31:0] a,b;
input[5:0] opcode;


// def variables 
reg[32:0] transfer =33'b1_0000_0000_0000_0000_0000_0000_0000_0000;

reg[31:0] reg_A, reg_B;
reg[32:0] reg_C;
reg[63:0] reg_hilo;
integer index;
reg[2:0] reg_zon = 3'b000;



// define all the opcodes from 6'b0 
parameter  add = 6'b000001,
addi = 6'b000010,
addu = 6'b000011,
addiu = 6'b000100,
sub  = 6'b000101,
subu  = 6'b000110,
mult = 6'b000111,
multu  = 6'b001000,
div = 6'b001001,
divu = 6'b001010,
sqrt = 6'b001011,
and_ = 6'b001100,
andi = 6'b001101,
or_ = 6'b001110,
ori  = 6'b001111,
nor_ = 6'b010000,
xor_  = 6'b010001,
xnor_ = 6'b010010, 

slt = 6'b010011,
slti = 6'b010100;




always @(a,b,opcode)
begin

// store the input a,b in reg_A and reg_B
//initialize the zon flag registers to 3'b000
reg_hilo = 0;
reg_zon = 3'b000;
reg_A = a;
reg_B = b;

case(opcode)

and_:
begin
    reg_C = reg_A & reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

andi:
begin
    reg_C = reg_A & reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

or_:
begin
    reg_C = reg_A | reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

ori:
begin
    reg_C = reg_A | reg_B;

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

nor_:
begin
    reg_C = ~(reg_A | reg_B);

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end

xor_:
begin
    reg_C = (reg_A ^ reg_B);

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end


xnor_:
begin
    reg_C = (reg_A ~^ reg_B);

    //zero flag
    if (reg_C == 0) begin
    reg_zon[2] = 1'b1;
    end

end


slt: // set on less than
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



slti : //set on less than immediate

begin
    reg_zon = 3'b000;
    reg_B = {{16{reg_B[15]}},reg_B[15:0]}; //sign extended of the immediate value
    

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



add:
begin
    reg_C = {1'b0,a[31:0]}+{1'b0,b[31:0]};
    
     // overflow flag
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

addi:
begin
    reg_B = {{16{reg_B[15]}},reg_B[15:0]}; //sign extended of the immediate value
    
    reg_C = {1'b0,a[31:0]}+{1'b0,b[31:0]};
    
     // overflow flag
    if (reg_C[31]^reg_A[31]^reg_B[31]^reg_C[32]) 
    begin
        reg_zon[1] = 1'b1;
    end

    //zero flag
    if (reg_C[31:0] == 0) begin
    reg_zon[2] = 1'b1;
    end

    // negative flag
    if(reg_C[31] == 1'b1)begin
        reg_zon[0] = 1'b1;
    end
    
end

addu:
begin
    reg_C = reg_A+reg_B;
   
    //zero flag
    if (reg_C[31:0] == 0) begin
    reg_zon[2] = 1'b1;
    end

    // negative flag
    if(reg_C[31] == 1'b1)begin
        reg_zon[0] = 1'b1;
    end
end

addiu:
begin
    reg_B = {{16{reg_B[15]}},reg_B[15:0]}; //sign extended of the immediate value
    reg_C = reg_A+reg_B;
   
    //zero flag
    if (reg_C[31:0] == 0) begin
    reg_zon[2] = 1'b1;
    end

    // negative flag
    if(reg_C[31] == 1'b1)begin
        reg_zon[0] = 1'b1;
    end
    
end

sqrt:
begin
    // use a empty for loop to find the largest integer which is smaller than sqrt(reg_A)
    for ( index = 0; (index * index) <= reg_A; index = index+1) begin
    end
    reg_C = index -1;
    
    //zero flag
    if (reg_C[31:0] == 0) begin
    reg_zon[2] = 1'b1;
    end
end




sub:
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

subu:
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


multu:
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

mult:
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

divu:
begin
    reg_hilo = {reg_A/reg_B,reg_A%reg_B};
end

div:
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


endcase




end


assign hi = reg_hilo[63:32];
assign lo = reg_hilo[31:0];
assign c = reg_C[31:0];
assign zon = reg_zon;

endmodule