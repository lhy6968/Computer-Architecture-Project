`timescale 1ns / 1ps

module CPU(
    input wire clock,
    input wire start,
    input [31:0] i_datain,
    input wire [31:0] d_datain,
    output wire [31:0] d_dataout
    );

    // define 8 general register
    reg [31:0]gr[7:0];
    reg [31:0] dataout;

    // process control
    reg [15:0]pc = 16'h0000; 

    reg [1:0]regWrite = 2'b0; // 00:invalid   01:$rt is the destination register(lw)  10: $rd is the destination

    reg [31:0]reg_A;
    reg [31:0]reg_B;
    reg [31:0]reg_C;
    

    reg [5:0]opcode;
    reg [5:0]functcode;



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


always @(start)
    begin
        // zero register
        gr[0] = 32'h0000_0000;
    end

always @(posedge clock)

	begin

        //control unit
        opcode = i_datain[31:26];
        functcode = i_datain[5:0];
        
        //
        dataout = 32'bxxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx;
        
        // def for i type instruction:( will be rewrite in R type instruction)
        reg_A = gr[i_datain[25:21]];
        reg_B = i_datain[15:0];

        case(opcode)


        // R-type instructions
        6'b000000:
        begin
            // load a , b and write the regWrite 
            reg_A = gr[i_datain[25:21]];
            reg_B = gr[i_datain[20:16]];
            

            case(functcode)
            
            add:
            begin
                
                reg_C = reg_A + reg_B;
                regWrite = 2'b10;
            end

            addu:
            begin
                
                reg_C = reg_A + reg_B;
                regWrite = 2'b10;
            end



            sub:
            begin
                
                reg_C = reg_A - reg_B;
                regWrite = 2'b10;
            end

            subu:
            begin
                
                reg_C = reg_A - reg_B;
                regWrite = 2'b10;
            end


            slt:
            begin
                if (reg_A[31] <reg_B[31]) 
                begin
                    reg_C = 0;
                end

                if (reg_A[31] > reg_B[31]) 
                begin
                    reg_C = 1;
                end

                if (reg_A[31] == reg_B[31])
                begin
                    reg_C = (reg_A[30:0]<reg_B[30:0]) ? 1:0;
                end
                regWrite = 2'b10;
            end

            jr:
            begin
                pc = gr[i_datain[25:21]];
                regWrite = 2'b00;
            end
            
            and_:
            begin
                reg_C = reg_A & reg_B;
                regWrite = 2'b10;
            end

            or_:
            begin
                reg_C = reg_A | reg_B;
                regWrite = 2'b10;
            end

            nor_:
            begin
                reg_C = ~(reg_A | reg_B);
                regWrite = 2'b10;
            end

            xor_:
            begin
                reg_C = (reg_A ^ reg_B);
                regWrite = 2'b10;
            end

            xnor_:
            begin
                reg_C = (reg_A ~^ reg_B);
                regWrite = 2'b10;
            end

            endcase
            
        end

        
        lw:
        begin
            reg_C = d_datain[31:0];
            regWrite = 2'b01;
        end

        addi:
        begin
            reg_B = {{16{reg_B[15]}},reg_B[15:0]}; //sign extended of the immediate value
            reg_C = reg_A+reg_B;
            regWrite = 2'b01;
        end

        addiu:
        begin
            reg_B = {{16{reg_B[15]}},reg_B[15:0]}; //sign extended of the immediate value
            reg_C = reg_A+reg_B;
            regWrite = 2'b01;
        end

        andi:
            begin
                reg_C = reg_A & reg_B;
                regWrite = 2'b01;
            end

        ori:
        begin
            reg_C = reg_A | reg_B;
            regWrite = 2'b01;
        end

        sw:
        begin
            dataout = gr[i_datain[20:16]];
            
            regWrite = 2'b00;
            
        end

        beq:
        begin
            reg_C = gr[i_datain[20:16]];
            reg_B = reg_B<<2;
            reg_B = {{16{reg_B[15]}},reg_B[15:0]};
            if (reg_A == reg_C)
            begin
                pc = pc+reg_B;
            end
            regWrite = 2'b00;
        end
    
        bne:
        begin
            reg_C = gr[i_datain[20:16]];
            reg_B = reg_B<<2;
            reg_B = {{16{reg_B[15]}},reg_B[15:0]};
            if (reg_A != reg_C)
            begin
                pc = pc+reg_B;
            end
            regWrite = 2'b00;
        end



        j:
        begin
            pc = i_datain[25:0];
        end

        jal: //use gr[7] as return address register.
        begin
            gr[7] = pc + 16'h0004;
            pc = i_datain[25:0];
        end





        endcase





            



        //write back to general registers
        if (regWrite == 2'b01)
            gr[i_datain[20:16]] = reg_C;
        else if (regWrite == 2'b10)
            gr[i_datain[15:11]] = reg_C;
        

        //pc
        pc <= pc + 16'h0004;
    end


assign d_dataout = dataout;




endmodule
                
