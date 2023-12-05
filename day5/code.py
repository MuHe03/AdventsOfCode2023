lines = open("input.txt").readlines()
seeds = [int(x) for x in lines[0].split(": ")[1].split(' ')]

rels = []
curpos = 3
for i in range(7):
    rel = []
    while curpos < len(lines) and lines[curpos] != '\n':
        [x, y, l] = [int(x) for x in lines[curpos].split(' ')]
        rel += [(y, y + l - 1, x - y)]
        curpos += 1
    curpos += 2
    rel.sort()
    rels += [rel]

print(rels)

locs = seeds
for rel in rels:
    nxt = locs
    for i in range(len(locs)):
        for (l, r, v) in rel:
            if locs[i] >= l and locs[i] <= r:
                nxt[i] += v
                break
    locs = nxt
print('task1:', min(locs))

