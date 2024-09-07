//ALU_tb.v test bench for ALU
module ALU_tb;
	reg[3:0] in;
	reg [7:0] a,b;
	wire [7:0] out;

        // duration for each bit = 20 * timescale = 20 * 1 ns  = 20ns
        localparam period = 20;  

    ALU UUT (.ALUctl(in),  .A(a), .B(b), .ALUOut(out)); 
    initial begin // initial block executes only once
     $dumpfile("ALU.vcd");
     $dumpvars(0,UUT);

// Note : For most gates I will do a =1, b= 0 
// but will not waste time with a = 0, b=1 
// It only makes sense to do it for a - b or a < b
	    // a and b
	    a = 0;
	    b = 0;
	    in = 0;
            #period; // wait for period 
	    
	    a = 1;
	    b = 0;
	    #period 

	    a = 1;
	    b = 1;
	    #period; 

	    // a or b
	    a = 0;
	    b = 0;
	    in = 1;
            #period;

	    a = 1;
	    b = 0;
	    #period;

	    a = 1;
	    b = 1;
	    #period

	    // a + b
	    in = 2;
	    a = 0;
	    b = 0;
	    #period;

	    a = 1;
	    b = 0;
	    #period;

	    a = 1;
	    b = 1;
	    #period;


	    // a - b
            in = 6;
	    a = 0;
	    b = 0;
	    #period;

	    a = 1;
	    b = 0;
	    #period;

	    a = 0;
	    b = 1;
	    #period;


	    a = 1;
	    b = 1;
	    #period;
	   
        
    	   // a < b ? 1 : 0
	   in = 7;
	    a = 0;
	    b = 0;
	    #period;

	    a = 1;
	    b = 0;
	    #period;

	    a = 0;
	    b = 1;
	    #period;


	    a = 1;
	    b = 1;
	    #period;
	   
	   // NOT( a or b)
	   in =12;
	    a = 0;
	    b = 0;
	    #period;

	    a = 1;
	    b = 0;
	    #period;

	    a = 1;
	    b = 1;
	    #period;

    	end

endmodule

