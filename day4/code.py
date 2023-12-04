lines = open("input.txt").readlines()

def stolist(s):
    l = []
    for x in s.split(' '):
        x = x.strip()
        if x != '':
            l += [int(x)]
    return l

cards = []
for line in lines:
    s1 = line.split(': ')[1].split(' | ')[0]
    l1 = stolist(s1)
    s2 = line.split(': ')[1].split(' | ')[1]
    l2 = stolist(s2)
    cards += [(l1, l2)]
    
score = []
for (l1, l2) in cards:
    score += [sum(x in l1 for x in l2)]

sum = 0
for x in score:
    if x:
        sum += (1 << (x - 1))
print('task1:', sum)

sum = 0
cnt = [1] * len(score)
for i in range(len(score)):
    sum += cnt[i]
    for j in range(i + 1, min(len(score), i + score[i] + 1)):
        cnt[j] += cnt[i]
print('task2:', sum)