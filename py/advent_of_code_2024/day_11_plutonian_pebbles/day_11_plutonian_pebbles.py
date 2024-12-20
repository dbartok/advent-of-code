import textwrap
import unittest
from collections import defaultdict


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    return get_num_stones_after_repeated_blinks(puzzle_input, 25)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    return get_num_stones_after_repeated_blinks(puzzle_input, 75)


def get_num_stones_after_repeated_blinks(puzzle_input, num_blinks):
    stones = list(map(int, puzzle_input.split(" ")))
    simulator = StoneBlinkSimulator(stones)
    simulator.blink_repeatedly(num_blinks)
    return simulator.get_num_stones()


class StoneBlinkSimulator:
    def __init__(self, initial_stones):
        self._stone_to_count = defaultdict(int)
        for stone in initial_stones:
            self._stone_to_count[stone] += 1

    def blink_repeatedly(self, num_blinks):
        for _ in range(num_blinks):
            self._blink()

    def get_num_stones(self):
        return sum(self._stone_to_count.values())

    def _blink(self):
        updated_stone_to_count = defaultdict(int)

        for stone, count in self._stone_to_count.items():
            stone_str = str(stone)

            if stone == 0:
                updated_stone_to_count[1] += count
            elif len(stone_str) % 2 == 0:
                mid = len(stone_str) // 2
                left, right = int(stone_str[:mid]), int(stone_str[mid:])

                updated_stone_to_count[left] += count
                updated_stone_to_count[right] += count
            else:
                updated_stone_to_count[stone * 2024] += count

        self._stone_to_count = updated_stone_to_count


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
        125 17
    """
    ).strip()

    def test_part_one(self):
        expected_output = 55312
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 65601038650482
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
