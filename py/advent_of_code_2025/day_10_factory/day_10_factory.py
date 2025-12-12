import textwrap
import unittest
from itertools import combinations
from z3 import Int, Optimize, sat


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    total_press_count = 0
    for line in puzzle_input.splitlines():
        diagram, buttons, _ = parse_line(line)
        total_press_count += calculate_fewest_presses_to_achieve_diagram(diagram, buttons)
    return total_press_count


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    total_press_count = 0
    for line in puzzle_input.strip().splitlines():
        _, buttons, joltages = parse_line(line)
        total_press_count += calculate_fewest_presses_to_achieve_joltages(buttons, joltages)
    return total_press_count


def parse_line(line):
    # Example:
    # [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
    parts = line.split()

    # Diagram
    diagram_raw = parts[0]  # "[.##.]"
    diagram = [c == "#" for c in diagram_raw[1:-1]]

    # Everything after the diagram until the final {} are buttons
    button_parts = parts[1:-1]  # (3) (1,3) (2) (2,3) (0,2) (0,1)
    buttons = []
    for bp in button_parts:
        assert bp[0] == "(" and bp[-1] == ")"
        inner = bp[1:-1].strip()
        buttons.append(tuple(int(x) for x in inner.split(",")))

    joltages_raw = parts[-1]  # "{3,5,4,7}"
    joltages = tuple(int(x) for x in joltages_raw[1:-1].split(","))

    return diagram, buttons, joltages


def calculate_fewest_presses_to_achieve_diagram(diagram, buttons):
    """
    Treat each button as pressable only 0 or 1 time.
    Check subsets by increasing size until the target diagram is matched.
    """

    numbers = range(len(diagram))

    for subset_size in range(len(buttons) + 1):
        for buttons_pressed in combinations(buttons, subset_size):
            lights = [0] * len(numbers)

            for button in buttons_pressed:
                for light_index in button:
                    lights[light_index] ^= 1

            if lights == diagram:
                return subset_size


def calculate_fewest_presses_to_achieve_joltages(buttons, joltages):
    """
    Minimize total presses.
    buttons: list of tuples of indices affected by each button
    joltage: tuple of target values for each counter
    """
    optimizer = Optimize()

    num_buttons = len(buttons)
    num_counters = len(joltages)

    # Variables: presses per button
    x = [Int(f"x_{j}") for j in range(num_buttons)]
    for var in x:
        optimizer.add(var >= 0)  # non-negative

    # For each counter, build linear equality
    for i in range(num_counters):
        optimizer.add(sum(x[j] for j in range(num_buttons) if i in buttons[j]) == joltages[i])

    # Objective: minimize total presses
    total = sum(x)
    optimizer.minimize(total)

    if optimizer.check() != sat:
        raise RuntimeError("No solution")

    model = optimizer.model()
    return sum(model[var].as_long() for var in x)


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
        [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
        [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
        [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
        """
    ).strip()

    def test_part_one(self):
        expected_output = 7
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 33
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
