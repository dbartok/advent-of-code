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
    _, _, _, program = parse_input(puzzle_input)
    return solve_recursive(program, 1, 0)


# Find the value of Register A recursively, building on the assumptions from the manual reverse engineering below
def solve_recursive(program, required_match_length, register_a_base_value):
    for current_three_bit_digit in range(8):
        register_a = register_a_base_value + current_three_bit_digit
        output = run_reverse_engineered_program(register_a)
        output_list = list(map(int, output.split(","))) if output else []

        # We build up register A to produce progressively larger suffixes of the output when fed into the program.
        # Therefore, we need to start by matching the last output digit, then the last two, and so on,
        # progressively matching longer suffixes of the program until the entire program is matched.
        expected_output = program[-required_match_length:]
        if output_list == expected_output:
            # Return the solution when the entire program is matched
            if required_match_length == len(program):
                return register_a
            # Recurse to find a larger matching portion of the program
            else:
                return solve_recursive(
                    program, required_match_length + 1, register_a * 8
                )


# Manually reverse engineered version of the program for understandability.
# This manual reverse engineering reveals that each 3-bit digit of Register A determines exactly one digit of the output
def run_reverse_engineered_program(register_a):
    a = register_a
    b = 0
    c = 0
    output = []

    # Instruction: 3, 0
    # jnz - If A is not zero, repeat the loop
    # Pulling this at the front works as long as register A doesn't start off as 0
    while a != 0:
        # Instruction: 2, 4
        # bst - Store A % 8 in register B
        b = a % 8

        # Instruction: 1, 2
        # bxl - XOR register B with 2
        b ^= 2

        # Instruction: 7, 5
        # cdv - Store A // 2^B in register C
        c = a // (2 ** b)

        # Instruction: 4, 5
        # bxc - XOR register B with register C
        b ^= c

        # Instruction: 0, 3
        # adv - Divide A by 8 and store the result in A
        a //= 8

        # Instruction: 1, 7
        # bxl - XOR register B with 7
        b ^= 7

        # Instruction: 5, 5
        # out - Output the value from register B
        output.append(b % 8)

    return ",".join(map(str, output))


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
    program = list(map(int, program_str.split(",")))

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

    # adv instruction (opcode 0)
    def _adv(self, operand):
        operand = self._resolve_combo_operand(operand)
        denominator = 2 ** operand
        self.register_a //= denominator

    # bxl instruction (opcode 1)
    def _bxl(self, operand):
        self.register_b ^= operand

    # bst instruction (opcode 2)
    def _bst(self, operand):
        operand = self._resolve_combo_operand(operand)
        self.register_b = operand % 8

    # jnz instruction (opcode 3)
    def _jnz(self, operand):
        if self.register_a != 0:
            # Subtract 2 so that the next instruction pointer step lands exactly on the desired instruction
            self.instruction_pointer = operand - 2

    # bxc instruction (opcode 4)
    def _bxc(self, operand):
        self.register_b ^= self.register_c

    # out instruction (opcode 5)
    def _out(self, operand):
        operand = self._resolve_combo_operand(operand)
        self.output.append(operand % 8)

    # bdv instruction (opcode 6)
    def _bdv(self, operand):
        operand = self._resolve_combo_operand(operand)
        denominator = 2 ** operand
        self.register_b = self.register_a // denominator

    # cdv instruction (opcode 7)
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
        puzzle_input = textwrap.dedent(
            """
            Register A: 729
            Register B: 0
            Register C: 0

            Program: 0,1,5,4,3,0
            """
        ).strip()
        expected_output = "4,6,3,5,6,3,5,2,1,0"
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        with open("./input.txt") as f:
            puzzle_input = f.read().strip()

        # Verify that the program was correctly reverse engineered by comparing results against the simulation from part one
        expected_output = solve_part_one(puzzle_input)
        self.assertEqual(expected_output, run_reverse_engineered_program(22817223))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
