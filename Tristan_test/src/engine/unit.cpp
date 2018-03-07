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

bool Unit::shouldDie()
{
    if (actionStack.empty() == false)
        std::cout << actionStack.size() << std::endl;
        if (actionStack.top() == DYING)
            return true;
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

void Unit::step(sf::RenderWindow& window)
{
    Action topAct = actionStack.top();
    // check health of unit
    if (hp <= 0 && !shouldDie())
    {
        std::cout << "health at death " << hp << std::endl;
        actionStack.push( DYING );
    }

    // priorityStack logic
    if (!actionStack.empty())
    {
        switch (topAct)
        {
            // move forward`
            case MARCH:
            {
                //std::cout << "MARCH" << std::endl;
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
                //std::cout << "MOVE" << std::endl;
                if (hasTarget())
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
                    actionStack.pop();
                }
                break;
            }
            case ATTACK:
            {
                //std::cout << "ATTACK" << std::endl;
                if (hasTarget())
                {
                    if (target->shouldDie())
                    {
                        // target is dying, stop targeting
                        target = nullptr;
                        actionStack.pop();
                    }
                    else
                    {
                        attack(target);
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
                //std::cout << "DYING" << std::endl;
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
    // draw shapes
    window.draw(body);
    window.draw(range);
    window.draw(vision);
}
