/**
 * @file CheckBox.h
 * @brief CheckBox UI element for toggling state.
 *
 * Defines a customizable CheckBox component composed of a background and an internal check button.
 * Inherits from UserInterface and internally uses a Button to handle user interaction and callbacks.
 * Allows full visual customization using `UISkin` for both the box and the check effect.
 *
 * The CheckBox toggles its state (`checked` or `unchecked`) when clicked, and you can assign
 * a callback using `setOnCheck()` to respond to state changes. Visual appearance is updated
 * automatically via the `UpdateVisual()` method.
 *
 * @note
 * - Call `Update()` each frame to process user interaction.
 * - Call `Draw()` each frame to render the checkbox and its components.
 * - Use `setOnCheckEffect()` to define the appearance of the check indicator.
 *
 * @example
 * CheckBox checkBox(
 *     RectanglePro{50, 50, 50, 50},
 *     boxSkin
 * );
 * checkBox.setOnCheck([]() {
 *     std::cout << "Checkbox clicked!" << std::endl;
 * });
 *
 * while (!WindowShouldClose())
 * {
 *     checkBox.Update();
 *     checkBox.Draw();
 *
 *     if (checkBox.getChecked())
 *     {
 *         // Do something when the checkbox is active
 *     }
 * }
 *
 * @author koliruslik
 * @date 17/06/2025
 */

#pragma once

#include "../button/button.h"

class CheckBox : UserInterface
{
public:
	CheckBox(const RectanglePro&, const UISkin& boxSkin);
	CheckBox(const RectanglePro&, const UISkin& boxSkin, const UISkin& checkButtonSkin);

	//Getters
	bool getChecked() const { return m_checked; }

	//Setters
	void setOnCheck(ButtonCallback onCheck) { m_checkButton.setOnClickFinished(onCheck); }
	void setOnHold(ButtonCallback onHold) { m_checkButton.setOnHold(onHold); }
	void setOnCheckEffect(const UISkin& effect) { m_onCheckEffect = effect; }

	void Draw() override;
	void Update() override;
private:
	Button m_checkButton;
	UISkin m_onCheckEffect;

	bool m_checked;

	void UpdateCheck();
	void UpdateVisual();

	static constexpr Vector2 DEFAULT_SIZE = { 50.0f, 50.0f };
	static constexpr Vector2 DEFAULT_CHECK_BUTTON_SIZE = { 45.0f, 45.0f };
	static constexpr Color DEFAULT_CHECK_BUTTON_SKIN = LIGHTGRAY;
	static constexpr Color DEFAULT_ON_CHECK_EFFECT = GREEN;
};