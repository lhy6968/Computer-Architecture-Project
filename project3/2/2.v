`timescale 1ns/1ps

module alu_test;

reg[31:0] i_datain,gr1,gr2;

wire[31:0]hi;
wire[31:0]lo;
wire[31:0]c;
wire zero;
wire overflow;
wire neg;
wire[2:0]zon;



alu testalu(i_datain,gr1,gr2,c,zon,hi,lo);

initial
begin

//$display("instruction: gr1      : gr2      : c      : hi      :lo      :   zon");
//$monitor(" %h:%h:%h:%h:%h:%h:%b",
//i_datain, gr1, gr2, c, hi, lo, zon);

$display("instruction:op:func:  gr1   :   c    : reg_A  : reg_B  : reg_C");
$monitor("   %h:%h: %h :%h:%h:%h:%h:%h",
i_datain, testalu.opcode, testalu.func, gr1 , c, testalu.reg_A, testalu.reg_B, testalu.reg_C);


//// arith left shift
#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0000;    //sll
gr1<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_1000_0000;
gr1<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0000;
gr1<=32'b0100_0000_0100_0000_0100_0000_0100_0000;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0001_0000_0000;
gr1<=32'b0100_0000_0100_0000_0110_0000_0100_0000;

#10 i_datain<=32'b0000_0000_0000_0000_0000_0000_0010_0000; //add 1077952576+(-1)
gr1<=32'b1100_0000_0100_0000_0100_0000_0100_0000;    
gr2<=32'b1111_1111_1111_1111_1111_1111_1111_1111;


#10 i_datain<=32'b0010_0000_0000_0000_0000_0000_1101_0000; //addi 1+208
gr1<=32'b0000_0000_0000_0000_0000_0000_0000_0001;



#10 $finish;
end

endmodule