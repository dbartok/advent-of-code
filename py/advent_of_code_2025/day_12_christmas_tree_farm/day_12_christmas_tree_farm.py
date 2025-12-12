import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    fit_count = 0
    for line in puzzle_input.splitlines():
        # Skip shape lines
        if "x" not in line:
            continue

        # Simplified packing algo, assuming that each shape takes its own 3x3 area in the region
        size, *nums = line.split()
        size = size.rstrip(":")
        w, h = map(int, size.split("x"))
        slots = (w // 3) * (h // 3)
        needed = sum(int(x) for x in nums)
        if needed <= slots:
            fit_count += 1

    return fit_count


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent(
            """
            0:
            ###
            ##.
            ##.

            1:
            ###
            ##.
            .##

            2:
            .##
            ###
            ##.

            3:
            ##.
            ###
            ##.

            4:
            ###
            #..
            ###

            5:
            ###
            .#.
            ###

            4x4: 0 0 0 0 2 0
            12x5: 1 0 1 0 2 2
            12x5: 1 0 1 0 3 2
            4x4: 1 0 0 0 0 0
            """
        ).strip()
        expected_output = 1
        self.assertEqual(expected_output, solve_part_one(puzzle_input))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
