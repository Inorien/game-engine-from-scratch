#pragma once

//interface class for controllable things (camera, icons, whatever)
//this class should probably be called TimeSensitive or something
struct KeyboardControllable {
	//virtual ~KeyboardControllable() = default;

	explicit KeyboardControllable(float& dt) :
		delta(dt)
	{}

protected:
	float& delta;
};