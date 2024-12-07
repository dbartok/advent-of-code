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
    grid = puzzle_input.splitlines()
    word_search = XShapeWordSearch(grid, "MAS")
    return word_search.get_count()


class WordSearch:
    # List of direction vectors (delta x, delta y)
    DIRECTIONS = [
        Vector(0, -1),  # Up (vertical)
        Vector(-1, 0),  # Left (horizontal)
        Vector(1, 0),  # Right (horizontal)
        Vector(0, 1),  # Down (vertical)
        Vector(-1, -1),  # Top-Left Diagonal
        Vector(-1, 1),  # Top-Right Diagonal
        Vector(1, -1),  # Bottom-Left Diagonal
        Vector(1, 1),  # Bottom-Right Diagonal
    ]

    def __init__(self, grid, target_word):
        self._grid = grid
        self._target_word = target_word

        self._height = len(grid)
        self._width = len(grid[0])

    def get_count(self):
        start_positions = [(x, y) for y in range(self._height) for x in range(self._width)]
        count = 0

        for (x, y) in start_positions:
            for direction_delta in self.DIRECTIONS:
                word_in_direction = self._get_word_in_direction(Vector(x, y), direction_delta)
                if word_in_direction == self._target_word:
                    count += 1

        return count

    def _get_word_in_direction(self, start_position, direction_delta):
        position = start_position
        word = []

        for i in range(len(self._target_word)):
            if not (0 <= position.x < self._width and 0 <= position.y < self._height):
                return ""
            word.append(self._grid[int(position.y)][int(position.x)])
            position += direction_delta

        return ''.join(word)


class XShapeWordSearch(WordSearch):
    def get_count(self):
        center_positions = [(x, y) for y in range(1, self._height - 1) for x in range(1, self._width - 1)]
        assert len(self._target_word) == 3
        start_char = self._target_word[0]
        center_char = self._target_word[1]
        end_char = self._target_word[2]
        count = 0

        for (x, y) in center_positions:
            if self._grid[y][x] != center_char:
                continue

            top_left = self._grid[y - 1][x - 1]
            top_right = self._grid[y - 1][x + 1]
            bottom_left = self._grid[y + 1][x - 1]
            bottom_right = self._grid[y + 1][x + 1]
            corner_characters = [
                top_left,
                top_right,
                bottom_left,
                bottom_right
            ]

            if (
                    corner_characters.count(start_char) == 2
                    and corner_characters.count(end_char) == 2
                    and top_left != bottom_right
            ):
                count += 1

        return count


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    PUZZLE_INPUT = textwrap.dedent("""
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

    def test_part_one(self):
        expected_output = 18
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 9
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
