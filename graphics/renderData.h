#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

//anything we want to run through the graphics thingy
struct RenderData {
//public:
//
//	RenderData() = delete;
//	~RenderData() = default;
//	RenderData(const RenderData&) = delete;
//	RenderData& operator=(const RenderData&) = delete;
//	RenderData(RenderData&&) = delete;
//	RenderData& operator=(RenderData&&) = delete;
//
//	RenderData()
//
//private:
	//these both need to be sent to gl every frame
	glm::mat4 matrix{};
	std::vector<float> vertices; //dim3 - TODO tidy this up!!!
	std::vector<float> uvCoords; //dim2
	std::vector<unsigned> indices; //TRIANGLE INDICES from vertices
	unsigned count{0}; //todo remove this, we have vertices.size()
	GLuint texture;
};

struct Renderables {
private:
	unsigned nextId{ 0 };
	std::map<unsigned, std::shared_ptr<RenderData>> entries;

	auto findEntry(const unsigned id) {
		auto entry{ entries.find(id) };
		if (entry == entries.end()) {
			const auto message{ "Attempt made to find non-existent renderable ID=" + id };
			throw std::exception(message);
		}
		return entry;
	}

public:

	[[nodiscard]]
	unsigned addRenderable(RenderData data) {
		const auto id{ nextId++ };
		entries[id] = std::make_shared<RenderData>(data);
		return id;
	}

	void deleteRenderable(const unsigned id) {
		entries.erase(findEntry(id)); //shared ptr should protect us if the data is still being used
	}

	auto getAllRenderData() const {
		std::vector<std::shared_ptr<RenderData>> retval;
		for (const auto& entry : entries) {
			retval.push_back(entry.second);
		}
		return retval;
	}

	auto& getRenderData(const unsigned id) {
		return findEntry(id)->second;
	}

};