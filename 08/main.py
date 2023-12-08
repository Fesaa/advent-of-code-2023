class Node:
    def __init__(self, code: str, left: str, right: str):
        self.code = code
        self.left = left
        self.right = right

nodes: dict[str, Node] = {}
instructions: list[str] = []
startNodes:list[str] = []

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
        if code.endswith("A"):
            startNodes.append(code)

cur = nodes.get("AAA", Node("ZZZ", "ZZZ", "ZZZ"))
steps: int = 0
while cur.code != "ZZZ":
    cur = nodes[cur.left if instructions[steps % len(instructions)] == "L" else cur.right]
    steps += 1

print("Part 1 steps:", steps)


# Part 2


loopSteps: list[int] = []
from itertools import cycle
from math import lcm

# This is nonsense, there is not a real guarantee that it loops on the Z end node. It's not how it was explained.
# But it does, so :/
for startNode in startNodes:
    i = 0
    for i, inst in enumerate(cycle(instructions)):
        startNode = nodes[startNode].left if inst == "L" else nodes[startNode].right
        if startNode.endswith("Z"):
            break
    loopSteps.append(i+1)

print("Part 2 steps:", lcm(*loopSteps))




