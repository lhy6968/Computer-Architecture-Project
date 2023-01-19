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
    wire [31:0] d_addr;

    CPU uut(
        .clock(clock),
        .start(start), 
		.d_datain(d_datain), 
		.i_datain(i_datain),
        .d_dataout(d_dataout),
        .d_addr(d_addr)
    );

    initial begin
        // Initialize Inputs
        clock = 0;
        start = 1;

    $display("pc      :        instruction             :  gr0   :  gr1   :  gr2   :  gr3   :   gr31 :dataout : address");
    $monitor("%h:%b:%h:%h:%h:%h:%h:%h:%h", 
        uut.pc,uut.instr, uut.gr[0], uut.gr[1], uut.gr[2], uut.gr[3],uut.gr[31],d_dataout,d_addr);

    /*Test:*/
    #period
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0001};  //lw gr1 = 0000_00ab
    d_datain <= 32'h0000_00ab;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period 
    d_datain <= 32'h0000_3c00;
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
  
	
    #period i_datain <= {6'b000100, `gr1, `gr2,16'h200};    //beq h'200

    #period i_datain <= {6'b000101, `gr1, `gr2, 16'h300};    //bne h'300(not jump)

    #period i_datain <= {6'b000010, 26'h100};    //j to pc = 100 

    #period i_datain <= {6'b000100, `gr1, `gr2,16'h200};    //beq h'200

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,5'b00000,6'b100010};  //sub gr3 = 0
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b001001, `gr2, `gr3, 16'h123};  //sub gr3 = gr2+291
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr2, `gr3, `gr1,5'b00000,6'b100110};  
    //xor   gr1 = gr2^gr3
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr2, `gr3, `gr1,5 'b00001,6'b000011}; 
    // sra gr1 = gr3>>>1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period d_datain <= 32'h0000_0002;
    i_datain <= {6'b100011, `gr0, `gr1, 16'h0002};    //lw gr1 = 2
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;

    #period i_datain <= {6'b000000, `gr1, `gr3, `gr2, 5'b00000,6'b000111};
    //srav  gr2 = gr3>>>gr1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
 
    #period i_datain <= {6'b000000, `gr1, `gr3, `gr2, 5'b00000,6'b000100};
    //sllv  gr2 = gr3<<gr1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr1, `gr3, `gr2, 5'b00001,6'b000000};
    //sll  gr2 = gr3<<1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00011,6'b000010};
    //srl  gr3 = gr2>>3
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000,6'b000110};
    //srlv  gr3 = gr2>>gr1
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3, 5'b00000,6'b100111};
    //nor gr3 = ~(gr1|gr2 ) 
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 

    #period i_datain <= {6'b001101, `gr2, `gr3, 16'b10};
    //ori gr3 = gr2|10 
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000;
    #period i_datain <= 32'b0000_0000_0000_0000_0000_0000_0000_0000; 





    #period $finish;
    end

parameter period = 10;
always #5 clock = ~clock;
endmodule