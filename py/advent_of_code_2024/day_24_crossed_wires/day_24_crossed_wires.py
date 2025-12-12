import textwrap
import unittest
from abc import ABC, abstractmethod
from copy import deepcopy

from graphviz import Digraph
import os

os.environ["PATH"] += os.pathsep + r"C:\Program Files\Graphviz\bin"


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

    original_output_id_to_element = parse_input(puzzle_input)

    original_visualizer = CircuitVisualizer(original_output_id_to_element, "Original")
    original_visualizer.visualize_elements()

    # Deduced manually by examining the output image from above
    swaps = [("z11", "sps"), ("z05", "tst"), ("z23", "frt"), ("cgh", "pmd")]
    fixed_original_output_id_to_element = fix_output_id_to_elements(
        original_output_id_to_element, swaps
    )

    fixed_visualizer = CircuitVisualizer(fixed_original_output_id_to_element, "Fixed")
    fixed_visualizer.visualize_elements()

    flat_list_of_swaps = [item for swap in swaps for item in swap]
    flat_list_of_swaps.sort()
    return ",".join(flat_list_of_swaps)


def fix_output_id_to_elements(output_id_to_element, swaps):
    fixed_output_id_to_element = deepcopy(output_id_to_element)

    for o1, o2 in swaps:
        fixed_output_id_to_element[o1], fixed_output_id_to_element[o2] = (
            fixed_output_id_to_element[o2],
            fixed_output_id_to_element[o1],
        )

    return fixed_output_id_to_element


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


class CircuitVisualizer:
    def __init__(self, output_id_to_element, name):
        self._output_id_to_element = output_id_to_element
        self._name = name

        self._graph = Digraph(comment=f"Circuit Diagram: {name}")

    def visualize_elements(self):
        for element in self._output_id_to_element.values():
            self._add_node(element)
        self._visualize_errors()
        self._graph.render(self._name, format="png")

    def _add_node(self, element):
        if isinstance(element, Wire):
            self._graph.node(element.output_id, element.output_id, color="blue")
        elif isinstance(element, Gate):
            gate_color = "darkgreen" if element.output_id.startswith("z") else "green"

            self._graph.node(
                element.output_id,
                f"{element.output_id}\n{element.input1_id} {element.operation} {element.input2_id}",
                color=gate_color,
            )

            self._graph.edge(element.input1_id, element.output_id)
            self._graph.edge(element.input2_id, element.output_id)

    def _visualize_errors(self):
        z_keys = sorted(
            [key for key in self._output_id_to_element if key.startswith("z")]
        )

        # Skip first two and last z wires, as these don't yet follow the expected structure
        # First two z wires: The circuit begins with a half adder
        # Last z wire: Final output is wired to the final carry
        z_keys_to_check = z_keys[2:-1]

        for z_key in z_keys_to_check:
            z_node = self._output_id_to_element[z_key]
            if not self._is_valid_z_structure(z_node):
                self._graph.node(z_key, color="red", style="filled", fillcolor="red")

    def _is_valid_z_structure(self, z_node):
        # z_n should be an XOR gate
        if not (isinstance(z_node, Gate) and z_node.operation) == "XOR":
            return False

        input1 = self._output_id_to_element[z_node.input1_id]
        input2 = self._output_id_to_element[z_node.input2_id]

        # The inputs to z_n should be an XOR gate and an OR gate
        if (
                not isinstance(input1, Gate)
                or not isinstance(input2, Gate)
                or {input1.operation, input2.operation} != {"XOR", "OR"}
        ):
            return False

        return True


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
        # Manual test only as we've solved the problem through reverse engineering
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
