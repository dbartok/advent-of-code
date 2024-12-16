import textwrap
import unittest
import itertools
from pygame.math import Vector2
from copy import deepcopy


class HashableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableVector):
            return self.x == other.x and self.y == other.y
        return False


Vector = HashableVector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid, moves = parse_input(puzzle_input)
    robot_sim = WarehouseRobot(grid, moves)
    robot_sim.run_simulation()
    return robot_sim.compute_gps_sum()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(input_data):
    grid_section, moves_section = input_data.split("\n\n")
    grid = [list(row) for row in grid_section.splitlines()]
    moves = moves_section.replace("\n", "")
    return grid, moves


class WarehouseRobot:
    def __init__(self, grid, moves):
        self._robot_position = None
        self._wall_positions = set()
        self._box_positions = set()

        # Generate all coordinate pairs (x, y) based on grid dimensions
        height, width = len(grid), len(grid[0])
        coordinates = itertools.product(range(width), range(height))

        for x, y in coordinates:
            cell = grid[y][x]
            if cell == '.':
                continue

            position = Vector(x, y)
            if cell == '@':
                self._robot_position = position
            elif cell == '#':
                self._wall_positions.add(position)
            else:
                self._box_positions.add(position)

        self._moves = moves

    def run_simulation(self):
        for move in self._moves:
            direction = self._get_direction(move)
            self._move_robot(direction)

    def compute_gps_sum(self):
        return sum(100 * box_position.y + box_position.x for box_position in self._box_positions)

    def _move_robot(self, direction):
        new_position = self._robot_position + direction
        if new_position not in self._wall_positions:
            potentional_box_position = deepcopy(new_position)
            boxes_pushed = []
            while potentional_box_position not in self._wall_positions and potentional_box_position in self._box_positions:
                boxes_pushed.append(deepcopy(potentional_box_position))
                potentional_box_position += direction

            if self._can_push_boxes(boxes_pushed, direction):
                self._push_boxes(boxes_pushed, direction)
                self._robot_position = new_position

    def _can_push_boxes(self, boxes, direction):
        if not boxes:
            return True

        # Check if there is space to push the boxes
        last_box_pos = boxes[-1] + direction
        return last_box_pos not in self._wall_positions

    def _push_boxes(self, boxes_pushed, direction):
        # Reverse the order to prevent boxes from temporarily overlapping when moved.
        # This ensures each box moves to its new position without conflicting with others in the set.
        for box in boxes_pushed[::-1]:
            self._box_positions.remove(box)
            new_pos = box + direction
            self._box_positions.add(new_pos)

    def _get_direction(self, move):
        if move == '>':
            return Vector(1, 0)
        elif move == '<':
            return Vector(-1, 0)
        elif move == '^':
            return Vector(0, -1)
        elif move == 'v':
            return Vector(0, 1)


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
            ##########
            #..O..O.O#
            #......O.#
            #.OO..O.O#
            #..O@..O.#
            #O#..O...#
            #O..O..O.#
            #.OO.O.OO#
            #....O...#
            ##########
            
            <vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
            vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
            ><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
            <<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
            ^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
            ^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
            >^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
            <><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
            ^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
            v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^
        """).strip()
        expected_output = 10092
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
