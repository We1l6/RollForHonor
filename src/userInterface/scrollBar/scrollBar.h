/**
 * @file ScrollBar.h
 * @brief Scroll bar UI element class
 * @details
 * Implements a scroll bar with a draggable thumb to select a value within a defined range.
 * Supports horizontal and vertical orientations.
 * Value is clamped between rangeMin and rangeMax, with optional step increments.
 * Thumb colors can be customized.
 * Update() must be called each frame to process input and update state.
 * Draw() renders the scroll bar and its thumb.
 *
 * @author koliruslik
 * @date 16/06/2025
 */

#pragma once


#include "../button/button.h"

/**
 * @note
 * When setting the value or normalized value, the value is clamped within the range [rangeMin, rangeMax].
 * The thumb color and hover color can be customized via the corresponding setters.
 * Make sure to call Update() each frame to handle user input and update the scroll bar state,
 * and call Draw() to render the scroll bar and thumb.
 *
 * Be aware that if the step value does not evenly divide the range,
 * it may cause issues with precisely reaching the rangeMin or rangeMax values.
 *
 * @example
 * ScrollBar scrollBar(
 *     RectanglePro{10, 10, 200, 20},  // bar rectangle
 *     RectanglePro{0, 0, 20, 20},     // thumb rectangle
 *     barSkin,                       // UISkin for bar
 *     thumbSkin,                     // UISkin for thumb
 *     0.0f,                         // rangeMin
 *     100.0f,                       // rangeMax
 *     true                          // horizontal
 * );
 *
 * while (!WindowShouldClose())
 * {
 *     scrollBar.Update();
 *     scrollBar.Draw();
 *     float value = scrollBar.getValue();
 *     // Use the scroll bar value for something...
 * }
 */

class ScrollBar : public UserInterface
{
public:
	ScrollBar(const RectanglePro& barRect, const UISkin& barSkin);
	ScrollBar(const RectanglePro& barRect, const RectanglePro& thumbRect, const UISkin& barSkin, const UISkin& thumbSkin);
	ScrollBar(const RectanglePro& barRect, const RectanglePro& thumbRect, const UISkin& barSkin, const UISkin& thumbSkin, float rangeMin, float rangeMax, bool horizontal);

	//Getters
	[[nodiscard]] float getRangeMin() const { return m_rangeMin; }
	[[nodiscard]] float getRangeMax() const { return m_rangeMax; }
	[[nodiscard]] float getValue() const { return m_value; }
	[[nodiscard]] float getStep() const { return m_step; }
	[[nodiscard]] float getNormalizedValue() const;
	
	//Setters
	void setRangeMin(float rangeMin) { m_rangeMin = rangeMin; }
	void setRangeMax(float rangeMax) { m_rangeMax = rangeMax; }
	void setStep(float step) { m_step = step; }
	void setValue(float value);
	void setNormalizedValue(float normalized);
	void setThumbColor(Color color) { m_thumbButton.setBaseColor(color); }
	void setThumbHoverColor(Color color) { m_thumbButton.setHoverColor(color); }	

	void Update() override;
	void Draw() override;
private:
	Button m_thumbButton;
	UISkin m_thumbSkin;
	float m_rangeMin;
	float m_rangeMax;
	float m_value;
	float m_step;
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
