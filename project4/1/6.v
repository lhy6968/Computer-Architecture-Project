`timescale 1ns / 1ps
 
////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   21:22:32 12/29/2014
// Design Name:   CPU
// Module Name:   C:/Users/liang/Desktop/embed/CPU/CPU/CPUTest.v
// Project Name:  CPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: CPU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
 
module CPU_test;
 
    // Inputs
    reg clock;
    reg enable;
    reg reset;
    reg [3:0] select_y;
    reg start;
 
    // Outputs
    wire [15:0] y;
 
    // Instantiate the Unit Under Test (UUT)
    CPU cpu (
        .clock(clock), 
        .enable(enable), 
        .reset(reset),      
        .start(start),     
      .select_y(select_y)     
         
    );
 
    initial begin
        // Initialize Inputs
        clock = 0;
        enable = 0;
        reset = 0;
        select_y = 0;
        start = 0;
 
        // Wait 100 ns for global reset to finish
        #100;
     forever begin
        #5
          clock <= ~clock;
      end  
        // Add stimulus here
    end
initial begin
 
        // Wait 100 ns for global reset to finish
        #100;
$display("pc:     id_ir      :                  ex_ir              :reg_A:     reg_B:   reg_C:     cf: nf: zf:      regC1:      gr1:     gr2:   gr3:   gr4:    gr5:");
$monitor("%h:  %b:           %b:         %h:     %h:     %h:     %h: %h: %h:         %h:      %h:    %h:   %h:   %h:  %h", 
    cpu.pcpu.pc, cpu.pcpu.id_ir, cpu.pcpu.ex_ir, cpu.pcpu.reg_A, cpu.pcpu.reg_B, cpu.pcpu.reg_C,
    cpu.pcpu.cf, cpu.pcpu.nf, cpu.pcpu.zf, cpu.pcpu.reg_C1, cpu.pcpu.gr[1], cpu.pcpu.gr[2], cpu.pcpu.gr[3], cpu.pcpu.gr[4], cpu.pcpu.gr[5]);
     
   enable <= 1; start <= 0; select_y <= 0;
 
#10 reset <= 0;
#10 reset <= 1;
#10 enable <= 1;
#10 start <=1;
#10 start <= 0;
    end
       
endmodule