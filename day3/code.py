def getnum(s, pos):
    nums = []
    i = 0
    while i < len(s):
        for j in reversed(range(i, len(s))):
            if s[i:j + 1].isdigit():
                nums += [(int(s[i:j + 1]), i, j, pos)]
                i = j
        i += 1 
    return nums


lines = open("input.txt").readlines()
nums = []
n, m = len(lines), len(lines[1]) - 1
for i in range(n):
    nums += getnum(lines[i], i)

sym = []
for i in range(n):
    for j in range(m):
        if lines[i][j] != '.' and not lines[i][j].isdigit():
            sym += [(i, j)]

sum = 0
for (val, l, r, x) in nums:
    f = False 
    for i in range(max(0, x - 1), min(n, x + 2)):
        for j in range(max(0, l - 1), min(m, r + 2)):
            f |= ((i, j) in sym)
    if f:
        sum += val 
print("task1:", sum)

sum = 0
for (x, y) in sym:
    num = []
    for i in range(max(0, x - 1), min(n, x + 2)):
        for j in range(max(0, y - 1), min(m, y + 2)):
            for (val, l, r, xx) in nums:
                if xx == i and l <= j and j <= r:
                    num += [(val, l, r, xx)]
    num = list(set(num))
    if len(num) == 2:
        sum += num[0][0] * num[1][0]
print("task2:", sum)