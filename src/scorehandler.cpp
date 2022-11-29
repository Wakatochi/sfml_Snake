#include "../header/scorehandler.h"
#include "../header/globals.h"

ScoreHandler::ScoreHandler()
{
   m_score = 0;
   m_multiplier = 1;

   m_xPos = 25.0f;
   m_yPos = 15.0f;
}

ScoreHandler::ScoreHandler(Font& font)
{
   m_score = 0;
   m_multiplier = 1;

   m_xPos = 100.0f;
   m_yPos = 25.0f;

   m_scoreText.setFont(font);
   m_scoreText.setCharacterSize(24);
   m_scoreText.setFillColor(Color::Cyan);
   m_scoreText.setPosition(m_xPos, m_yPos);

   // DEBUG INFO
   m_angle.setString(toStringf(0.0f));
   m_angle.setFont(font);
   m_angle.setCharacterSize(24);
   m_angle.setFillColor(Color::Cyan);
   m_angle.setPosition(m_xPos + 200.0f, m_yPos);
}

ScoreHandler::~ScoreHandler()
{

}

void
ScoreHandler::initText(Font& font)
{
   m_scoreText.setFont(font);
   m_scoreText.setCharacterSize(12);
   m_scoreText.setFillColor(Color::Magenta);
   m_scoreText.setPosition(m_xPos, m_yPos);

   // DEBUG INFO
   m_angle.setString(toStringf(0.0f));
   m_angle.setFont(font);
   m_angle.setCharacterSize(12);
   m_angle.setFillColor(Color::Magenta);
   m_angle.setPosition(m_xPos + 200.0f, m_yPos);
}

void
ScoreHandler::addScore(int points)
{
   m_score = m_score + (points * m_multiplier);
}

void
ScoreHandler::resetScore()
{
   m_score = 0;
}

int
ScoreHandler::totalScore()
{
   return m_score;
}

void
ScoreHandler::Draw(RenderWindow& window)
{
   m_scoreText.setString("Score: " + toString(m_score));

   window.draw(m_scoreText);
   window.draw(m_angle);
}

String
ScoreHandler::toString(int val)
{
   ostringstream os;
   os << val;
   return os.str();
}

String
ScoreHandler::toStringf(float val)
{
   ostringstream os;
   os << val;
   return os.str();
}

void
ScoreHandler::setAngle(float angle)
{
   m_angle.setString(toStringf(angle));
}