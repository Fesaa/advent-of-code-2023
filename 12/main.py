with open("input") as f:
    input = f.read().strip().split("\n")

def replacer(s, newstring, index, nofail=False):
    if not nofail and index not in range(len(s)):
        raise ValueError("index outside given string")

    if index < 0:  # add it to the beginning
        return newstring + s
    if index > len(s):  # add it to the end
        return s + newstring

    return s[:index] + newstring + s[index + 1:]

records: list[tuple[str, list[int], int]] = []
for line in input:
    p = line.split(" ")
    c = list(map(int, p[1].split(",")))
    records.append((p[0], c, sum(c)))

def is_valid(record: tuple[str, list[int], int]) -> bool:
    counts = []
    cur = 0
    for s in record[0]:
        if s == "#":
            cur += 1
        else:
            if cur != 0:
                counts.append(cur)
            cur = 0
    if cur != 0:
        counts.append(cur)
    return counts == record[1]

def permuations(record: tuple[str, list[int], int]) -> int:
    if record[0].count("#") == record[2]:
        return 1 if is_valid(record) else 0
    if "?" not in record[0]:
        return 1 if is_valid(record) else 0
    else:
        i = record[0].index("?")
        a = permuations((replacer(record[0], "#", i), record[1], record[2]))
        b = permuations((replacer(record[0], ".", i), record[1], record[2]))
        return a + b



print("Part 1: ", sum(map(permuations, records)))
