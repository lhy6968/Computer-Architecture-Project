`timescale 1ns/1ps

// general register
`define gr0  	5'b00000
`define gr1  	5'b00001
`define gr2  	5'b00010
`define gr3 	5'b00011
`define gr4  	5'b00100
`define gr5  	5'b00101
`define gr6  	5'b00110
`define gr7  	5'b00111
`define gr8  	5'b01000
`define gr9  	5'b01001
`define gr10  	5'b01010
`define gr11  	5'b01011
`define gr12  	5'b01100
`define gr13  	5'b01101
`define gr14  	5'b01110
`define gr15  	5'b01111
`define gr16  	5'b10000
`define gr17  	5'b10001
`define gr18  	5'b10010
`define gr19  	5'b10011
`define gr20  	5'b10100
`define gr21  	5'b10101
`define gr22  	5'b10110
`define gr23 	5'b10111
`define gr24  	5'b11000
`define gr25  	5'b11001
`define gr26  	5'b11010
`define gr27  	5'b11011
`define gr28  	5'b11100
`define gr29  	5'b11101
`define gr30  	5'b11110
`define gr31  	5'b11111

module CPU_test;

    // Inputs
	reg clock;
	reg [31:0] d_datain;
	reg [31:0] i_datain;
    reg start;

    wire [31:0] d_dataout;

    CPU uut(
        .clock(clock),
        .start(start), 
		.d_datain(d_datain), 
		.i_datain(i_datain),
        .d_dataout(d_dataout)
    );

    initial begin
        // Initialize Inputs
        clock = 0;
        start = 1;

    $display("pc  :        instruction             : instrD  : instrE  : instrM  : instrW :d_datain:  gr0   :  gr1   :  gr2   :  gr3");
    $monitor("%h:%b:%h:%h:%h:%h:%h:%h:%h:%h:%h", 
        uut.pc,i_datain, uut.instrD, uut.instrE, uut.instrM, uut.instrW, d_datain, uut.gr[0], uut.gr[1], uut.gr[2], uut.gr[3]);

    /*Test:*/
    #period
    d_datain <= 32'h0000_00ab;
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0001};

    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {6'b100011, `gr0, `gr2, 16'h0002};
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;


    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, 6'b100000};
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;


    #period $finish;
    end

parameter period = 10;
always #5 clock = ~clock;
endmodule