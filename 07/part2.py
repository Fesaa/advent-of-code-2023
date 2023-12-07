import collections
lines = [i for i in open('input.txt').read().split('\n') if i.strip()]
def hand(h):
    h2 = ['J23456789TXQKA'.index(i)for i in h]
    ts = []
    for r in '23456789TQKA':
        c = collections.Counter(h.replace('J', r))
        p = tuple(sorted(c.values()))
        t = [(1,1,1,1,1),(1,1,1,2),(1,2,2),(1,1,3),(2,3),(1,4),(5,)].index(p)
        ts.append(t)
    return (max(ts), *h2)

h = sorted((hand(h), int(b)) for h, b in (l.split() for l in lines))
t = 0
for i,(_,b) in enumerate(h):
    t+=(i+1)*b
print('Part2:', t)
