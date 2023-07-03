#pragma once

#include <iostream>
#include <string>

#include "../SFML/Graphics.hpp"

class Button{

public:

  Button();
  Button(
    const sf::Vector2f& Pos,
    const sf::Vector2f& Size,
    const sf::Color& ButtonBodyColor,
    const sf::Color& ButtonOutlineColor,
    float ButtonOutlineThickness,
    const std::string& ButtonText,
    int ButtonTextSize,
    const sf::Color& ButtonTextColor,
    const sf::Font* ButtonTextFont
  );

  void SetPosition (const sf::Vector2f& pos);
  void SetSize (const sf::Vector2f& size);
  void SetButtonColor (const sf::Color& color);
  void SetButtonOutlineColor ( const sf::Color& color);
  void SetButtonOutlineThickness (const float t);
  void SetText (const std::string& str);
  void SetTextSize (const int s);
  void SetTextColor (const sf::Color& color);
  void SetTextFont (const sf::Font * font);

  const sf::Vector2f& GetPosition () const;
  const sf::Vector2f& GetSize () const;
  const sf::Color& GetButtonColor () const;
  const sf::Color& GetButtonOutlineColor () const;
  const float GetButtonOutlineThickness () const;
  const std::string& GetText () const;
  const int GetTextSize () const;
  const sf::Color& GetTextColor () const;
  const sf::Font* GetTextFont () const;

  Button operator=(const Button& button);

  bool MouseOver(sf::RenderWindow& window) const;
  
  void RenderTo(sf::RenderWindow& window) const;

  bool IsClicked;

private:
  sf::RectangleShape m_ButtonBody;
  sf::Text m_ButtonText;

};