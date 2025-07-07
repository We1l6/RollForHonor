#include "checkBox.h"

CheckBox::CheckBox(const RectanglePro& rect, const UISkin& boxSkin)
	: CheckBox(rect, boxSkin, UISkin(DEFAULT_CHECK_BUTTON_SKIN))
{
}
CheckBox::CheckBox(const RectanglePro& rect,const UISkin& boxSkin, const UISkin& checkButtonSkin) 
	: UserInterface(rect, boxSkin), m_checked(false)
{
	m_checkButton = Button(
		RectanglePro(
			rect.getPosition(),
			DEFAULT_CHECK_BUTTON_SIZE,
			0.0f,
			0.0f
		),
		UISkin(checkButtonSkin),
		TextPro(),
		nullptr,
		[this]() { UpdateCheck(); });
}

void CheckBox::UpdateCheck()
{
	m_checked = !m_checked;	
}

void CheckBox::UpdateVisual()
{
	if (m_onCheckEffect.getTexture().id == 0)
	{
		m_checkButton.setColor(
			m_checked ?
			m_onCheckEffect.getColor()
			: m_checkButton.getBaseColor()
		);
	}
	else
	{
		m_checkButton.setTexture(
			m_checked ?
			m_onCheckEffect.getTexture()
			: m_checkButton.getBaseTexture()
		);
	}
	

}

void CheckBox::Draw()
{
	if (m_visible)
	{
		m_skin.Draw(m_rect);
		m_checkButton.Draw();
	}
}

void CheckBox::Update()
{
	m_checkButton.Update();
	UpdateVisual();
}

