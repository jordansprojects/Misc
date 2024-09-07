//multiplexor_tb.v

`timescale 1 ns/10 ps  // time-unit = 1 ns, precision = 10 ps
module multiplexor_tb;
    reg [0:31] a,b,c,d; // each input, let a = in1 b = in2....
    reg [0:1] sel; 		// selector signal
    // duration for each bit = 20 * timescale = 20 * 1 ns  = 20ns
    localparam period = 20;  
    multiplexor UUT (.In1(a), .In2(b), .In3(c), .In4(d), .Sel(sel)); 
    initial begin // initial block executes only once
     $dumpfile("multiplexor.vcd");
     $dumpvars(0,UUT);
            // initial values for each input
	    // increase in order to make it easy to determine which input is
	    // being selected 
	    a = 1;
	    b = 2;
	    c = 3;
	    d = 4;
	    sel = 0;
            #period; // wait for period 
            sel = 1;
            #period;
            sel = 2;
            #period;
	    sel= 3;
            #period;
        end
endmodule
