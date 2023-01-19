`timescale 1ns/1ps

module alu_test;

reg[31:0] gr1,gr2,i_datain;

wire[31:0]hi;
wire[31:0]lo;
wire[31:0]c;
wire zero;
wire overflow;
wire neg;
wire[2:0]zon;



alu testalu(gr1,gr2,i_datain,c,zon,hi,lo);

initial
begin

$display("i: gr1      : gr2      : c      : hi      :lo      :   zon");
$monitor(" %h:%h:%h:%h:%h:%h:%b",
i_datain, gr1, gr2, c, hi, lo, zon);

//// arith left shift
#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0000;
gr1<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_1000_0000;
gr1<=32'b1101_1101_1101_1101_1101_1101_1101_1101;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0000_0100_0000;
gr1<=32'b0100_0000_0100_0000_0100_0000_0100_0000;

#10 i_datain<=32'b0000_0000_0000_0001_0001_0001_0000_0000;
gr1<=32'b0100_0000_0100_0000_0100_0000_0100_0000;

#10 $finish;
end

endmodule