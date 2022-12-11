#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <thread>
#include <vector>
#include <bit>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "varint.hpp"

auto main() -> int {
	using boost::asio::ip::tcp;

	spdlog::set_level(spdlog::level::debug);

	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v6(), 25565));
	acceptor.listen();

	spdlog::info("Listening on :{}", acceptor.local_endpoint().port());

	tcp::socket client_socket(io_service);

  // Connect client and server sockets.
	acceptor.async_accept(client_socket, [&](boost::system::error_code ec){
		auto read = [&client_socket](){
			std::array<uint8_t, 1> read_buffer;
		  auto n = boost::asio::read(
				client_socket,
				boost::asio::buffer(read_buffer),
				boost::asio::transfer_exactly(1)
			);
			if (n <= 0)
				throw std::runtime_error("Failed to read data");

			return read_buffer[0];
		};

		// TODO: move to separate file?
		auto read_packet = [&read]() {
			auto packet_length = mcpp::read_varint(read); 
			auto packet_id = mcpp::read_varint(read); 
			
			spdlog::debug(
				"Received packet with id {0:x} and length {1}",
				packet_id,
				packet_length
			);

			return packet_id;
		};

		try {
			auto packet_id = read_packet();	

			if (packet_id == 0x00) {
				// Handshake
				auto protocol_version = mcpp::read_varint(read);

				spdlog::debug(
					"Received handshake with protocol version {0:}",
					protocol_version
				);
			}
		} catch(const std::runtime_error& err) {
			spdlog::error(err.what());	
		}
	});

  io_service.run();

	return 0;
}
