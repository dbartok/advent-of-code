import textwrap
import unittest
from collections import deque


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = parse_input(puzzle_input)
    topographic_map = TopographicMap(grid)
    return topographic_map.get_total_score()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(puzzle_input):
    return [[int(c) for c in line.strip()] for line in puzzle_input.splitlines()]


class TopographicMap:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

    def _is_within_bounds(self, x, y):
        return 0 <= x < self._width and 0 <= y < self._height

    def _get_num_good_hiking_trails_starting_from(self, start_x, start_y):
        # Trails always start a 0
        if self._grid[start_y][start_x] != 0:
            return 0

        # BFS to explore reachable height 9 cells
        queue = deque([(start_x, start_y)])
        visited = set()
        visited.add((start_x, start_y))
        num_reachable_nines = 0

        while queue:
            x, y = queue.popleft()
            if self._grid[y][x] == 9:
                num_reachable_nines += 1
                continue

            # Explore neighbors (left, right, up, down)
            for delta_x, delta_y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                new_x, new_y = x + delta_x, y + delta_y
                if (self._is_within_bounds(new_x, new_y)
                        and (new_x, new_y) not in visited
                        and self._grid[new_y][new_x] == self._grid[y][x] + 1):
                    visited.add((new_x, new_y))
                    queue.append((new_x, new_y))

        return num_reachable_nines

    def get_total_score(self):
        return sum(self._get_num_good_hiking_trails_starting_from(x, y)
                   for y in range(self._height)
                   for x in range(self._width))


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent("""
            89010123
            78121874
            87430965
            96549874
            45678903
            32019012
            01329801
            10456732
        """).strip()
        expected_output = 36
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
