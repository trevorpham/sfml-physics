#pragma once

namespace app::config {
	inline constexpr int kDisplayRate = 144;
	inline constexpr unsigned int kHDisplaySize = 800;
	inline constexpr unsigned int kVDisplaySize = 600;
	inline constexpr float kFixedTimeStep = 1.f / 144.f;
	inline constexpr float kMaxFrameTime = 0.25f;
}
