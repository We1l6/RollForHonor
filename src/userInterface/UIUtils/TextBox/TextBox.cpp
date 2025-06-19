#include "TextBox.h"

TextBox::TextBox(const std::string text)
	: TextBox(
		text, 
		RectanglePro(
			
		),
		UISkin(

		))
{
}

TextBox::TextBox(const std::string text, const RectanglePro& rect, const UISkin& skin)
	: m_textBoxButton(rect,skin,TextPro(""))
{
	
	m_maxWidth = rect.width;
	m_fontSize = DEFAULT_FONT_SIZE;
	m_font = GetFontDefault();
	m_lineSpacing = DEFAULT_LINE_SPACING;
	m_charSpacing = DEFAULT_CHAR_SPACING;
	m_position = { rect.x, rect.y };
	m_timer = DEFAULT_TIMER;
	m_visibleChars = DEFAULT_VISIBLE_CHARS;
	m_charDelay = DEFAULT_CHARS_DELAY;
	m_textColor = DEFAULT_TEXT_COLOR;
	wrapTextToLines(text);

	m_textBoxButton.setOnClickFinished([this]() { skipAnimation(); });
	if (skin.getTexture().id == 0)
	{
		m_holdColor = skin.getColor();
		m_holdColor.a -= 10.0f;
		m_textBoxButton.setOnHold([this]() {
			m_textBoxButton.setColor(m_holdColor);
			});
	}
	else
	{
		m_textBoxButton.setOnHold(nullptr);
	}
	m_textBoxButton.setHoverColor(skin.getColor());
	m_textBoxButton.setBaseColor(skin.getColor());
}

void TextBox::wrapTextToLines(std::string text)
{
	std::istringstream iss(text);
	std::vector<std::string> words;
	std::string word;

	while (iss >> word) {
		words.push_back(word);
	}

	std::string currentLine;

	for (size_t i = 0; i < words.size(); ++i) {
		std::string testLine = currentLine.empty() ? words[i] : currentLine + " " + words[i];
		int testWidth = MeasureText(testLine.c_str(), m_fontSize);

		if (testWidth > m_maxWidth) {
			if (!currentLine.empty()) {
				m_lines.push_back(currentLine);
			}
			currentLine = words[i];
		}
		else {
			currentLine = testLine;
		}
	}

	if (!currentLine.empty()) {
		m_lines.push_back(currentLine);
	}
}

int TextBox::getTotalCharCount() const
{
	int count = 0;
	for (const std::string& line : m_lines)
		for(int i = 0; i < line.length(); i++)
			count += static_cast<int>(line.size());
	return count;
}

void TextBox::skipAnimation()
{
	m_visibleChars = getTotalCharCount();
	m_timer = 0.0f;
}

void TextBox::Draw()
{
	m_textBoxButton.Draw();
	int currentY = m_position.y;
	for (const auto& line : m_lines)
	{
		DrawText(line.c_str(), m_position.x, currentY, m_fontSize, m_textColor);
		currentY += m_lineSpacing;
	}
}

void TextBox::Update()
{
	m_textBoxButton.Update();
}

void TextBox::DrawAnimated()
{
	m_textBoxButton.Draw();
	m_timer += GetFrameTime();

	if (m_visibleChars < getTotalCharCount())
	{
		if (m_timer >= m_charDelay)
		{
			m_visibleChars++;
			m_timer = 0.0f;
		}
	}

	int drawnChars = 0;
	float xStart = m_position.x;
	float y = m_position.y;

	for (const std::string& line : m_lines)
	{
		float x = xStart;

		for (int i = 0; i < (int)line.size(); ++i)
		{
			if (drawnChars >= m_visibleChars)
				break;

			char c = line[i];
			char str[2] = { c, '\0' };

			DrawTextEx(m_font, str, { x, y }, m_fontSize, m_spacing, m_textColor);

			Vector2 size = MeasureTextEx(m_font, str, m_fontSize, m_spacing);
			x += size.x + m_charSpacing;

			drawnChars++;
		}

		y += m_lineSpacing;
		if (drawnChars >= m_visibleChars)
			break;
	}
}
