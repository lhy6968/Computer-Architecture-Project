`timescale 1ns/1ps

module alu_test;

reg[31:0] i_datain,gr1,gr2;

wire[31:0]hi;
wire[31:0]lo;
wire[31:0]c;
wire[2:0]zon;


alu testalu(i_datain,gr1,gr2,c,zon,hi,lo);

initial
begin


$display("instruction:op:func:  gr1   :   gr2    : reg_A  : reg_B  : reg_C : lo : hi : zon");
$monitor("   %h:%h: %h :%h:%h:%h:%h:%h:%h:%h:%b",
i_datain, testalu.opcode, testalu.func, gr1 , gr2, testalu.reg_A, testalu.reg_B, testalu.reg_C,testalu.lo,testalu.hi,zon);

//// arith left shift
#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0000; //add -1069531072+(-1)
gr1<=32'b1100_0000_0100_0000_0100_0000_0100_0000;    
gr2<=32'b1111_1111_1111_1111_1111_1111_1111_1111;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0001; //addu 3225436224+4294967295
gr1<=32'b1100_0000_0100_0000_0100_0000_0100_0000;    
gr2<=32'b1111_1111_1111_1111_1111_1111_1111_1111;

#10 i_datain<=32'b0010_0000_0000_0000_1111_1111_1101_0000; //addi (-48��+(-2147483647)
gr1<=32'b1000_0000_0000_0000_0000_0000_0000_0001; 

#10 i_datain<=32'b0010_0100_0000_0000_1111_1111_1101_0000; //addiu (-48��+(-2147483647)
gr1<=32'b1000_0000_0000_0000_0000_0000_0000_0001;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0010; //sub 2147483647-(-2147483648)
gr1<=32'b0111_1111_1111_1111_1111_1111_1111_1111; 
gr2<=32'b1000_0000_0000_0000_0000_0000_0000_0000;    

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0010; //sub 2147483647-(-1)
gr1<=32'b0111_1111_1111_1111_1111_1111_1111_1111; 
gr2<=32'b1111_1111_1111_1111_1111_1111_1111_1111; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0011; //subu 2147483647-4294967295
gr1<=32'b0111_1111_1111_1111_1111_1111_1111_1111; 
gr2<=32'b1111_1111_1111_1111_1111_1111_1111_1111; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0001_1000; //mult -2147483629*-2147483647
gr1<=32'b1000_0000_0000_0000_0000_0000_0001_0011; 
gr2<=32'b1000_0000_0000_0000_0000_0000_0000_0001;   

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0001_1000; //mult -7*1
gr1<=32'b1111_1111_1111_1111_1111_1111_1111_1001; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0000_0001; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0001_1001; //multu 7*1
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0111; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0000_0001; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0001_1010; //div 21/5
gr1<=32'b0000_0000_0000_0000_0000_0000_0001_0011; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0000_0101;  

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0001_1011; //divu  21/1
gr1<=32'b1000_0000_0000_0000_0000_0000_0001_0011; 
gr2<=32'b1000_0000_0000_0000_0000_0000_0000_0001; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0100; //and 1
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0011; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0011_0001;  

#10 i_datain<=32'b0011_0000_0000_0000_0000_0000_0110_0100; //andi 100100
gr1<=32'b0011_0000_0000_0000_0000_0000_0010_0111;    

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0111; //nor 100111011100
gr1<=32'b1111_1111_1111_1111_1111_0110_0010_0011; 
gr2<=32'b1111_1111_1111_1111_1111_0000_0010_0001; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0101; //or 110011
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0011_0001;  

#10 i_datain<=32'b0011_0100_0000_0000_0000_0000_1010_0101; //ori  10100111
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0110; //xor  10010
gr1<=32'b0000_0000_0000_0000_0000_0000_0011_0011; 
gr2<=32'b0000_0000_0000_0000_0000_0000_0010_0001; 

#10 i_datain<=32'b0011_1000_0000_0000_0000_0000_0011_0110; //xori 10101
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011; 

#10 i_datain<=32'b0001_0000_0000_0000_0000_0000_1001_0110; //beq zf=1
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011;
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011;  

#10 i_datain<=32'b0001_0100_0000_0000_0000_0000_1101_0110; //bne zf=0
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_0011;
gr1<=32'b0000_0000_0000_0000_0000_0000_0010_1011;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0110_1010; //slt c=0
gr1<=32'b0101_1101_1101_1101_1101_1101_1101_1100;
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100; 

#10 i_datain<=32'b0010_1000_0000_0000_0000_0000_0110_1010; //slti c=0
gr1<=32'b1000_0000_0000_1101_1101_1101_1101_1100;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0110_1011; //sltu c=1
gr1<=32'b0101_1101_1101_1101_1101_1101_1101_1100;
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100;

#10 i_datain<=32'b0010_1100_0000_0000_0000_0000_0110_1010; //sltiu c=1
gr1<=32'b1000_0000_0000_1101_1101_1101_1101_1100;

#10 i_datain<=32'b1000_1100_0000_0000_0000_0000_0010_1010; //lw 24028+42
gr1<=32'b0000_0000_0000_0000_0101_1101_1101_1100;

#10 i_datain<=32'b1010_1100_0000_0000_0000_0000_0010_1011; //sw 24024+43
gr1<=32'b0000_0000_0000_0000_0101_1101_1101_1000;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0000;    //sll
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0100;    //sllv
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0010;
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0100_0010; //srl
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100;   

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0000_0110; //srlv
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100; 
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0100;   


#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0100_0011; //sra
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100; 

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0100_0011; //srav
gr2<=32'b1101_1101_1101_1101_1101_1101_1101_1100; 
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0001; 



#10 $finish;
end

endmodule