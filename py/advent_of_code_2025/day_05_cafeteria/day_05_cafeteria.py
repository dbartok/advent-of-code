import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    ranges, ids = parse_input(puzzle_input)
    return InventorySystem(ranges, ids).count_fresh()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    ranges, ids = parse_input(puzzle_input)
    return InventorySystem(ranges, ids).count_coverage()


def parse_input(puzzle_input):
    ranges_lines, ids_lines = puzzle_input.strip().split("\n\n")

    ranges = []
    for line in ranges_lines.splitlines():
        a, b = line.split('-')
        ranges.append((int(a), int(b)))

    ids = [int(x) for x in ids_lines.splitlines()]

    return ranges, ids


class InventorySystem:
    def __init__(self, ranges, ids):
        self._ranges = ranges
        self._ids = ids
        self._merge_ranges()

    def count_fresh(self):
        return sum(1 for x in self._ids if self._is_fresh(x))

    def count_coverage(self):
        total = 0
        for begin, end in self._ranges:
            total += (end - begin + 1)
        return total

    def _merge_ranges(self):
        if not self._ranges:
            self._ranges = []
            return

        sorted_ranges = sorted(self._ranges)
        merged = [sorted_ranges[0]]

        for begin, end in sorted_ranges[1:]:
            last_begin, last_end = merged[-1]
            if begin <= last_end + 1:
                merged[-1] = (last_begin, max(last_end, end))
            else:
                merged.append((begin, end))

        self._ranges = merged

    def _is_fresh(self, x):
        for a, b in self._ranges:
            if a <= x <= b:
                return True
        return False


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
        3-5
        10-14
        16-20
        12-18

        1
        5
        8
        11
        17
        32
        """
    ).strip()

    def test_part_one(self):
        expected_output = 3
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 14
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
