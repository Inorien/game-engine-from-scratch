#pragma once
#include <functional>
#include <map>

//this becomes the glfw window user pointer
//callbacks are set here

class CallbackControl {
public:

	void registerKeyCallback(int key, const std::function<void()>& func) {
		callbacks.insert({ key, {func, false} });
	}

	void enableCallback(int key) {
		auto func{ callbacks.find(key) };
		if (func == callbacks.end()) {
			return;
		}
		func->second.isEnabled = true;
	}

	void disableCallback(int key) {
		auto func{ callbacks.find(key) };
		if (func == callbacks.end()) {
			return;
		}
		func->second.isEnabled = false;
	}

	void update() const {
		for (const auto& callback : callbacks) {
			const auto& callable{ callback.second };
			if (callable.isEnabled) {
				callable.function();
			}
		}
	}

private:
	struct Callable {
		std::function<void()> function;
		bool isEnabled;
	};

	std::map<int, Callable> callbacks;

};