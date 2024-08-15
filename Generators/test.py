import sys
sys.stdin = open('Random\output.txt', 'r')
x = [int(i) for i in input().split()]
print(len(x))

import sys
sys.stdin = open('Random\input.txt','r')
sys.stdout = open('Random\output.txt', 'w')
x = input()
for i in x:
    if i != '[' and i != ']' and i != ',':
        print(i, end="")
    else: print(" ", end="")