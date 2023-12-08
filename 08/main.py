class Node:
    def __init__(self, code: str, left: str, right: str):
        self.code = code
        self.left = left
        self.right = right

nodes: dict[str, Node] = {}
instructions: list[str] = []

with open("input", "r") as f:
    lines = f.readlines()

    instructions = list(lines[0])[0:-1]
    for line in lines[2:]:
        split = line.split(" = ")
        code = split[0]
        rl = split[1].removeprefix("(").removesuffix(")\n").split(", ")
        left = rl[0]
        right = rl[1]

        nodes[code] = Node(code, left, right)

cur = nodes["AAA"]
steps: int = 0
while cur.code != "ZZZ":
    cur = nodes[cur.left if instructions[steps % len(instructions)] == "L" else cur.right]
    steps += 1

print("Steps:", steps)
