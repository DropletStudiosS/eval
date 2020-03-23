import sys
import os

f1 = open('test.txt', 'r')
f2 = open('result.txt', 'r')

score = 100

for line1 in f1:
    for line2 in f2:
        if line1 == line2:
            score = score
        else:
            score = score - 10

print(score)

f1.close()
f2.close()
            