import os

def solve1():
    with open('input.txt') as finput:
        sum = 0
        for s in finput:
            x, posx, y, posy = 0, len(s), 0, -1
            for i in range(1, 10):
                p = s.find(str(i))
                if p != -1 and p < posx:
                    x, posx = i, p 
                p = s.rfind(str(i))
                if p != -1 and p > posy:
                    y, posy = i, p
            sum += x * 10 + y
        print("task1: ", sum)
        
def solve2():
    with open('input.txt') as finput:
        sum = 0
        m = {
            "one"   : 1,
            "1"     : 1,
            "two"   : 2,
            "2"     : 2,
            "three" : 3, 
            "3"     : 3,
            "four"  : 4,
            "4"     : 4,
            "five"  : 5,
            "5"     : 5,
            "six"   : 6,
            "6"     : 6,
            "seven" : 7,
            "7"     : 7,
            "eight" : 8,
            "8"     : 8,
            "nine"  : 9,
            "9"     : 9,
        }
        for s in finput:
            x, posx, y, posy = 0, len(s), 0, -1
            for ss in m: 
                p = s.find(ss)
                if p != -1 and p < posx:
                    x, posx = m[ss], p 
                p = s.rfind(ss)
                if p != -1 and p > posy:
                    y, posy = m[ss], p
            sum += x * 10 + y
        print("task2: ", sum)
        
solve1()
solve2()