import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    compactor = DiskCompactor(puzzle_input)
    compactor.compact()
    return compactor.get_checksum()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class DiskCompactor:
    def __init__(self, disk_map: str):
        self.disk_map = disk_map
        self.file_sizes, self.space_sizes = self._parse_disk_map()

        # List to store (file_id, file_size) tuples
        self.new_disk_layout = []

    def compact(self):
        self.new_disk_layout.clear()

        # Start by placing the first file
        self.new_disk_layout.append((0, self.file_sizes[0]))

        file_to_move_index = len(self.file_sizes) - 1
        remaining_file_size = self.file_sizes[file_to_move_index]
        space_index = 0
        remaining_space_size = self.space_sizes[space_index]
        while space_index < file_to_move_index - 1:
            if remaining_space_size == 0:
                # Write file that was originally after this space
                file_after_space_index = space_index + 1
                self.new_disk_layout.append((file_after_space_index, self.file_sizes[file_after_space_index]))

                # Move onto next space
                space_index += 1
                remaining_space_size = self.space_sizes[space_index]

            # Write the file chunk to the current space
            write_size = min(remaining_file_size, remaining_space_size)
            self.new_disk_layout.append((file_to_move_index, write_size))
            remaining_file_size -= write_size
            remaining_space_size -= write_size

            if remaining_file_size == 0:
                # Move onto previous file (we process the files backwards)
                file_to_move_index -= 1
                remaining_file_size = self.file_sizes[file_to_move_index]

        # Write final chunk of last file
        self.new_disk_layout.append((file_to_move_index, remaining_file_size))

    def get_checksum(self):
        expanded_layout = []

        # Expand the new disk layout to get actual blocks
        for file_id, file_size in self.new_disk_layout:
            expanded_layout.extend([file_id] * file_size)

        # Calculate checksum by summing the position * file_id for each block
        checksum = sum(position * file_id for position, file_id in enumerate(expanded_layout))
        return checksum

    def _parse_disk_map(self):
        file_sizes = []
        space_sizes = []

        for i in range(len(self.disk_map)):
            if i % 2 == 0:  # Even indices (0, 2, 4, ...) are file sizes
                file_sizes.append(int(self.disk_map[i]))
            else:  # Odd indices (1, 3, 5, ...) are space sizes
                space_sizes.append(int(self.disk_map[i]))

        return file_sizes, space_sizes


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
            2333133121414131402
        """).strip()
        expected_output = 1928
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
