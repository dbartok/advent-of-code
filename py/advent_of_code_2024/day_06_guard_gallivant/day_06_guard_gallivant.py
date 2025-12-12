import textwrap
import unittest
from copy import deepcopy

from pygame.math import Vector2 as Vector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = [list(line) for line in puzzle_input.splitlines()]
    simulator = GuardPatrolSimulator(grid)
    simulator.simulate()
    return simulator.get_visited_positions_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = [list(line) for line in puzzle_input.splitlines()]
    loop_finder = GuardPatrolLoopFinder(grid)
    return loop_finder.get_loop_count()


class GuardPatrolSimulator:
    # Order of directions (up, right, down, left)
    DIRECTIONS = ["^", ">", "v", "<"]

    # Movement deltas for directions: up, right, down, left
    DELTAS = {
        "^": Vector(0, -1),  # Move up
        ">": Vector(1, 0),  # Move right
        "v": Vector(0, 1),  # Move down
        "<": Vector(-1, 0),  # Move left
    }

    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

        self._current_position = self.find_start_position()
        self._current_direction_index = 0  # Start by facing up ('^')

        self._visited = set()
        self._has_terminated_due_to_loop = False

    def find_start_position(self):
        return next(
            Vector(x, y)
            for y in range(self._height)
            for x in range(self._width)
            if self._get_element_at(Vector(x, y)) == "^"
        )

    def simulate(self):
        while self._is_within_bounds(self._current_position):
            current_state = (
                self._current_position.x,
                self._current_position.y,
                self._current_direction_index,
            )
            if current_state in self._visited:
                self._has_terminated_due_to_loop = True
                break

            self._visited.add(current_state)

            next_position = self._get_next_position()
            if (
                    self._is_within_bounds(next_position)
                    and self._get_element_at(next_position) == "#"
            ):
                self._turn_right()
            else:
                self._current_position = next_position

    def get_visited_positions_count(self):
        distinct_positions = set((x, y) for x, y, _ in self._visited)
        return len(distinct_positions)

    def has_terminated_due_to_loop(self):
        return self._has_terminated_due_to_loop

    def _is_within_bounds(self, position):
        return 0 <= position.x < self._width and 0 <= position.y < self._height

    def _get_next_position(self):
        direction = self.DIRECTIONS[self._current_direction_index]
        return self._current_position + self.DELTAS[direction]

    def _turn_right(self):
        self._current_direction_index = (self._current_direction_index + 1) % 4

    def _get_element_at(self, position):
        return self._grid[int(position.y)][int(position.x)]


class GuardPatrolLoopFinder:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

    def get_loop_count(self):
        simulator = GuardPatrolSimulator(self._grid)
        start_position = simulator.find_start_position()

        return len(
            [
                (x, y)
                for y in range(self._height)
                for x in range(self._width)
                if Vector(x, y) != start_position
                   and self._has_loop_with_obstacle_at(x, y)
            ]
        )

    def _has_loop_with_obstacle_at(self, x, y):
        new_grid = deepcopy(self._grid)
        new_grid[y][x] = "#"
        simulator = GuardPatrolSimulator(new_grid)
        simulator.simulate()
        return simulator.has_terminated_due_to_loop()


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
        """
    ).strip()

    def test_part_one(self):
        expected_output = 41
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 6
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
