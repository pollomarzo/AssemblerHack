// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/07/MemoryAccess/BasicTest/BasicTest.tst

load BasicTest.asm,
output-file BasicTest.out,
compare-to BasicTest.cmp,
output-list RAM[256]%D1.6.1 RAM[300]%D1.6.1 RAM[401]%D1.6.1 
            RAM[402]%D1.6.1 RAM[16]%D1.6.1 RAM[18]%D1.6.1
            RAM[17]%D1.6.1 RAM[19]%D1.6.1;

set RAM[1] 300,
set RAM[2] 400,
set RAM[3] 3000,
set RAM[4] 3010,

repeat 600 {
  ticktock;
}

output;
