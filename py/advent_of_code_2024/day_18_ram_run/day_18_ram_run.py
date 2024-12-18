import textwrap
import unittest
from collections import deque
from pygame.math import Vector2


class HashableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableVector):
            return self.x == other.x and self.y == other.y
        return False


Vector = HashableVector


def solve_part_one(puzzle_input, grid_size=71, num_byte_falls_to_simulate=1024):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    byte_falls = parse_input(puzzle_input)
    traverser = MemoryGridTraverser(byte_falls, grid_size, num_byte_falls_to_simulate)
    traverser.find_shortest_path()
    return traverser.get_shortest_path_length()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class MemoryGridTraverser:
    DIRECTIONS = [Vector(0, -1), Vector(0, 1), Vector(-1, 0), Vector(1, 0)]  # Up, Down, Left, Right

    def __init__(self, byte_falls, grid_size, num_byte_falls_to_simulate):
        self._byte_falls = byte_falls
        self._grid_size = grid_size
        self._corrupted_positions = set()
        self._start = Vector(0, 0)
        self._end = Vector(grid_size - 1, grid_size - 1)
        self._corrupted_positions.update([Vector(x, y) for x, y in self._byte_falls[:num_byte_falls_to_simulate]])

        self._shortest_path_length = float('inf')

    def find_shortest_path(self):
        # Queue to store tuples in the form of (current_position, current_steps)
        queue = deque()
        queue.append((self._start, 0))
        visited = {self._start}

        while queue:
            current_position, num_steps = queue.popleft()

            if current_position == self._end:
                self._shortest_path_length = num_steps
                return

            valid_neighbors = self._get_valid_neighbor_positions(current_position)
            unvisited_valid_neighbors = [neighbor for neighbor in valid_neighbors if neighbor not in visited]

            for neighbor_position in unvisited_valid_neighbors:
                visited.add(neighbor_position)
                queue.append((neighbor_position, num_steps + 1))

    def get_shortest_path_length(self):
        return self._shortest_path_length

    def _get_valid_neighbor_positions(self, current_position):
        potential_neighbors = [current_position + direction for direction in self.DIRECTIONS]
        return [neighbor for neighbor in potential_neighbors if self._is_valid_position(neighbor)]

    def _is_valid_position(self, position):
        return 0 <= position.x < self._grid_size and 0 <= position.y < self._grid_size and position not in self._corrupted_positions


def parse_input(input_data):
    # Parse input as a list of tuples (x, y)
    return [tuple(map(int, line.split(','))) for line in input_data.splitlines()]


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
            5,4
            4,2
            4,5
            3,0
            2,1
            6,3
            2,4
            1,5
            0,6
            3,3
            2,6
            5,1
            1,2
            5,5
            2,5
            6,5
            1,4
            0,4
            6,4
            1,1
            6,1
            1,0
            0,5
            1,6
            2,0
        """).strip()
        expected_output = 22
        self.assertEqual(expected_output, solve_part_one(puzzle_input, 7, 12))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
