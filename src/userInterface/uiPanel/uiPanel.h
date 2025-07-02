/**
 * @file UIPanel.h
 * @brief UI panel container class.
 *
 * Implements a UI panel that can contain multiple UI elements.
 * Supports adding child elements with positions relative to the panel's top-left corner.
 * Handles updating and drawing of all contained elements.
 * The panel itself can be shown or hidden via visibility control.
 *
 * @note
 * The panel manages its child elements via shared pointers.
 * Coordinates of child elements are specified relative to the panel.
 * Call Update() each frame to update all child elements.
 * Call Draw() each frame to render the panel and all child elements.
 *
 * @example
 * UIPanel panel(RectanglePro({100, 100}, {300, 200}, 0, 10), skin);
 * auto button = std::make_shared<Button>(/* parameters * /);
 * panel.AddElement(button, Vector2{50, 50});
 *
 * while (!WindowShouldClose())
 * {
 *     panel.Update();
 *     panel.Draw();
 * }
 *
 * @author koliruslik
 * @date 02/07/2025
 */

#pragma once

#include "../userInterface.h"
#include "raymath.h"

class UIPanel : public UserInterface
{
public:
	UIPanel(const RectanglePro& rect, const UISkin& skin);
	virtual ~UIPanel() = default;

	Vector2 getLocalCenter();
	UISkin getSkin() const { return m_skin; }

	void setVisible(bool visible) { m_visible = visible; }

	void Draw() override;
	void Update() override;
	
	void AddElement(std::shared_ptr<UserInterface> element, Vector2 localPosition);

private:
	bool m_visible;
	std::vector<std::shared_ptr<UserInterface>> m_elements;
};
