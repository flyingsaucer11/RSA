#! /usr/bin/env python3.6

'''
Requirement: Python3, GCC
Usage: 
(1) Compiles single C/C++ file 
(2) Prints build output 
(3) Runs the executable
Format: ./runner.py [filename]
Example: ./runner.py fibonacci
The file must be a C/C++ file

'''

import os
import sys
x=sys.argv[1]

str2='Building '+x+'.cpp'+'...'
print(str2)
str1='g++ '+str(x)+'.cpp'+' -o '+str(x)+' 2> result.txt'
os.system(str1)
if os.path.getsize('./result.txt') == 0:
	print("Build Successfull\n")
	str3='./'+x
	os.system(str3)
else:
	print("Build Failed\n")
	f=open('result.txt','r')
	print(f.read())