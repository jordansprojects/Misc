// Half Adder from Computer Architecture MIPS Editon
module half_adder(A,B, Sum,Carry);
  input A, B; //Two 1-bit inputs
  output Sum, Carry; // Two 1-bit outputs
  assign Sum = A^B; // sum is A XOR B
  assign Carry = A & B; //Carry is A AND B
endmodule
