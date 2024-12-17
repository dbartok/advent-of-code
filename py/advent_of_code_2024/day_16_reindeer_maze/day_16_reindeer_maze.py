import textwrap
import unittest
from heapq import heappop, heappush
from pygame.math import Vector2


class HashableComparableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableComparableVector):
            return self.x == other.x and self.y == other.y
        return False

    def __lt__(self, other):
        if isinstance(other, HashableComparableVector):
            return (self.x, self.y) < (other.x, other.y)
        return False


Vector = HashableComparableVector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    reindeer_maze = ReindeerMaze(grid)
    reindeer_maze.traverse()
    return reindeer_maze.get_score()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class ReindeerMaze:
    # Directions are in the order of East, North, West, South (counterclockwise)
    DIRECTIONS = [Vector(1, 0), Vector(0, -1), Vector(-1, 0), Vector(0, 1)]
    EAST_DIRECTION_INDEX = 0

    def __init__(self, grid):
        self._grid = grid
        self._start_position = self._find_position('S')
        self._end_position = self._find_position('E')
        self._score = float('inf')

    def _find_position(self, char):
        for y, row in enumerate(self._grid):
            for x, cell in enumerate(row):
                if cell == char:
                    return Vector(x, y)

    def traverse(self):
        # Priority queue will store tuples of (score, position, direction)
        priority_queue = []
        heappush(priority_queue, (0, self._start_position, self.EAST_DIRECTION_INDEX))
        visited = set()

        while priority_queue:
            current_score, current_position, current_direction_index = heappop(priority_queue)

            # Avoid revisiting the same state
            if (current_position, current_direction_index) in visited:
                continue

            if current_position == self._end_position:
                self._score = current_score
                return

            visited.add((current_position, current_direction_index))

            # Move forward
            forward_position = current_position + self.DIRECTIONS[current_direction_index]
            if self._grid[int(forward_position.y)][int(forward_position.x)] != '#':
                heappush(priority_queue, (current_score + 1, forward_position, current_direction_index))

            # Turn left (counterclockwise)
            new_direction_index = (current_direction_index + 1) % 4
            heappush(priority_queue, (current_score + 1000, current_position, new_direction_index))

            # Turn right (clockwise)
            new_direction_index = (current_direction_index - 1) % 4
            heappush(priority_queue, (current_score + 1000, current_position, new_direction_index))

    def get_score(self):
        return self._score


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
            ###############
            #.......#....E#
            #.#.###.#.###.#
            #.....#.#...#.#
            #.###.#####.#.#
            #.#.#.......#.#
            #.#.#####.###.#
            #...........#.#
            ###.#.#####.#.#
            #...#.....#.#.#
            #.#.#.###.#.#.#
            #.....#...#.#.#
            #.###.#.#.#.#.#
            #S..#.....#...#
            ###############
        """).strip()
        expected_output = 7036
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_one_second_example(self):
        puzzle_input = textwrap.dedent("""
            #################
            #...#...#...#..E#
            #.#.#.#.#.#.#.#.#
            #.#.#.#...#...#.#
            #.#.#.#.###.#.#.#
            #...#.#.#.....#.#
            #.#.#.#.#.#####.#
            #.#...#.#.#.....#
            #.#.#####.#.###.#
            #.#.#.......#...#
            #.#.###.#####.###
            #.#.#...#.....#.#
            #.#.#.#####.###.#
            #.#.#.........#.#
            #.#.#.#########.#
            #S#.............#
            #################
        """).strip()
        expected_output = 11048
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
