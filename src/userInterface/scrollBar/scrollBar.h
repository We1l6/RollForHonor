#pragma once

#include "../button/button.h"

class ScrollBar : public UserInterface
{
public:
	ScrollBar(const RectanglePro& rect);
	ScrollBar(const RectanglePro& rect, const TextPro& text);
	ScrollBar(const RectanglePro& rect, const TextPro& text, float rangeMin, float rangeMax, bool horizontal);

	// Getters
	[[nodiscard]] float getRangeMin() const { return m_rangeMin; }
	[[nodiscard]] float getRangeMax() const { return m_rangeMax; }
	[[nodiscard]] float getValue() const { return m_value; }
	[[nodiscard]] float getStep() const { return m_step; }
	[[nodiscard]] float getNormalizedValue() const;
	// Setters
	void setRangeMin(float rangeMin) { m_rangeMin = rangeMin; }
	void setRangeMax(float rangeMax) { m_rangeMax = rangeMax; }
	void setStep(float step) { m_step = step; }
	void setValue(float value);
	void setNormalizedValue(float normalized);
	void setColor(Color color) { m_barRect.setColor(color); }
	void setThumbColor(Color color) { m_thumbButton.setBaseColor(color); }
	void setThumbHoverColor(Color color) { m_thumbButton.setHoverColor(color); }	

	void Update() override;
	void Draw() override;
private:
	RectanglePro m_barRect;
	Button m_thumbButton;
	TextPro m_text;

	float m_rangeMin;
	float m_rangeMax;
	float m_value;
	float m_step;
	float m_thumbPosition;
	float m_thumbSize;
	bool m_horizontal;

	void updateThumbPosition();
	void updateValueFromThumbPosition();
	void updatePositionFromValue();

	static constexpr float DEFAULT_RANGE_MIN = 0.0f;
	static constexpr float DEFAULT_RANGE_MAX = 100.0f;
	static constexpr float DEFAULT_STEP = 1.0f;
	static constexpr float DEFAULT_THUMB_SIZE = 20.0f;
	static constexpr Color THUMB_COLOR = { 0, 0, 0 };
};
