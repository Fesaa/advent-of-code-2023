with open("input", "r") as f:
    R = f.read()

universe: list[list[str]] = []

for line in R.split("\n"):
    if line.strip() == "":
        continue
    universe.append(list(line))
    if "#" not in line:
        universe.append(list(line))

to_add = []
for i in range(len(universe[0])):
    if "#" not in [row[i] for row in universe]:
        to_add.append(i)

for idx, i in enumerate(to_add):
    for row in universe:
        row.insert(i+idx, ".")

coords: list[tuple[int, int]] = [(i, j) for i in range(len(universe)) for j in range(len(universe[0])) if universe[i][j] == "#"]
sum: int = 0
for c1 in coords:
    for c2 in coords:
        sum += abs(c1[0]-c2[0]) + abs(c1[1]-c2[1])
print(sum//2)
