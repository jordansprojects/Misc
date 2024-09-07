// Multiplexor from Computer Architecture MIPS Edition
module multiplexor(In1, In2, In3, In4, Sel, Out);
   input [31:0] In1, In2, In3, In4; //four 32 bit inputs
   input [1:0] Sel; //selector signal
   output reg[31:0] Out; //32-bit output
   always @(In1,In2,In3,In4,Sel)
   case(Sel) // a 4->1 multiplexor
     0: Out <= In1;
     1: Out <= In2;
     2: Out <= In3;
     default: Out <= In4;
    endcase;
endmodule
