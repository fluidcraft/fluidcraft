#pragma once

#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>
#include <zmq.hpp>

namespace mcpp {
const int segment_bits = 0x7f;
const int continue_bit = 0x80;

auto inline read_varint(std::function<uint8_t()> read_byte) -> int {
    int value = 0;
		int position = 0;

		while (true) {
			const auto current_byte = read_byte();
			value |= (current_byte & segment_bits) << position;

			if ((current_byte & continue_bit) == 0) break;

			position += 7;

			if (position >= 32) throw new std::runtime_error("varint is too large");
    }

    return value;
}


auto inline write_varint(std::function<void(uint8_t)> write_byte, int value) {
	while (true) {
		if ((value & ~segment_bits) == 0) {
			write_byte(value);
			return;
		}

		write_byte((value & segment_bits) | continue_bit);

		value >>=7;
	}
}
};
