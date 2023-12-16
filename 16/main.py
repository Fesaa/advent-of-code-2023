with open('input') as f:
    grid: list[list[str]] = [list(line.strip()) for line in f.readlines()]

class Beam:
    def __init__(self, x: int, y: int, dx: int, dy: int):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy

beams: set[Beam] = set()
beams.add(Beam(-1, 0, 1, 0))

visited: set[tuple[int, int, int, int]] = set()

while len(beams) != 0:
    new_beams: set[Beam] = set()
    to_remove: set[Beam] = set()
    for beam in beams:
        beam.x += beam.dx
        beam.y += beam.dy

        if beam.x < 0 or beam.x >= len(grid[0]) or beam.y < 0 or beam.y >= len(grid):
            to_remove.add(beam)
            continue

        if (beam.x, beam.y, beam.dx, beam.dy) in visited:
            to_remove.add(beam)
            continue

        visited.add((beam.x, beam.y, beam.dx, beam.dy))
        match grid[beam.y][beam.x]:
            case '/':
                beam.dx, beam.dy = -beam.dy, -beam.dx
            case '\\':
                beam.dx, beam.dy = beam.dy, beam.dx
            case '|':
                if beam.dx != 0:
                    beam.dx, beam.dy = 0, 1
                    new_beams.add(Beam(beam.x, beam.y, 0, -1))
            case '-':
                if beam.dy != 0:
                    beam.dx, beam.dy = 1, 0
                    new_beams.add(Beam(beam.x, beam.y, -1, 0))

    beams = beams | new_beams
    beams = beams - to_remove

visitedT: set[tuple[int, int]] = {i[:2] for i in visited}
print(len(visitedT))
