import textwrap
import unittest
import re


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    register_a, register_b, register_c, program = parse_input(puzzle_input)
    computer = ThreeBitComputer(register_a, register_b, register_c, program)
    computer.run()
    return computer.get_output()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(puzzle_input):
    # Regex to extract register values
    register_pattern = r"Register A: (\d+)\nRegister B: (\d+)\nRegister C: (\d+)"
    match = re.search(register_pattern, puzzle_input)
    register_a = int(match.group(1))
    register_b = int(match.group(2))
    register_c = int(match.group(3))

    # Regex to extract the program list (comma-separated numbers)
    program_pattern = r"Program:\s*(.*)"
    match = re.search(program_pattern, puzzle_input)
    program_str = match.group(1)
    program = list(map(int, program_str.split(',')))

    return register_a, register_b, register_c, program


class ThreeBitComputer:
    def __init__(self, register_a, register_b, register_c, program):
        # Initialize registers and program
        self.register_a = register_a
        self.register_b = register_b
        self.register_c = register_c
        self.program = program
        self.instruction_pointer = 0
        self.output = []

    def run(self):
        while self.instruction_pointer < len(self.program):
            opcode = self.program[self.instruction_pointer]
            operand = self.program[self.instruction_pointer + 1]
            self._execute_instruction(opcode, operand)

            self.instruction_pointer += 2

    def get_output(self):
        return ",".join(map(str, self.output))

    def _execute_instruction(self, opcode, operand):
        # Process instructions based on the opcode
        if opcode == 0:
            self._adv(operand)
        elif opcode == 1:
            self._bxl(operand)
        elif opcode == 2:
            self._bst(operand)
        elif opcode == 3:
            self._jnz(operand)
        elif opcode == 4:
            self._bxc(operand)
        elif opcode == 5:
            self._out(operand)
        elif opcode == 6:
            self._bdv(operand)
        elif opcode == 7:
            self._cdv(operand)

    # Adv instruction (opcode 0)
    def _adv(self, operand):
        operand = self._resolve_combo_operand(operand)
        denominator = 2 ** operand
        self.register_a //= denominator

    # Bxl instruction (opcode 1)
    def _bxl(self, operand):
        self.register_b ^= operand

    # Bst instruction (opcode 2)
    def _bst(self, operand):
        operand = self._resolve_combo_operand(operand)
        self.register_b = operand % 8

    # Jnz instruction (opcode 3)
    def _jnz(self, operand):
        if self.register_a != 0:
            # Subtract 2 so that the next instruction pointer step lands exactly on the desired instruction
            self.instruction_pointer = operand - 2

    # Bxc instruction (opcode 4)
    def _bxc(self, operand):
        self.register_b ^= self.register_c

    # Out instruction (opcode 5)
    def _out(self, operand):
        operand = self._resolve_combo_operand(operand)
        self.output.append(operand % 8)

    # Bdv instruction (opcode 6)
    def _bdv(self, operand):
        operand = self._resolve_combo_operand(operand)
        denominator = 2 ** operand
        self.register_b = self.register_a // denominator

    # Cdv instruction (opcode 7)
    def _cdv(self, operand):
        operand = self._resolve_combo_operand(operand)
        denominator = 2 ** operand
        self.register_c = self.register_a // denominator

    def _resolve_combo_operand(self, operand):
        if operand == 4:
            return self.register_a
        elif operand == 5:
            return self.register_b
        elif operand == 6:
            return self.register_c
        else:
            return operand


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
            Register A: 729
            Register B: 0
            Register C: 0
            
            Program: 0,1,5,4,3,0
        """).strip()
        expected_output = "4,6,3,5,6,3,5,2,1,0"
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
