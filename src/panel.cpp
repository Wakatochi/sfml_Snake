#include "..\header\panel.h"
#include "..\header\globals.h"

Panel::Panel()
{
   m_shape = RectangleShape(Vector2f((float)Const_Window::WINDOW_WIDTH, 32.0f));
   m_xPos = 0.0f;
   m_yPos = 0.0f;

   loadResource();
   m_scoreHandler.initText(m_font);

   m_shape.setTexture(&m_texture);
   m_shape.setTextureRect(IntRect(0, 0, (float)Const_Window::WINDOW_WIDTH, 32));
}

Panel::~Panel()
{

}

void
Panel::Draw(RenderWindow& window)
{
    window.draw(m_shape);
    m_scoreHandler.Draw(window);
}

void
Panel::addPoints(int points)
{
    m_scoreHandler.addScore(points);
}

void
Panel::setAngle(float angle)
{
    m_scoreHandler.setAngle(angle);
}

void
Panel::resetScore()
{
    m_scoreHandler.resetScore();
}

void
Panel::loadResource()
{
    m_texture.loadFromFile("Resources\\Textures\\metal.png");
    m_sprite.setTexture(m_texture);

    m_font.loadFromFile("Resources\\Fonts\\Retro Stereo Wide.ttf");
}