import textwrap
import unittest
from pygame.math import Vector2
from collections import deque

REAL_INPUT_REQUIRED_IMPROVEMENT_VIA_CHEATING = 100
ALLOWED_CHEAT_LENGTH_PART_ONE = 2
ALLOWED_CHEAT_LENGTH_PART_TWO = 20


class HashableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableVector):
            return self.x == other.x and self.y == other.y
        return False


Vector = HashableVector


def solve_part_one(
        puzzle_input,
        required_improvement_via_cheating=REAL_INPUT_REQUIRED_IMPROVEMENT_VIA_CHEATING,
):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = puzzle_input.splitlines()
    race_track = RaceTrack(
        grid, required_improvement_via_cheating, ALLOWED_CHEAT_LENGTH_PART_ONE
    )
    return race_track.calculate_num_total_valid_cheats()


def solve_part_two(
        puzzle_input,
        required_improvement_via_cheating=REAL_INPUT_REQUIRED_IMPROVEMENT_VIA_CHEATING,
):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = puzzle_input.splitlines()
    race_track = RaceTrack(
        grid, required_improvement_via_cheating, ALLOWED_CHEAT_LENGTH_PART_TWO
    )
    return race_track.calculate_num_total_valid_cheats()


class RaceTrack:
    DIRECTIONS = [Vector(0, -1), Vector(0, 1), Vector(-1, 0), Vector(1, 0)]

    def __init__(self, grid, required_improvement_via_cheating, allowed_cheat_length):
        self._grid = grid
        self._required_improvement_via_cheating = required_improvement_via_cheating
        self._allowed_cheat_length = allowed_cheat_length
        self._start_position = self._find_position("S")
        self._end_position = self._find_position("E")
        self._distances_from_start = self._get_distances_from_position(
            self._start_position
        )
        self._distances_from_end = self._get_distances_from_position(self._end_position)
        self._min_distance_without_cheating = self._distances_from_start[
            self._end_position
        ]

    def calculate_num_total_valid_cheats(self):
        # Prefilter valid cheat start position to those that are within min_distance_without_cheating
        cheat_start_positions = [
            cheat_start_position
            for cheat_start_position, distance_from_start in self._distances_from_start.items()
            if distance_from_start < self._min_distance_without_cheating
        ]

        return sum(
            self._count_num_valid_cheats_from_position(cheat_start_position)
            for cheat_start_position in cheat_start_positions
        )

    def _find_position(self, char):
        for y, row in enumerate(self._grid):
            for x, cell in enumerate(row):
                if cell == char:
                    return Vector(x, y)

    def _is_valid_position(self, position):
        x, y = int(position.x), int(position.y)
        return (
                0 <= x < len(self._grid[0])
                and 0 <= y < len(self._grid)
                and self._grid[y][x] != "#"
        )

    def _get_distances_from_position(self, start_position):
        queue = deque([(start_position, 0)])  # (position, time_taken)
        position_to_distance = {start_position: 0}

        while queue:
            current_position, time_taken = queue.popleft()

            valid_neighbor_positions = [
                current_position + direction
                for direction in self.DIRECTIONS
                if self._is_valid_position(current_position + direction)
                and (current_position + direction) not in position_to_distance
            ]

            for neighbor_position in valid_neighbor_positions:
                position_to_distance[neighbor_position] = time_taken + 1
                queue.append((neighbor_position, time_taken + 1))

        return position_to_distance

    def _count_num_valid_cheats_from_position(self, cheat_start_position):
        return sum(
            1
            for cheat_end_position in self._get_valid_cheat_end_positions(
                cheat_start_position
            )
            if self._is_cheat_saving_enough_time(
                cheat_start_position, cheat_end_position
            )
        )

    def _get_valid_cheat_end_positions(self, cheat_start_position):
        return [
            Vector(cheat_start_position.x + dx, cheat_start_position.y + dy)
            for dx, dy in self._get_cheat_offsets()
            if self._is_valid_position(
                Vector(cheat_start_position.x + dx, cheat_start_position.y + dy)
            )
        ]

    def _get_cheat_offsets(self):
        return [
            (dx, dy)
            for dx in range(-self._allowed_cheat_length, self._allowed_cheat_length + 1)
            for dy in range(-self._allowed_cheat_length, self._allowed_cheat_length + 1)
            if abs(dx) + abs(dy) <= self._allowed_cheat_length
        ]

    def _is_cheat_saving_enough_time(self, cheat_start_position, cheat_end_position):
        distance_after_cheating = self._calculate_distance_after_cheating(
            cheat_start_position, cheat_end_position
        )
        improvement = self._min_distance_without_cheating - distance_after_cheating
        return improvement >= self._required_improvement_via_cheating

    def _calculate_distance_after_cheating(
            self, cheat_start_position, cheat_end_position
    ):
        cheat_distance = abs(cheat_end_position.x - cheat_start_position.x) + abs(
            cheat_end_position.y - cheat_start_position.y
        )
        return (
                self._distances_from_start[cheat_start_position]
                + cheat_distance
                + self._distances_from_end[cheat_end_position]
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
        ###############
        #...#...#.....#
        #.#.#.#.#.###.#
        #S#...#.#.#...#
        #######.#.#.###
        #######.#.#...#
        #######.#.###.#
        ###..E#...#...#
        ###.#######.###
        #...###...#...#
        #.#####.#.###.#
        #.#...#.#.#...#
        #.#.#.#.#.#.###
        #...#...#...###
        ###############
        """
    ).strip()

    def test_part_one(self):
        expected_output = 44
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT, 2))

    def test_part_two(self):
        expected_output = 285
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT, 50))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
