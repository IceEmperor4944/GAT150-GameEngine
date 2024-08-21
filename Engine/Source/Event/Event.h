#pragma once
#include <string>
#include <variant>

using id_t = std::string;

struct Event {
	using data_t = std::variant<int, bool, float, std::string>;

	Event(const id_t& id, data_t data) : id{ id }, data{ data } {}

	id_t id;
	data_t data;
};