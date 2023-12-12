with open("input") as f:
    uinput = f.read().strip().split("\n")


records: list[tuple[str, list[int]]] = []
records2: list[tuple[str, list[int]]] = []
for line in uinput:
    p = line.split(" ")
    c = list(map(int, p[1].split(",")))
    records.append((p[0], c))

    c2 = []
    for _ in range(5):
        for i in c:
            c2.append(i)
    d = p[0]
    records2.append(("?".join((d, d, d, d, d)), c2))

cache: dict[str, int] = {}
def permutations(s: str, counts: list[int]) -> int:
    if s + ";".join(map(str, counts)) in cache:
        return cache[s + ";".join(map(str, counts))]

    if s == "":
        return 1 if len(counts) == 0 else 0

    if len(counts) == 0:
        return 1 if "#" not in s else 0

    perms: int = 0

    if s[0] in (".", "?"):
        perms += permutations(s[1:], counts)

    if s[0] in ("#", "?"):
        if counts[0] > len(s):
            return perms
        if counts[0] != len(s) and s[counts[0]] == "#":
            return perms
        if "."in s[:counts[0]]:
            return perms
        if counts[0] == len(s):
            perms += permutations("", counts[1:])
        else:
            perms += permutations(s[counts[0]+1:], counts[1:])
    cache[s + ";".join(map(str, counts))] = perms
    return perms

print("Part 1:", sum(permutations(r[0], r[1]) for r in records))
print("Part 2:", sum(permutations(r[0], r[1]) for r in records2))


