#include <iostream>
#include <vector>
#include "unit.hpp"
#include "board.hpp"
#include "collider.hpp"

Unit::Unit(Board* board, sf::Vector2f pos, Team team, Attributes attributes)
{

    // setup priorityStack
    this->actionStack.push( MARCH );
    
    // setup member vars
    this->parentBoard = board;
    this->attributes = attributes;
    this->hp = attributes.max_hp;
    this->team = team;
    this->moveSpeed = attributes.moveSpeed;

    // TODO remove this temporary sizing
    sf::Vector2f sizeVec;
    sizeVec.x = 20.0f;
    sizeVec.y = 20.0f;

    // setup body rectangle
    this->body.setSize(sizeVec);
    this->body.setOrigin(sizeVec / 2.0f);
    this->body.setPosition(pos);

    // setup vision circle
    this->vision.setRadius(attributes.visionRadius);
    this->vision.setOrigin(attributes.visionRadius, attributes.visionRadius);
    this->vision.setPosition(pos);

    // setup range circle
    this->range.setRadius(attributes.attackRadius);
    this->range.setOrigin(attributes.attackRadius, attributes.attackRadius);
    this->range.setPosition(pos);

    // color
    sf::Color rColor(0, 255, 0);
    rColor.a = 100;
    sf::Color vColor(0, 0, 255);
    vColor.a = 50;
    this->body.setFillColor(sf::Color::Red);
    this->range.setFillColor(rColor);
    this->vision.setFillColor(vColor);
}

// TODO deprecate
bool Unit::shouldDie()
{
    if (actionStack.empty() == false)
        if (actionStack.top() == DYING)
            return true;
    return false;
}

bool Unit::isLiving()
{
    if (hp > 0) return true;
    return false;
}

bool Unit::hasTarget()
{
    if (target != nullptr)
    {
        return true;
    }
    return false;
}

bool Unit::targetInRange()
{
    if (!hasTarget()) return false;
    Collider targetCollider = target->getCollider();
    return getCollider().checkRangeCollision(targetCollider);
}

void Unit::step()
{
    Action topAct = actionStack.top();
    // check health of unit
    if (!isLiving())
    {
        if (topAct != DYING)
            actionStack.push( DYING );
    }
    else
    {
    // priorityStack logic
    if (!actionStack.empty())
    {
        switch (topAct)
        {
            // move forward`
            case MARCH:
            {
                if (team == LEFT)
                {
                    body.move(moveSpeed, 0);
                } else if (team == RIGHT)
                {
                    body.move(-moveSpeed, 0);
                }
                break;
            }
            // move towards another unit in vision
            case MOVE:
            {
                if (isLiving() && hasTarget() && target->isLiving())
                {
                    if (targetInRange())
                    {
                        actionStack.pop();
                        actionStack.push( ATTACK );
                    }
                    else
                    {
                        // movement towards target
                        sf::Vector2f dir = target->getPosition() - getPosition();
                        body.move((moveSpeed / 200) * dir);
                    }
                }
                else
                {
                    // idk what im doing here lmao
                    target = nullptr;
                    actionStack.pop();
                }
                break;
            }
            case ATTACK:
            {
                if (isLiving() && hasTarget())
                {
                    if (target->isLiving())
                    {
                        attack(target);
                    }
                    else
                    {
                        // target is dying, stop targeting
                        target = nullptr;
                        actionStack.pop();
                    }
                }
                else
                {
                    // idk what im doing here lmao
                    actionStack.pop();
                }
                break;
            }
            case DYING:
            {
                // do nothing, maybe show a death animation?
                break;
            }
        }
    } else {
        std::cout << "THIS SHOULD NEVER TRIGGER" << std::endl;
    }
    
    // update pos
    sf::Vector2f curPos = body.getPosition();
    range.setPosition(curPos);
    vision.setPosition(curPos);
    }
}

void Unit::draw(sf::RenderWindow &window)
{
    // draw shapes
    window.draw(body);
    window.draw(range);
    window.draw(vision);
}
