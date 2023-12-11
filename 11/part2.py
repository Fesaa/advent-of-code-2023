with open("input", "r") as f:
    R = f.read()

EXP = 1_000_000

universe: list[list[tuple[str, int, int]]] = []

for line in R.split("\n"):
    if line.strip() == "":
        continue
    mul = 1 if "#" in line else EXP
    universe.append([(c, mul, 1) for c in line])


to_add: list[int] = []

for i in range(len(universe[0])):
    if "#" not in [row[i][0] for row in universe]:
        to_add.append(i)

for i in to_add:
    for row in universe:
        row[i] = (row[i][0], row[i][1], EXP)


coords: list[tuple[int, int]] = [(i, j) for i in range(len(universe)) for j in range(len(universe[0])) if universe[i][j][0] == "#"]

sum: int = 0
for c1 in coords:
    for c2 in coords:
        if c1 == c2:
            continue

        d: int = 0
        yStart = min(c1[0], c2[0])
        yEnd = max(c1[0], c2[0])
        for i in range(yStart+1, yEnd + 1):
            a = universe[i][c1[0]]
            d += universe[i][c1[0]][1]

        xStart = min(c1[1], c2[1])
        xEnd = max(c1[1], c2[1])
        for i in range(xStart+1, xEnd + 1):
            a = universe[c1[1]][i]
            d += a[2]

        sum += d

print(sum//2)
