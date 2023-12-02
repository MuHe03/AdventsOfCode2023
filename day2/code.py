games = []

with open("input.txt") as finput:
    lines = finput.readlines()
    for line in lines:
        id = int(line.split(': ')[0].split(' ')[1])
        line = line.split(': ')[1][0:-1]
        game = []
        for set in line.split('; '):
            r, g, b = 0, 0, 0
            for col in set.split(', '): 
                num = int(col.split(' ')[0])
                c = col.split(' ')[1]
                if c == 'red':
                    r += num 
                if c == 'green': 
                    g += num 
                if c == 'blue':
                    b += num 
            game = game + [(r, g, b)]
        games = games + [(id, game)]
            
# task1
ans = 0
for (id, game) in games:
    f = True 
    for (r, g, b) in game:
        f = f and r <= 12 and g <= 13 and b <= 14 
    if f:
        ans += id 
print("task1:", ans)

ans = 0
for (id, game) in games:
    r, g, b = 0, 0, 0
    for (rr, gg, bb) in game: 
        r, g, b = max(r, rr), max(g, gg), max(b, bb)
    ans += r * g * b
print("task2:", ans)