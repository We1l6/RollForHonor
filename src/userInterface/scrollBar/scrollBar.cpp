#include "scrollBar.h"

ScrollBar::ScrollBar(
	const RectanglePro& barRect,
	const UISkin& barSkin
)
	: ScrollBar(
		barRect,
		RectanglePro{
			{ barRect.getPosition().x - barRect.getSize().x / 2.0f + DEFAULT_THUMB_SIZE / 2.0f,
			  barRect.getPosition().y },
			{ DEFAULT_THUMB_SIZE, barRect.getSize().y },
			0.0f,
			barRect.getCornerRadius()
		},
		barSkin,
		barSkin,
		DEFAULT_RANGE_MIN,
		DEFAULT_RANGE_MAX,
		true
	)
{
}

ScrollBar::ScrollBar(
	const RectanglePro& barRect, 
	const RectanglePro& thumbRect,
	const UISkin& barSkin,
	const UISkin& thumbSkin)
	: ScrollBar(barRect, thumbRect, barSkin, thumbSkin, DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX, true)
{
}
ScrollBar::ScrollBar(
	const RectanglePro& barRect,
	const RectanglePro& thumbRect,
	const UISkin& barSkin,
	const UISkin& thumbSkin,
	float rangeMin,
	float rangeMax,
	bool horizontal)
	: UserInterface(barRect, barSkin),
	m_thumbSkin(thumbSkin),
	m_horizontal(horizontal),
	m_rangeMin(rangeMin),
	m_rangeMax(rangeMax),
	m_value(rangeMin),
	m_step(DEFAULT_STEP)
{
	//RectanglePro thumbRect;

	/*if (horizontal) {
		thumbRect = RectanglePro{
			{rect.getPosition().x - rect.getSize().x / 2.0f + DEFAULT_THUMB_SIZE / 2.0f, rect.getPosition().y},
			{DEFAULT_THUMB_SIZE, rect.getSize().y},
			0.0f,
			rect.getCornerRadius()
		};
	}
	else {
		thumbRect = RectanglePro{
			{rect.getPosition().x, rect.getPosition().y - rect.getSize().y / 2.0f + DEFAULT_THUMB_SIZE / 2.0f},
			{rect.getSize().x, DEFAULT_THUMB_SIZE},
			0.0f,
			rect.getCornerRadius()
		};

	}*/

	m_thumbButton = Button(
		thumbRect,
		thumbSkin,
		TextPro(""),
		[this]() { updateThumbPosition(); }, // onHold callback
		nullptr
	);

	m_text.setColor(BLACK);
	//m_thumbButton.setColor(THUMB_COLOR);

	updatePositionFromValue();
	updateValueFromThumbPosition();
}

void ScrollBar::Update()
{
	m_thumbButton.Update();

	Vector2 thumbPos = m_thumbButton.getPosition();
	Vector2 thumbSize = m_thumbButton.getSize();

	m_text.setPosition({
		thumbPos.x + thumbSize.x / 2.0f,
		thumbPos.y - 20.0f
		});

	m_text.setText(std::to_string(static_cast<int>(m_value)));

	Draw();
}

void ScrollBar::Draw()
{	
	m_skin.Draw(m_rect); 
	m_thumbButton.Draw();
	m_text.Draw();
}

