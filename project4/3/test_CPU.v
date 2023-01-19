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

module CPU_test;

    // Inputs
	reg clock;
	reg [31:0] d_datain;
	reg [31:0] i_datain;
    reg start;

    wire [31:0] d_dataout;





parameter  
// R type, function code
add = 6'b100000,
addu = 6'b100001,
and_ = 6'b100100,
jr = 6'b001000,
nor_ = 6'b100111,
or_ = 6'b100101,
slt = 6'b101010,
sub  = 6'b100010,
subu  = 6'b100011,
xor_  = 6'b100110,
xnor_ = 6'b111111, 

//I and J type, opcode
addi = 6'b001000,
addiu = 6'b001001,
andi = 6'b001100,
ori  = 6'b001111,
lw = 6'b100011,
sw = 6'b101011,
beq = 6'b000100,
bne = 6'b000101,
j = 6'b000010,
jal = 6'b000011;


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
        start = 0;
        d_datain = 0;
        i_datain = 0;

     $display("pc  :        instruction             : reg_A  : reg_B  : reg_C  : reg_C1 :d_datain:  gr0   :  gr1   :  gr2   :  gr3");
    $monitor("%h:%b:%h:%h:%h:%h:%h:%h:%h:%h:%h", 
        uut.pc, uut.instr, uut.reg_A, uut.reg_B, uut.reg_C, uut.reg_C1, d_datain, uut.gr[0], uut.gr[1], uut.gr[2], uut.gr[3]);

    /*Test:*/
    #5 start = 1;
    #5 d_datain <= 32'h0000_00ab;
    i_datain <= {lw, `gr0, `gr1, 16'h0001};

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {lw, `gr0, `gr2, 16'h0002};

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {sw, `gr0, `gr2, 16'h0002};

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {addi, `gr1, `gr3, 16'h0003};

    #period d_datain <= 32'h0000_3c00;
    i_datain <= {addiu, `gr1, `gr3, 16'h0003};





    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, add};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, addu};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, sub};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, subu};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, and_};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, or_};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, nor_};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, xor_};

    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, xnor_};


    #period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, jr};


    #period i_datain <= {6'b000000, `gr2, `gr1, `gr3,  5'b00000, slt};

    #period i_datain <= {andi, `gr1, `gr3, 16'h0004};
    #period i_datain <= {ori, `gr1, `gr3, 16'h0004};

    #period i_datain <= {beq, `gr1, `gr3, 16'h0004};

    #period i_datain <= {bne, `gr1, `gr3, 16'h0004};

    #period i_datain <= {j,26'h0};
    #period i_datain <= {jal,26'h8};
#period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, jr};
#period i_datain <= {6'b000000, `gr1, `gr2, `gr3,  5'b00000, jr};










    #period $finish;
    end

parameter period = 10;
always #5 clock = ~clock;
endmodule