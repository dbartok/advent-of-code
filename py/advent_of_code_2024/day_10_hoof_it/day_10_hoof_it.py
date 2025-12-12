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
    topographic_map.explore()
    return topographic_map.get_total_score()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = parse_input(puzzle_input)
    topographic_map = TopographicMap(grid)
    topographic_map.explore()
    return topographic_map.get_total_rating()


def parse_input(puzzle_input):
    return [[int(c) for c in line.strip()] for line in puzzle_input.splitlines()]


class TopographicMap:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

        self._num_reachable_nines = (
            0  # Will store the total number of reachable 9s (for part 1)
        )
        self._distinct_trails = set()  # Will store distinct hiking trails (for part 2)

    def _is_within_bounds(self, x, y):
        return 0 <= x < self._width and 0 <= y < self._height

    def _explore_paths_from(self, start_x, start_y):
        # If the start is not a trailhead (height 0), return immediately
        if self._grid[start_y][start_x] != 0:
            return

        # BFS to explore reachable cells
        queue = deque(
            [(start_x, start_y, {(start_x, start_y)})]
        )  # Track the path (visited nodes)
        visited_nines = set()  # Track reached 9s for this trailhead

        while queue:
            x, y, trail_path = queue.popleft()

            if self._grid[y][x] == 9:
                # Counting reachable 9s (part 1), ensure each 9 is only counted once per trailhead
                if (x, y) not in visited_nines:
                    self._num_reachable_nines += 1
                    visited_nines.add((x, y))

                # Counting distinct hiking trails (part 2)
                self._distinct_trails.add(frozenset(trail_path))
                continue

            # Explore neighbors (left, right, up, down)
            for delta_x, delta_y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                new_x, new_y = x + delta_x, y + delta_y
                if (
                        self._is_within_bounds(new_x, new_y)
                        and (new_x, new_y) not in trail_path
                        and self._grid[new_y][new_x] == self._grid[y][x] + 1
                ):
                    new_trail_path = trail_path.copy()
                    new_trail_path.add((new_x, new_y))
                    queue.append((new_x, new_y, new_trail_path))

    def explore(self):
        for y in range(self._height):
            for x in range(self._width):
                self._explore_paths_from(x, y)

    def get_total_score(self):
        return self._num_reachable_nines

    def get_total_rating(self):
        return len(self._distinct_trails)


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    PUZZLE_INPUT = textwrap.dedent(
        """
        89010123
        78121874
        87430965
        96549874
        45678903
        32019012
        01329801
        10456732
        """
    ).strip()

    def test_part_one(self):
        expected_output = 36
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 81
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
