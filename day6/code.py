import re

def task1():
    f = open("input.txt")
    ts = f.readline()
    t = []
    while (ts != ''):
        spos = re.search("\d", ts).start()
        l = len(ts[spos:].split(' ')[0])
        t += [int(ts[spos:spos + l])]
        ts = ts[spos + l:]

    ds = f.readline()
    d = []
    while (ds != ''):
        spos = re.search("\d", ds).start()
        l = len(ds[spos:].split(' ')[0])
        d += [int(ds[spos:spos + l])]
        ds = ds[spos + l:]

    ans = 1
    for i in range(len(d)):
        cnt = 0
        for k in range(t[i] + 1):
            cnt += ((t[i] - k) * k > d[i])
        ans *= cnt
    print("task1:", ans)
    
def task2():
    f = open("input.txt")
    ts = f.readline()
    tss = ''
    while (ts != ''):
        spos = re.search("\d", ts).start()
        l = len(ts[spos:].split(' ')[0])
        tss += ts[spos:spos + l]
        ts = ts[spos + l:]
    t = int(tss)

    ds = f.readline()
    dss = ''
    while (ds != ''):
        spos = re.search("\d", ds).start()
        l = len(ds[spos:].split(' ')[0])
        dss += ds[spos:spos + l]
        ds = ds[spos + l:]
    d = int(dss)

    cnt = 0
    for k in range(t + 1):
        cnt += ((t - k) * k > d)
    print("task1:", cnt)

task1()
task2()