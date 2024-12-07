import textwrap
import unittest
from pygame.math import Vector2 as Vector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = puzzle_input.splitlines()
    simulator = GuardPatrolSimulator(grid)
    simulator.simulate()
    return simulator.get_visited_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class GuardPatrolSimulator:
    # Order of directions (up, right, down, left)
    DIRECTIONS = ['^', '>', 'v', '<']

    # Movement deltas for directions: up, right, down, left
    DELTAS = {
        '^': Vector(0, -1),  # Move up
        '>': Vector(1, 0),  # Move right
        'v': Vector(0, 1),  # Move down
        '<': Vector(-1, 0),  # Move left
    }

    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

        self._current_position = self._find_start_position()
        self._current_direction_index = 0  # Start by facing up ('^')

        self.visited = set()

    def simulate(self):
        while self._is_within_bounds(self._current_position):
            self.visited.add((self._current_position.x, self._current_position.y))

            direction = self.DIRECTIONS[self._current_direction_index]
            next_position = self._current_position + self.DELTAS[direction]
            if self._is_within_bounds(next_position) and self._get_element_at(next_position) == '#':
                self._turn_right()
            else:
                self._current_position = next_position

    def get_visited_count(self):
        return len(self.visited)

    def _find_start_position(self):
        return next(
            Vector(x, y) for y in range(self._height) for x in range(self._width)
            if self._get_element_at(Vector(x, y)) == '^'
        )

    def _is_within_bounds(self, position):
        return 0 <= position.x < self._width and 0 <= position.y < self._height

    def _turn_right(self):
        self._current_direction_index = (self._current_direction_index + 1) % 4

    def _get_element_at(self, position):
        return self._grid[int(position.y)][int(position.x)]


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
            ....#.....
            .........#
            ..........
            ..#.......
            .......#..
            ..........
            .#..^.....
            ........#.
            #.........
            ......#...
        """).strip()
        expected_output = 41
        self.assertEqual(solve_part_one(puzzle_input), expected_output)

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
