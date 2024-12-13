import textwrap
import unittest
import re
import math
import numpy as np


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    machines = parse_input(puzzle_input)

    return sum(
        3 * A + B
        for machine in machines
        if (solution := machine.solve_equation()) is not None
        for A, B in [solution]
    )


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


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

    def solve_equation(self):
        """
        The system of equations is:
        a_x * A + b_x * B = p_x
        a_y * A + b_y * B = p_y

        We solve for A and B.

        Returns:
        A tuple with the solution in the form of (A, B) if a valid solution exists,
        otherwise returns None if there is no integer solution.
        """
        # Coefficients matrix (M)
        # M is a 2x2 matrix that represents the system of linear equations.
        # It holds the coefficients for A and B in the following format:
        #
        # M = | a_x  b_x |
        #     | a_y  b_y |
        M = np.array([[self.a_x, self.b_x], [self.a_y, self.b_y]])

        # Constants vector (p)
        # p is a 2x1 vector that holds the constants on the right-hand side of the equations.
        # It represents the target coordinates of the prize:
        #
        # p = | p_x |
        #     | p_y |
        p = np.array([self.p_x, self.p_y])

        # Compute the determinant of M
        # The determinant tells us whether the system has a unique solution.
        # If the determinant is zero, the system has either no solution or infinite solutions.
        # If the determinant is non-zero, the system has a unique solution.
        det = np.linalg.det(M)

        if det == 0:
            return None

        # Compute the inverse of the matrix M
        # If the determinant is non-zero, we can safely calculate the inverse of M.
        M_inv = np.linalg.inv(M)

        # M_inv * p gives us the solution to the system of equations.
        # The resulting vector will contain the values of A and B
        solution = np.dot(M_inv, p)
        A, B = solution

        # Check if the values are close enough to integers, allowing for small floating-point errors
        if math.isclose(A, round(A)) and math.isclose(B, round(B)):
            return int(round(A)), int(round(B))
        else:
            # No valid integer solution
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
        """).strip()
        expected_output = 480
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
