#include "..\header\panel.h"
#include "..\header\globals.h"

Panel::Panel()
{
   m_xPos = 0.0f;
   m_yPos = 0.0f;
}

Panel::Panel(Texture& texture)
{
   m_shape = RectangleShape(Vector2f((float)Const_Window::WINDOW_WIDTH, 15.0f));
   m_texture = &texture;

   m_xPos = 0.0f;
   m_yPos = 0.0f;
}


Panel::~Panel()
{

}

void
Panel::Update()
{

}

void
Panel::Draw(RenderWindow& window)
{

}
