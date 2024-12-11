import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    stones = list(map(int, puzzle_input.split(" ")))
    simulator = StoneBlinkSimulator(stones)
    simulator.blink_repeatedly(25)
    return simulator.get_num_stones()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class StoneBlinkSimulator:
    def __init__(self, initial_stones):
        self._stones = initial_stones

    def blink_repeatedly(self, num_blinks):
        for _ in range(num_blinks):
            self._blink()

    def get_num_stones(self):
        return len(self._stones)

    def _blink(self):
        updated_stones = []

        for stone in self._stones:
            stone_str = str(stone)

            if stone == 0:
                updated_stones.append(1)
            elif len(stone_str) % 2 == 0:
                mid = len(stone_str) // 2
                left, right = stone_str[:mid], stone_str[mid:]

                updated_stones.append(int(left))
                updated_stones.append(int(right))
            else:
                updated_stones.append(stone * 2024)

        self._stones = updated_stones


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
            125 17
        """).strip()
        expected_output = 55312
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
