temp=0x1ff
tmp=0xffffffffffffffff
uselenght=0
size=3
print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-(uselenght+size))))
uselenght+=size
size=6
print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-size)))
print(hex(int("111111",2)))