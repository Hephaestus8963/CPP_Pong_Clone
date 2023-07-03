#include "User/Button.hpp"


Button::Button() {  }

Button::Button(
  const sf::Vector2f& Pos,
  const sf::Vector2f& Size,
  const sf::Color& ButtonBodyColor,
  const sf::Color& ButtonOutlineColor,
  float ButtonOutlineThickness,
  const std::string& ButtonText,
  int ButtonTextSize,
  const sf::Color& ButtonTextColor,
  const sf::Font* ButtonTextFont
) {
  SetButtonColor(ButtonBodyColor);
  SetButtonOutlineColor(ButtonBodyColor);
  SetButtonOutlineThickness(ButtonOutlineThickness);
  SetText(ButtonText);
  SetTextSize(ButtonTextSize);
  SetTextColor(ButtonTextColor);
  SetTextFont(ButtonTextFont);
  SetSize(Size);
  SetPosition(Pos);
  IsClicked = false;
}

void Button::SetPosition(const sf::Vector2f &pos){
  m_ButtonBody.setPosition(pos);

  float TxtPosX = (pos.x + m_ButtonBody.getLocalBounds().width / 2) - (m_ButtonText.getLocalBounds().width / 2);
  float TxtPosY = (pos.y + m_ButtonBody.getLocalBounds().height / 2) - (m_ButtonText.getLocalBounds().height / 2);

  m_ButtonText.setPosition(sf::Vector2f(TxtPosX, TxtPosY));
}

void Button::SetSize(const sf::Vector2f &size){
  m_ButtonBody.setSize(size);
}

void Button::SetButtonColor(const sf::Color &color){
  m_ButtonBody.setFillColor(color);
}

void Button::SetButtonOutlineColor(const sf::Color &color){
  m_ButtonBody.setOutlineColor(color);
}

void Button::SetButtonOutlineThickness(const float t){
  m_ButtonBody.setOutlineThickness(t);
}

void Button::SetText(const std::string &str){
  m_ButtonText.setString(str);
}

void Button::SetTextSize(const int s){
  m_ButtonText.setCharacterSize(s);
}

void Button::SetTextColor(const sf::Color &color){
  m_ButtonText.setFillColor(color);
}

void Button::SetTextFont(const sf::Font * font){
  m_ButtonText.setFont(*font);
}

const sf::Vector2f &Button::GetPosition() const{
  return m_ButtonBody.getPosition();
}

const sf::Vector2f &Button::GetSize() const{
  return m_ButtonBody.getSize();
}

const sf::Color &Button::GetButtonColor() const{
  return m_ButtonBody.getFillColor();
}

const sf::Color &Button::GetButtonOutlineColor() const{
  return m_ButtonBody.getOutlineColor();
}

const float Button::GetButtonOutlineThickness() const{
  return m_ButtonBody.getOutlineThickness();
}

const std::string &Button::GetText() const{
  return m_ButtonText.getString();
}

const int Button::GetTextSize() const{
  return m_ButtonText.getCharacterSize();
}

const sf::Color &Button::GetTextColor() const{
  return m_ButtonText.getFillColor();
}

const sf::Font *Button::GetTextFont() const{
  return m_ButtonText.getFont();
}


bool Button::MouseOver(sf::RenderWindow& window) const {
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float btnXpos = m_ButtonBody.getPosition().x;
  float btnYpos = m_ButtonBody.getPosition().y;

  float btnXposMax = btnXpos + m_ButtonBody.getLocalBounds().width;
  float btnYposMax = btnYpos + m_ButtonBody.getLocalBounds().height;

  if (mouseX > btnXpos && mouseX < btnXposMax && mouseY > btnYpos && mouseY < btnYposMax) return true;
  
  return false;
}

void Button::RenderTo(sf::RenderWindow& window) const{
  window.draw(m_ButtonBody);
  window.draw(m_ButtonText);

}

Button Button::operator=(const Button &button)
{
  SetButtonColor(button.GetButtonColor());
  SetButtonOutlineColor(button.GetButtonOutlineColor());
  SetButtonOutlineThickness(button.GetButtonOutlineThickness());
  SetText(button.GetText());
  SetTextSize(button.GetTextSize());
  SetTextColor(button.GetTextColor());
  SetTextFont(button.GetTextFont());
  SetSize(button.GetSize());
  SetPosition(button.GetPosition());
  return *this;
}