void ScrollBar::updateThumbPosition()
{
	Vector2 mousePos = GetMousePosition();
	Vector2 barCenter = m_rect.getPosition();
	Vector2 barSize = m_rect.getSize();
	Vector2 thumbSize = m_thumbButton.getSize();

	Vector2 barPos = {
		barCenter.x - barSize.x / 2.0f,
		barCenter.y - barSize.y / 2.0f
	};

	float start, end, rangeLength, mouseCoord;

	if (m_horizontal) {
		start = barPos.x + (thumbSize.x / 2.0f);
		end = barPos.x + barSize.x - (thumbSize.x / 2.0f);
		rangeLength = end - start;

		mouseCoord = std::clamp(mousePos.x, start, end);

		float normalized = (mouseCoord - start) / rangeLength;
		float value = m_rangeMin + normalized * (m_rangeMax - m_rangeMin);

		value = std::round(value / m_step) * m_step;

		if (value < m_rangeMin) value = m_rangeMin;
		if (value > m_rangeMax) value = m_rangeMax;

		m_value = value;
		normalized = (m_value - m_rangeMin) / (m_rangeMax - m_rangeMin);

		float newX = start + normalized * rangeLength;

		m_thumbButton.setPosition({ newX, barCenter.y });
	}
	else {
		start = barPos.y + (thumbSize.y / 2.0f);
		end = barPos.y + barSize.y - (thumbSize.y / 2.0f);
		rangeLength = end - start;

		mouseCoord = std::clamp(mousePos.y, start, end);

		float normalized = 1.0f - (mouseCoord - start) / rangeLength;
		float value = m_rangeMin + normalized * (m_rangeMax - m_rangeMin);

		value = std::round(value / m_step) * m_step;

		if (value < m_rangeMin) value = m_rangeMin;
		if (value > m_rangeMax) value = m_rangeMax;

		m_value = value;
		normalized = (m_value - m_rangeMin) / (m_rangeMax - m_rangeMin);

		float newY = start + (1.0f - normalized) * rangeLength;

		m_thumbButton.setPosition({ barCenter.x, newY });
	}
}



void ScrollBar::updateValueFromThumbPosition()
{
	Vector2 barCenter = m_rect.getPosition();
	Vector2 barSize = m_rect.getSize();
	Vector2 thumbSize = m_thumbButton.getSize();
	float thumbPos = m_horizontal ? m_thumbButton.getPosition().x : m_thumbButton.getPosition().y;

	float barStart = m_horizontal
		? (barCenter.x - barSize.x / 2.0f + thumbSize.x / 2.0f)
		: (barCenter.y - barSize.y / 2.0f + thumbSize.y / 2.0f);

	float barEnd = m_horizontal
		? (barCenter.x + barSize.x / 2.0f - thumbSize.x / 2.0f)
		: (barCenter.y + barSize.y / 2.0f - thumbSize.y / 2.0f);

	float normalizedPosition = (thumbPos - barStart) / (barEnd - barStart);

	//Inverting the normalized position for vertical scrollbars
	if (!m_horizontal)
		normalizedPosition = 1.0f - normalizedPosition;  

	m_value = m_rangeMin + normalizedPosition * (m_rangeMax - m_rangeMin);
}

void ScrollBar::updatePositionFromValue()
{
	float normalizedValue = (m_value - m_rangeMin) / (m_rangeMax - m_rangeMin);
	Vector2 barCenter = m_rect.getPosition();
	Vector2 barSize = m_rect.getSize();
	Vector2 thumbSize = m_thumbButton.getSize();

	if (m_horizontal) {
		float thumbX = barCenter.x - barSize.x / 2.0f + thumbSize.x / 2.0f + normalizedValue * (barSize.x - thumbSize.x);
		m_thumbButton.setPosition({ thumbX, barCenter.y });
	}
	else {
		float thumbY = barCenter.y - barSize.y / 2.0f + thumbSize.y / 2.0f + normalizedValue * (barSize.y - thumbSize.y);
		m_thumbButton.setPosition({ barCenter.x, thumbY });
	}
}

float ScrollBar::getNormalizedValue() const {
	return (m_value - m_rangeMin) / (m_rangeMax - m_rangeMin);
}

void ScrollBar::setValue(float value) {
	if (value < m_rangeMin) value = m_rangeMin;
	if (value > m_rangeMax) value = m_rangeMax;

	float stepsCount = std::round((value - m_rangeMin) / m_step);
	m_value = m_rangeMin + stepsCount * m_step;

	updatePositionFromValue();
}

void ScrollBar::setNormalizedValue(float normalized) {
	if (normalized < 0.f) normalized = 0.f;
	if (normalized > 1.f) normalized = 1.f;

	float value = m_rangeMin + normalized * (m_rangeMax - m_rangeMin);

	setValue(value);
}

