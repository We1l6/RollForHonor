/**
 * @file checkBox.h
 * @brief CheckBox UI element for toggling state
 * @details
 * Defines a customizable CheckBox component composed of a background and an internal check button.
 * Inherits from UserInterface and internally uses a Button to handle user interaction.
 *
 * @author koliruslik
 * @date 17/06/2025
 */

#pragma once

#include "../button/button.h"


 /**
  * @note
  * The CheckBox toggles its state (`checked` or `unchecked`) when clicked.
  * The visual appearance (color or texture) updates accordingly via the `UpdateVisual()` method.
  *
  * A callback can be set using `setOnCheck()` to respond to the user toggling the checkbox.
  * The appearance of the check indicator can be customized via `setOnCheckEffect()`
  * using either a color or texture.
  *
  * Make sure to call `Update()` each frame to handle interaction logic,
  * and `Draw()` to render the checkbox and its components.
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
  */

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