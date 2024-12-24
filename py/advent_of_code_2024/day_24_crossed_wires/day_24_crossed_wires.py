import textwrap
import unittest
from abc import ABC, abstractmethod


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    output_id_to_element = parse_input(puzzle_input)

    # Evaluate all wires starting with 'z'
    result = 0
    multiplier = 1
    for wire_id in sorted(output_id_to_element.keys()):
        if wire_id.startswith("z"):
            result += (
                output_id_to_element[wire_id].evaluate(output_id_to_element)
                * multiplier
            )
            multiplier <<= 1  # Moving left in the binary representation

    return result


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(input_lines):
    output_id_to_element = {}

    wire_part, gate_part = input_lines.split("\n\n")

    # Process the wire values
    for line in wire_part.splitlines():
        if ": " in line:
            wire_id, value = line.split(": ")
            output_id_to_element[wire_id] = Wire(wire_id, int(value))

    # Process the gate operations
    for line in gate_part.splitlines():
        if "->" in line:
            parts = line.split(" -> ")
            operation_part, output_id = parts[0], parts[1]
            inputs = operation_part.split(" ")
            input1_id, operation, input2_id = inputs
            output_id_to_element[output_id] = Gate(
                output_id, input1_id, input2_id, operation
            )

    return output_id_to_element


class Element(ABC):
    def __init__(self, output_id):
        self.output_id = output_id

    @abstractmethod
    def evaluate(self, elements):
        """Subclasses should implement this method."""
        pass


class Wire(Element):
    def __init__(self, output_id, value=None):
        super().__init__(output_id)
        self.value = value

    def evaluate(self, elements):
        return self.value


class Gate(Element):
    def __init__(self, output_id, input1_id, input2_id, operation):
        super().__init__(output_id)
        self.input1_id = input1_id
        self.input2_id = input2_id
        self.operation = operation

    def evaluate(self, elements):
        input1_value = elements[self.input1_id].evaluate(elements)
        input2_value = elements[self.input2_id].evaluate(elements)

        if self.operation == "AND":
            return input1_value & input2_value
        elif self.operation == "OR":
            return input1_value | input2_value
        elif self.operation == "XOR":
            return input1_value ^ input2_value
        else:
            raise ValueError(f"Unknown operation: {self.operation}")


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
            x00: 1
            x01: 0
            x02: 1
            x03: 1
            x04: 0
            y00: 1
            y01: 1
            y02: 1
            y03: 1
            y04: 1
            
            ntg XOR fgs -> mjb
            y02 OR x01 -> tnw
            kwq OR kpj -> z05
            x00 OR x03 -> fst
            tgd XOR rvg -> z01
            vdt OR tnw -> bfw
            bfw AND frj -> z10
            ffh OR nrd -> bqk
            y00 AND y03 -> djm
            y03 OR y00 -> psh
            bqk OR frj -> z08
            tnw OR fst -> frj
            gnj AND tgd -> z11
            bfw XOR mjb -> z00
            x03 OR x00 -> vdt
            gnj AND wpb -> z02
            x04 AND y00 -> kjc
            djm OR pbm -> qhw
            nrd AND vdt -> hwm
            kjc AND fst -> rvg
            y04 OR y02 -> fgs
            y01 AND x02 -> pbm
            ntg OR kjc -> kwq
            psh XOR fgs -> tgd
            qhw XOR tgd -> z09
            pbm OR djm -> kpj
            x03 XOR y03 -> ffh
            x00 XOR y04 -> ntg
            bfw OR bqk -> z06
            nrd XOR fgs -> wpb
            frj XOR qhw -> z04
            bqk OR frj -> z07
            y03 OR x01 -> nrd
            hwm AND bqk -> z03
            tgd XOR rvg -> z12
            tnw OR pbm -> gnj
        """
        ).strip()
        expected_output = 2024
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
