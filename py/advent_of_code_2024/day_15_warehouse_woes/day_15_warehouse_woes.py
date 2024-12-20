import textwrap
import unittest
import itertools
from collections import deque

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
    grid, moves = parse_input(puzzle_input)
    robot_sim = WideWareHouseRobot(grid, moves)
    robot_sim.run_simulation()
    return robot_sim.compute_gps_sum()


def parse_input(input_data):
    grid_section, moves_section = input_data.split("\n\n")
    grid = [list(row) for row in grid_section.splitlines()]
    moves = moves_section.replace("\n", "")
    return grid, moves


class WarehouseRobot:
    LEFT = Vector(-1, 0)
    RIGHT = Vector(1, 0)
    UP = Vector(0, -1)
    DOWN = Vector(0, 1)

    def __init__(self, grid, moves):
        self._robot_position = None
        self._wall_positions = set()
        self._box_positions = set()

        # Generate all coordinate pairs (x, y) based on grid dimensions
        height, width = len(grid), len(grid[0])
        coordinates = itertools.product(range(width), range(height))

        for x, y in coordinates:
            cell = grid[y][x]

            position = Vector(x, y)
            if cell == "@":
                self._robot_position = position
            elif cell == "#":
                self._wall_positions.add(position)
            elif cell == "O" or cell == "[":
                self._box_positions.add(position)

        self._moves = moves

    def run_simulation(self):
        for move in self._moves:
            direction = self._get_direction(move)
            self._move_robot(direction)

    def compute_gps_sum(self):
        return int(
            sum(
                100 * box_position.y + box_position.x
                for box_position in self._box_positions
            )
        )

    def _move_robot(self, direction):
        boxes_pushed = self.identify_pushed_boxes(direction)

        if self._can_push_boxes(boxes_pushed, direction):
            self._push_boxes(boxes_pushed, direction)
            self._robot_position += direction

    def identify_pushed_boxes(self, direction):
        potential_box_position = self._robot_position + direction
        boxes_pushed = []

        while (
            potential_box_position not in self._wall_positions
            and potential_box_position in self._box_positions
        ):
            boxes_pushed.append(deepcopy(potential_box_position))
            potential_box_position += direction

        return boxes_pushed

    def _can_push_boxes(self, boxes, direction):
        if not boxes:
            return self._robot_position + direction not in self._wall_positions

        # Check if there is space to push the boxes
        last_box_position = boxes[-1] + direction
        return last_box_position not in self._wall_positions

    def _push_boxes(self, boxes_pushed, direction):
        # Reverse the order to prevent boxes from temporarily overlapping when moved.
        # This ensures each box moves to its new position without conflicting with others in the set.
        for box in boxes_pushed[::-1]:
            self._box_positions.remove(box)
            new_pos = box + direction
            self._box_positions.add(new_pos)

    def _get_direction(self, move):
        if move == ">":
            return self.RIGHT
        elif move == "<":
            return self.LEFT
        elif move == "^":
            return self.UP
        elif move == "v":
            return self.DOWN


class WideWareHouseRobot(WarehouseRobot):
    def __init__(self, grid, moves):
        # Expand the grid to make it twice as wide
        expanded_grid = self._expand_grid(grid)
        super().__init__(expanded_grid, moves)

    @staticmethod
    def _expand_grid(grid):
        # Expand the grid by doubling the width and modifying the characters as required
        height, width = len(grid), len(grid[0])
        new_grid = []

        for y in range(height):
            new_row = []
            for x in range(width):
                cell = grid[y][x]
                if cell == "#":
                    new_row.append("##")
                elif cell == "O":
                    new_row.append("[]")
                elif cell == ".":
                    new_row.append("..")
                elif cell == "@":
                    new_row.append("@.")
            new_grid.append("".join(new_row))

        return new_grid

    def identify_pushed_boxes(self, direction):
        boxes_to_process_queue = deque()

        for offset in [
            0,
            1,
        ]:  # 0 for the left side of the box, 1 for the right side of the box
            potential_pushed_box_position = (
                self._robot_position + direction - Vector(offset, 0)
            )
            if potential_pushed_box_position in self._box_positions:
                boxes_to_process_queue.append(potential_pushed_box_position)

        boxes_pushed = []
        while boxes_to_process_queue:
            box_to_process = boxes_to_process_queue.popleft()
            if box_to_process in boxes_pushed:
                continue

            boxes_pushed.append(box_to_process)
            neighbor_boxes = self._get_neighbor_boxes(box_to_process, direction)
            boxes_to_process_queue.extend(neighbor_boxes)

        return boxes_pushed

    def _can_push_boxes(self, boxes, direction):
        if not boxes:
            return self._robot_position + direction not in self._wall_positions

        return all(self._can_push_box(box, direction) for box in boxes)

    def _get_neighbor_boxes(self, box_to_process, direction):
        potential_neighbor_box_positions = [
            box_to_process + direction,
            box_to_process + direction + Vector(-1, 0),
            box_to_process + direction + Vector(1, 0),
        ]

        actual_neighbor_boxes = [
            box
            for box in potential_neighbor_box_positions
            if box in self._box_positions
        ]
        return actual_neighbor_boxes

    def _can_push_box(self, box, direction):
        return all(
            (box + direction + offset) not in self._wall_positions
            for offset in [Vector(0, 0), Vector(1, 0)]
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
            """
    ).strip()

    def test_part_one(self):
        expected_output = 10092
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 9021
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
