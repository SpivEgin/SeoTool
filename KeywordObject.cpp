#include "KeywordObject.h"

KeywordObject::KeywordObject()
{

}

QString KeywordObject::name() const
{
    return m_name;
}

void KeywordObject::setName(const QString &name)
{
    m_name = name;
}

int KeywordObject::position() const
{
    return m_position;
}

void KeywordObject::setPosition(int position)
{
    m_position = position;
}

int KeywordObject::bestPosition() const
{
    return m_bestPosition;
}

void KeywordObject::setBestPosition(int value)
{
    m_bestPosition = value;
}

int KeywordObject::newPosition() const
{
    return m_newPosition;
}

void KeywordObject::setNewPosition(int newPosition)
{
    m_newPosition = newPosition;
    setTime(QDateTime::currentDateTime());

    if(m_newPosition < m_bestPosition || m_bestPosition < 0 )
    {
        setBestPosition(m_newPosition);
        setBestPosTime(QDateTime::currentDateTime());
    }

    setPositionDiff(m_position - m_newPosition);
}

QDateTime KeywordObject::time() const
{
    return m_time;
}

void KeywordObject::setTime(const QDateTime &time)
{
    m_time = time;
}

QDateTime KeywordObject::bestPosTime() const
{
    return m_bestPosTime;
}

void KeywordObject::setBestPosTime(const QDateTime &bestPosTime)
{
    m_bestPosTime = bestPosTime;
}

int KeywordObject::positionDiff() const
{
    return m_positionDiff;
}

void KeywordObject::setPositionDiff(int positionDiff)
{
    m_positionDiff = positionDiff;
}

int KeywordObject::domainID() const
{
    return m_domainID;
}

void KeywordObject::setDomainID(int domainID)
{
    m_domainID = domainID;
}

