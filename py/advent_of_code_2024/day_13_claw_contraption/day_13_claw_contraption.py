import textwrap
import unittest
import re
import sympy as sp


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    machines = parse_input(puzzle_input)
    return get_num_tokens_spent_to_win_all_prizes(machines)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    machines = parse_input(puzzle_input)

    for machine in machines:
        machine.apply_prize_offset(10000000000000)

    return get_num_tokens_spent_to_win_all_prizes(machines)


class ClawMachine:
    def __init__(self, a_x, a_y, b_x, b_y, p_x, p_y):
        """
        Initialize the ClawMachine instance with the coefficients for the system of
        Diophantine equations:
        a_x * A + b_x * B = p_x
        a_y * A + b_y * B = p_y

        A and B represent the number of presses for buttons A and B respectively, initially unknown without solving the equation.

        Parameters:
        ax, ay, bx, by: Coefficients from the machine's Button A and Button B behavior.
        px, py: The target positions (prize location) that need to be matched.
        """
        self.a_x = a_x
        self.a_y = a_y
        self.b_x = b_x
        self.b_y = b_y
        self.p_x = p_x
        self.p_y = p_y

    def apply_prize_offset(self, offset):
        self.p_x += offset
        self.p_y += offset

    def solve_equation(self):
        # Define symbols for the button presses A and B
        A, B = sp.symbols("A B")

        # Define the Diophantine equation for both axes
        eq_x = self.a_x * A + self.b_x * B - self.p_x
        eq_y = self.a_y * A + self.b_y * B - self.p_y

        # Solve the system of equations
        solutions = sp.solve((eq_x, eq_y), (A, B))

        # Check if a valid solution was found
        if solutions and solutions[A].is_integer and solutions[B].is_integer:
            return int(solutions[A]), int(solutions[B])

        # Return None if no valid solution is found
        return None


def parse_input(puzzle_input):
    input_lines = puzzle_input.splitlines()
    machines = []

    # Regex pattern to capture the values for a_x, a_y, b_x, b_y, p_x, p_y
    pattern = re.compile(
        r"Button A: X\+(\d+), Y\+(\d+)\s*Button B: X\+(\d+), Y\+(\d+)\s*Prize: X=(\d+), Y=(\d+)"
    )

    # Parse each line set (3 lines per machine configuration, plus an empty line after each machine)
    for i in range(0, len(input_lines), 4):
        match = pattern.match(input_lines[i] + input_lines[i + 1] + input_lines[i + 2])
        if match:
            a_x, a_y, b_x, b_y, p_x, p_y = map(int, match.groups())
            machines.append(ClawMachine(a_x, a_y, b_x, b_y, p_x, p_y))

    return machines


def get_num_tokens_spent_to_win_all_prizes(machines):
    return sum(
        3 * A + B
        for machine in machines
        if (solution := machine.solve_equation()) is not None
        for A, B in [solution]
    )


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
        Button A: X+94, Y+34
        Button B: X+22, Y+67
        Prize: X=8400, Y=5400

        Button A: X+26, Y+66
        Button B: X+67, Y+21
        Prize: X=12748, Y=12176

        Button A: X+17, Y+86
        Button B: X+84, Y+37
        Prize: X=7870, Y=6450

        Button A: X+69, Y+23
        Button B: X+27, Y+71
        Prize: X=18641, Y=10279
        """
    ).strip()

    def test_part_one(self):
        expected_output = 480
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 875318608908
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
