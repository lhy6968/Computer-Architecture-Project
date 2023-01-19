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
`define gr15 	5'b01111
`define gr16  	5'b10000
`define gr17  	5'b10001
`define gr18  	5'b10010
`define gr19  	5'b10011
`define gr20  	5'b10100
`define gr21  	5'b10101
`define gr22 	5'b10110
`define gr23  	5'b10111
`define gr24	5'b11000
`define gr25  	5'b11001
`define gr26  	5'b11010
`define gr27  	5'b11011
`define gr28 	5'b11100
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
        d_datain = 0;
        i_datain = 0;

    $display("pc  :        instruction             : reg_A  : reg_B  : reg_C : reg_C1  :ALU: d_datain: instr  :  gr0   :  gr1   :  gr2   :  gr3  :    Equal: BranchD :PCBJ");
    $monitor("%h:%b:%h:%h:%h:%h:%b:%h:%h:%h:%h:%h:%h:%h:%h:%h", 
        uut.pc, uut.instr, uut.reg_A, uut.reg_B, uut.reg_C,uut.reg_C1,uut.ALUControlE, d_datain,uut.instr, uut.gr[0], uut.gr[1], uut.gr[2], uut.gr[3], uut.EqualD, uut.BranchD, uut.PCBJ);

    /*Test:*/

    #period
    d_datain <= 32'h0000_00ab;
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0001};  //lw gr1 = 0000_00ab
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {6'b100011, `gr0, `gr2, 16'h0002};    //lw gr2 = 0000_3c00
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, 6'b100000}; //add
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
 
    #period d_datain <= 32'h0000_3c00;
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0002};    //lw gr1 = 0000_3c00
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period i_datain <= {6'b101011, `gr2, `gr3, 16'h0001};    //sw address = gr3
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b001000, `gr2, `gr3, 16'h1}; //addi gr3=gr2+1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
  
	
    #period i_datain <= {6'b000100, `gr1, `gr2,16'h200};    //beq to pc = 200
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000101, `gr1, `gr2, 16'h300};    //bne to pc = 300(not jump)
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000010, 26'h100};    //j to pc = 100
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;     

    #period i_datain <= {6'b000100, `gr1, `gr2,16'h200};    //beq to pc = 200
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period $finish;
    end

parameter period = 10;
always #5 clock = ~clock;
endmodule