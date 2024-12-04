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
    word_search = WordSearch(grid, "XMAS")
    return word_search.get_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class WordSearch:
    # List of direction vectors (delta x, delta y)
    DIRECTIONS = [
        Vector(0, -1),  # Up (vertical)
        Vector(-1, 0),  # Left (horizontal)
        Vector(1, 0),  # Right (horizontal)
        Vector(0, 1),  # Down (vertical)
        Vector(1, 1),  # Bottom-Right Diagonal
        Vector(1, -1),  # Bottom-Left Diagonal
        Vector(-1, 1),  # Top-Right Diagonal
        Vector(-1, -1)  # Top-Left Diagonal
    ]

    def __init__(self, grid, target_word):
        self.grid = grid
        self.target_word = target_word

        self.height = len(grid)
        self.width = len(grid[0])

    def get_count(self):
        start_positions = [(x, y) for y in range(self.height) for x in range(self.width)]
        count = 0

        for (x, y) in start_positions:
            for direction_delta in self.DIRECTIONS:
                word_in_direction = self._get_word_in_direction(Vector(x, y), direction_delta)
                if word_in_direction == self.target_word:
                    count += 1

        return count

    def _get_word_in_direction(self, start_position, direction_delta):
        position = start_position
        word = []

        for i in range(len(self.target_word)):
            if not (0 <= position.x < self.width and 0 <= position.y < self.height):
                return ""
            word.append(self.grid[int(position.y)][int(position.x)])
            position += direction_delta

        return ''.join(word)


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
            MMMSXXMASM
            MSAMXMSMSA
            AMXSXMAAMM
            MSAMASMSMX
            XMASAMXAMM
            XXAMMXXAMA
            SMSMSASXSS
            SAXAMASAAA
            MAMMMXMMMM
            MXMXAXMASX
        """).strip()
        expected_output = 18
        self.assertEqual(solve_part_one(puzzle_input), expected_output)

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
