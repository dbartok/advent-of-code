import textwrap
import unittest
import networkx as nx


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    G = build_graph(puzzle_input)
    return len(list(nx.all_simple_paths(G, "you", "out")))


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    G = build_graph(puzzle_input)

    # case A: svr -> dac -> fft -> out
    a1 = count_paths_dag(G, "svr", "dac")
    a2 = count_paths_dag(G, "dac", "fft")
    a3 = count_paths_dag(G, "fft", "out")
    case_a = a1 * a2 * a3

    # case B: svr -> fft -> dac -> out
    b1 = count_paths_dag(G, "svr", "fft")
    b2 = count_paths_dag(G, "fft", "dac")
    b3 = count_paths_dag(G, "dac", "out")
    case_b = b1 * b2 * b3

    return case_a + case_b


def build_graph(puzzle_input):
    G = nx.DiGraph()
    for line in puzzle_input.splitlines():
        src, rest = line.split(":")
        src = src.strip()
        targets = rest.strip().split()
        for t in targets:
            G.add_edge(src, t)
    return G


def count_paths_dag(G, start, end, memo=None):
    if memo is None:
        memo = {}
    if start == end:
        return 1
    if start in memo:
        return memo[start]
    total = 0
    for neighbor in G.successors(start):
        total += count_paths_dag(G, neighbor, end, memo)
    memo[start] = total
    return total


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
            aaa: you hhh
            you: bbb ccc
            bbb: ddd eee
            ccc: ddd eee fff
            ddd: ggg
            eee: out
            fff: out
            ggg: out
            hhh: ccc fff iii
            iii: out
            """
        ).strip()
        expected_output = 5
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        puzzle_input = textwrap.dedent(
            """
            svr: aaa bbb
            aaa: fft
            fft: ccc
            bbb: tty
            tty: ccc
            ccc: ddd eee
            ddd: hub
            hub: fff
            eee: dac
            dac: fff
            fff: ggg hhh
            ggg: out
            hhh: out
            """
        ).strip()
        expected_output = 2
        self.assertEqual(expected_output, solve_part_two(puzzle_input))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
