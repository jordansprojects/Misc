// half_adder test bench from verilog guide
`timescale 1 ns/10 ps  // time-unit = 1 ns, precision = 10 ps
module half_adder_tb;
    reg a, b;
    wire sum, carry;
    // duration for each bit = 20 * timescale = 20 * 1 ns  = 20ns
    localparam period = 20;  
    half_adder UUT (.A(a), .B(b), .Sum(sum), .Carry(carry)); 
    initial begin // initial block executes only once
     $dumpfile("half_adder.vcd");
     $dumpvars(0,UUT);
            // values for a and b
            a = 0;
            b = 0;
            #period; // wait for period 

            a = 0;
            b = 1;
            #period;

            a = 1;
            b = 0;
            #period;

            a = 1;
            b = 1;
            #period;
        end
endmodule
