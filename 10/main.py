with open("input","r") as f:
	R=f.read()
grid=R.split("\n")
height=len(grid)
width=len(grid[0])

holder = [[0]*width for _ in range(height)] # part 2

curX = -1
curY = -1
for i in range(height):
	for j in range(width):
		if "S" in grid[i]:
			curX=i
			curY=grid[i].find("S")

# rightward downward leftward upward
dirs = [(0,1),(1,0),(0,-1),(-1,0)]
canMoveIn = ["-7J", "|LJ", "-FL", "|F7"]
Sdirs = []
for i in range(4):
    pos = dirs[i]
    nextX = curX+pos[0]
    nextY = curY+pos[1]
    if nextX < 0:
        continue
    if nextX > height:
        continue
    if nextY < 0:
        continue
    if nextY > width:
        continue
    if grid[nextX][nextY] not in canMoveIn[i]:
        continue
    Sdirs.append(i)

Svalid = 3 in Sdirs

# rightward downward leftward upward
transform: dict[tuple[int, str], int] = {
	(0,"-"): 0,
	(0,"7"): 1,
	(0,"J"): 3,
	(2,"-"): 2,
	(2,"F"): 1,
	(2,"L"): 3,
	(1,"|"): 1,
	(1,"L"): 0,
	(1,"J"): 2,
	(3,"|"): 3,
	(3,"F"): 0,
	(3,"7"): 2,
}

curdir = Sdirs[0]
cntX = curX + dirs[curdir][0]
cntY = curY + dirs[curdir][1]
length = 1
holder[curX][curY] = 1
while (cntX,cntY)!=(curX,curY):
	holder[cntX][cntY] = 1
	length += 1
	curdir = transform[(curdir,grid[cntX][cntY])]
	cntX = cntX + dirs[curdir][0]
	cntY = cntY + dirs[curdir][1]
print("Part 1: ", length//2)

area = 0
for i in range(height):
	inn = False
	for j in range(width):
		if holder[i][j]:
			if grid[i][j] in "|JL" or (grid[i][j]=="S" and Svalid): inn = not inn
		else:
			area += inn
print("Part 2: ", area)
