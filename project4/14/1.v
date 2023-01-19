`timescale 1ns / 1ps

//This is an example for a single cycle cpu.
//You should:
//1. Extend the combinational logic part to construct a single cycle processor.(85%)
//2. Add more sequential logic to construct a pipeline processor.(100%)

module CPU(
    input wire clock,
    input wire start,
    input [31:0] i_datain,
    input wire [31:0] d_datain,
    output wire [31:0] d_dataout
    );

    reg [31:0]gr[31:0];//[31:0]for 32bit MIPS processor
    reg [15:0]pc = -32'b00000100;

    reg [31:0]instr;
    reg [31:0]instrE;
    reg [31:0]instrM;
    reg [31:0]reg_A;
    reg [31:0]reg_B;
    reg [31:0]reg_C;
    reg [31:0]reg_C1;
    reg [31:0]reg_Cw;
    reg [31:0]reg_CM;

    reg [5:0]opcode;
    reg [5:0]func;
    reg RegWriteD;
    reg MemtoRegD;
    reg MemWriteD;
    reg BranchD;
    reg [3:0]ALUControlD;
    reg ALUsrcD;
    reg RegDstD;
    reg JumpD = 1'b0;
    reg [31:0]d_datainD;
    reg RegWriteE;
    reg MemtoRegE;
    reg MemWriteE;
    reg BranchE;
    reg [3:0]ALUControlE;
    reg ALUsrcE;
    reg RegDstE;
    reg JumpE;
    reg [31:0]d_datainE;
    reg PCSrcD;
    reg [31:0]PCBJ = 32'h0;
    reg EqualD;
    reg [15:0]pcD;
    reg RegWriteM;
    reg MemtoRegM;
    reg MemWriteM;
    reg [31:0]d_datainM;
    reg RegWriteW;
    reg MemtoRegW;
    reg [4:0]WriteRegE;
    reg [4:0]WriteRegM;
    reg [4:0]WriteRegW;
    reg [31:0]d_datainW;
    reg [31:0]ResultW;
    reg [31:0]rt;
    reg [4:0]shamt;
    reg [15:0]imm;





//sequential logic
always @(posedge clock)
	begin
	gr[0] = 32'h0000_0000;
	instr <= i_datain;
	//opcode <= i_datain[31:26];
	//func <= i_datain[5:0];
	d_datainD <= d_datain;
	pcD <= pc;
    end

//combinational logic
always @(posedge clock)
    begin
	opcode = instr[31:26];
	func = instr[5:0];
	case(opcode)
	6'b000000:
	begin

	case(func)  //add
	6'b100000:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //sll
	6'b000000:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0100;
	ALUsrcD = 1'b1;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //sub
	6'b100010:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0110;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //sllv
	6'b000100:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0100;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //srl
	6'b000010:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0101;
	ALUsrcD = 1'b1;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //srlv
	6'b000110:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0101;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //sra
	6'b000011:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b1101;
	ALUsrcD = 1'b1;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //srav
	6'b000111:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b1101;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //addu
	6'b100001:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //and
	6'b100100:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0000;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //nor
	6'b100111:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b1111;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //or
	6'b100101:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0001;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //xor
	6'b100110:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0011;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //subu
	6'b100011:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0110;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //slt
	6'b101010:
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0111;
	ALUsrcD = 1'b0;
	RegDstD = 1'b1;
	end
	endcase

	case(func)  //jr
	6'b001000:
	begin
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b1;
	ALUControlD = 4'b1000;
	ALUsrcD = 1'b0;
	RegDstD = 1'b0;
	PCBJ = gr[instr[25:21]];
	end
	endcase



	end
	endcase

	case(opcode) //lw
	6'b100011: 
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b1;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //sw
	6'b101011: 
	begin
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b1;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //addi
	6'b001000: 
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //addiu
	6'b001001: 
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0010;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //andi
	6'b001100: 
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0000;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //ori
	6'b001101: 
	begin
	RegWriteD = 1'b1;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD =  1'b0;
	PCSrcD = 1'b0;
	ALUControlD = 4'b0001;
	ALUsrcD = 1'b1;
	RegDstD = 1'b0;
	end
	endcase

	case(opcode) //beq
	6'b000100:
	begin
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0; 
	BranchD = 1'b1;
	PCSrcD = 1'b0;
	EqualD = 1'b0;
	if (gr[instr[25:21]] == gr[instr[20:16]]) begin
		EqualD = 1'b1;
	end
	ALUControlD = 4'b0110;
	ALUsrcD = 1'b0;
	RegDstD = 1'b0;
	PCBJ = instr[15:0];
	end
	endcase

	case(opcode) //bne
	6'b000101: 
	begin 
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0; 
	BranchD = 1'b1;
	PCSrcD = 1'b0;
	EqualD = 1'b0;
	if (gr[instr[25:21]] != gr[instr[20:16]]) begin
		EqualD = 1'b1;
	end
	ALUControlD = 4'b0110;
	ALUsrcD = 1'b0;
	RegDstD = 1'b0;
	PCBJ = instr[15:0];
	end
	endcase

	case(opcode) //j
	6'b000010:
	begin 
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0; 
        BranchD = 1'b0;
	PCSrcD = 1'b1;
	PCBJ = instr[25:0];
	ALUControlD = 4'b1000;
	ALUsrcD = 1'b0;
	RegDstD = 1'b0;
	end
	endcase
	
	case(opcode) //jal
	6'b000011: 
	begin
	RegWriteD = 1'b0;
	MemtoRegD = 1'b0;
	MemWriteD = 1'b0;
	BranchD = 1'b0; 
	PCSrcD = 1'b1;
	gr[31] = pcD + 32'h00000004;
	PCBJ <= instr[25:0];
	ALUControlD = 4'b1000;
	ALUsrcD = 1'b0;
	RegDstD = 1'b0;
	end
	endcase

	RegWriteE <= RegWriteD;
	MemtoRegE <= MemtoRegD;
	MemWriteE <= MemWriteD;
	BranchE <= BranchD;
	ALUControlE <= ALUControlD;
	RegDstE <= RegDstD;
	instrE <= instr;
	ALUsrcE <= ALUsrcD;
	d_datainE <=d_datainD;

	if  (PCSrcD ==1'b1) begin
	pc = PCBJ;
	end 
	else if (BranchD == 1'b1 && EqualD == 1'b1) begin
	pc <= pc+4*PCBJ;
	end
	else begin
	pc <= pc + 32'h00000004;
	end


end	

always @(posedge clock)
	begin
	
	reg_A <= gr[instr[25:21]];
	reg_B <= gr[instr[20:16]];
	imm <= instr[15:0];
	rt <= gr[instr[20:16]];

	if (ALUsrcE == 1'b1) begin
		shamt <= instr[10:6];
	end else begin
		shamt = reg_A;
	end


        case (ALUControlE)
	4'b0000: //and
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = reg_A & reg_B;
	end else begin
	reg_C = reg_A & imm;
	end
	end

	4'b0001: //or
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = reg_A | reg_B;
	end else begin
	reg_C = reg_A | imm;
	end
	end

	4'b0010:   //lw,add
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = reg_A + reg_B;
	end else begin
	reg_C = reg_A + {{16{instr[15]}},imm};;
	end
	end
	
	4'b0011:  //xor
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = reg_A ^ reg_B;
	end else begin
	reg_C = reg_A ^ imm;
	end
	end
	
	4'b0100: //sll
	begin
	reg_C = rt << shamt;
	end

	4'b0101:  //srl
	begin
	reg_C = rt >> shamt;
	end
	
	4'b0110:  //sub
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = reg_A - reg_B;
	end else begin
	reg_C = reg_A - imm;
	end
	end


	4'b1101: //sra
	begin
	reg_C = rt >>> shamt;
	end

	4'b1111: //nor
	begin
	if (ALUsrcE == 1'b0) begin
	reg_C = ~(reg_A|reg_B);
	end else begin
	reg_C = ~(reg_A|imm);
	end
	end
	
	endcase	

	if (RegDstE == 1'b1)
	begin
	WriteRegE = instrE[15:11];
	end else begin
	WriteRegE = instrE[20:16];
	end

	instrM <= instrE;
	RegWriteM <= RegWriteE;
	MemtoRegM <= MemtoRegE;
	MemWriteM <= MemWriteE;
	d_datainM <= d_datainE;
	WriteRegM <= WriteRegE;
	reg_CM <= reg_C;

end

always @(posedge clock)
	begin

	if (MemWriteM == 1'b1) //sw
	reg_C1 = gr[instrM[20:16]];
	else if (MemtoRegM == 1'b1)//lw
	reg_C1 = d_datainM;
	else
	reg_C1 = reg_CM;


	d_datainW <= d_datainM;
	WriteRegW <= WriteRegM;
	MemtoRegW <= MemtoRegM;
	RegWriteW <= RegWriteM;
	reg_Cw <= reg_C1;

	end

always @(posedge clock)
	begin

	case (MemtoRegW)
	1'b1:   //lw
	begin
	ResultW = d_datainW;
	end
	1'b0:
	begin
	ResultW = reg_Cw;
	end
	endcase
	if (RegWriteW == 1) begin
	gr[WriteRegW] = ResultW;
	end
	
	
	end
	


endmodule
                
