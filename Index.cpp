#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

float GetMagnitude(const sf::Vector2f& vect){
  return sqrt(vect.x * vect.x + vect.y * vect.y);
}

const float WINDOW_HEIGHT = 500;
const float WINDOW_WIDTH = 800;

const float BALL_SPEED = 500.f;
const float BALL_RADIUS = 10.f;
const float PLAYER_SPEED = 500.f;
const sf::Vector2f PLAYER_SIZE(20, 70);

sf::CircleShape ball(BALL_RADIUS);

sf::RectangleShape Player1(PLAYER_SIZE);
sf::RectangleShape Player2(PLAYER_SIZE);

bool Player1_Is_Moving = false;
bool Player2_Is_Moving = false;

sf::Vector2f Player1_Movement_Direction;
sf::Vector2f Player2_Movement_Direction;

int Player2_Point = 0;
int Player1_Point = 0;

sf::Text Player1_Point_Count;
sf::Text Player2_Point_Count;
sf::Vector2f& MoveBall(sf::Time DeltaTime, sf::Vector2f& BallDirection){
  
  float MoveAmount = BALL_SPEED * DeltaTime.asSeconds();
  sf::Vector2f Displacement = BallDirection * MoveAmount;
  sf::Vector2f NewPos = ball.getPosition() + Displacement;

  if (NewPos.x <= 0){
    Player2_Point++;
    NewPos = sf::Vector2f(400, 250);
  } else if(NewPos.x >= WINDOW_WIDTH - 2 * BALL_RADIUS){
    Player1_Point++;    
    NewPos = sf::Vector2f(400, 250);
  }

  if (NewPos.y <= 0 || NewPos.y >= WINDOW_HEIGHT - 2 * BALL_RADIUS) BallDirection.y = - BallDirection.y;
  
  if (NewPos.x < (Player1.getPosition().x + PLAYER_SIZE.x) && 
      NewPos.y < (Player1.getPosition().y + PLAYER_SIZE.y) &&
      NewPos.y > Player1.getPosition().y
    ) {
      BallDirection.x = - BallDirection.x;
    }
  else if (NewPos.x + 2 * BALL_RADIUS > (Player2.getPosition().x) &&
           NewPos.y < (Player2.getPosition().y + PLAYER_SIZE.y) &&
           NewPos.y > Player2.getPosition().y
  ) {
    BallDirection.x = - BallDirection.x;
  }
  ball.setPosition(NewPos);
  
  return BallDirection /= GetMagnitude(BallDirection);
}

void MovePlayer(bool IsMoving, sf::RectangleShape& player, sf::Vector2f& dir, sf::Time& DeltaTime){
  if (!IsMoving) return;

  float MoveAmount = PLAYER_SPEED * DeltaTime.asSeconds();
  sf::Vector2f Displacement = dir * MoveAmount;
  sf::Vector2f NewPos = player.getPosition() + Displacement;

  if (NewPos.y <= 0 || NewPos.y >= WINDOW_HEIGHT - PLAYER_SIZE.y) NewPos = player.getPosition(); 
  player.setPosition(NewPos);
}

void ParseKeyPressEvent(){
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    Player1_Is_Moving = true;
    Player1_Movement_Direction = sf::Vector2f(0, -1);
  }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    Player1_Is_Moving = true;
    Player1_Movement_Direction = sf::Vector2f(0, 1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    Player2_Is_Moving = true;
    Player2_Movement_Direction = sf::Vector2f(0, -1);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    Player2_Is_Moving = true;
    Player2_Movement_Direction = sf::Vector2f(0, 1);
  }
}

void ParseKeyReleaseEvent(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::W) {
    Player1_Is_Moving = false;
  }else if (key == sf::Keyboard::S) {
    Player1_Is_Moving = false;
  }
  if (key == sf::Keyboard::Up) {
    Player2_Is_Moving = false;
  } else if (key == sf::Keyboard::Down){
    Player2_Is_Moving = false;
  }
}

void ParseEvents(sf::RenderWindow& window, sf::Event& event, sf::Time& dt){
  switch (event.type)
  {
  case sf::Event::Closed:
    window.close();
    break;
  case sf::Event::KeyPressed:
    ParseKeyPressEvent();
    break;
  case sf::Event::KeyReleased:
    ParseKeyReleaseEvent(event.key.code);
  default:
    break;
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 500), "Pong");
 
  sf::Font FiraCode;
  if(!FiraCode.loadFromFile("./Assets/Fonts/FiraCodeNerdFontMono-Retina.ttf")){
    std::cout << "Font not loaded...\n";
  }

  ball.setFillColor(sf::Color::Red);
  ball.setPosition(sf::Vector2f(400, 250));

  Player1.setFillColor(sf::Color::White);
  Player1.setPosition(sf::Vector2f(5, 0));
  Player2.setFillColor(sf::Color::White);
  Player2.setPosition(sf::Vector2f(775, 0));

  Player1_Point_Count.setPosition(sf::Vector2f(100, 50));
  Player1_Point_Count.setFont(FiraCode);
  Player2_Point_Count.setPosition(sf::Vector2f(700, 50));
  Player2_Point_Count.setFont(FiraCode);

  sf::Clock clock;
  sf::Time delta;
  sf::Vector2f BallDirection (3, 4);
  while (window.isOpen())
  {
    
    sf::Event event;
    while(window.pollEvent(event)) ParseEvents(window, event, delta);

    Player1_Point_Count.setString(std::to_string(Player1_Point));
    Player2_Point_Count.setString(std::to_string(Player2_Point));

    window.clear();
    
    BallDirection = MoveBall(delta, BallDirection);
    
    MovePlayer(Player1_Is_Moving, Player1, Player1_Movement_Direction, delta);
    MovePlayer(Player2_Is_Moving, Player2, Player2_Movement_Direction, delta);

    window.draw(ball);
    window.draw(Player1);
    window.draw(Player2);
    window.draw(Player1_Point_Count);
    window.draw(Player2_Point_Count);
    window.display();
    
    delta = clock.restart();
  }
  return 0;
}