#include "../../../headers/entities/tanks/EnemyTank.h"

#include <random>

float EnemyTank::getDistanceBetweenTanks(const floatPair &point1, const floatPair &point2) {
    const auto [x1, y1] = point1;
    const auto [x2, y2] = point2;

    const float x = x2 - x1;
    const float y = y2 - y1;

    return std::sqrt(x * x + y * y);
}

void EnemyTank::aggressiveMovement(const std::unique_ptr<ITank> &player, const float deltaTime, ProjectileCallBack onShoot) {
    const auto playerPosition = player->getPosition();
    m_shootTime += deltaTime;

    this->rotateToPlayer(player, ROTATION_SPEED * deltaTime);

    if (isFacingPlayer(player, 6.0f)) {
        const auto [playerX, playerY] = playerPosition;
        const auto [enemyX, enemyY] = this->getPosition();

        float x = playerX - enemyX;
        float y = playerY - enemyY;

        float distance = std::sqrt(x * x + y * y);

        if (distance > 0.001f) {
            float directionX = x / distance;
            float directionY = y / distance;

            this->move({directionX * MOVE_SPEED * deltaTime, directionY * MOVE_SPEED * deltaTime});
        }

        if (m_shootTime >= SHOOT_TIMER) {
            onShoot(this->shoot());
            m_shootTime = 0;
        }
    }
}

void EnemyTank::defensiveMovement(const std::unique_ptr<ITank> &player, const float deltaTime, ProjectileCallBack onShoot) {
    const auto playerPosition = player->getPosition();
    m_shootTime += deltaTime;

    this->rotateToPlayer(player, ROTATION_SPEED * deltaTime);

    if (getDistanceBetweenTanks(playerPosition, this->getPosition()) <= SHOOTING_RADIUS && m_shootTime >= SHOOT_TIMER) {
        onShoot(this->shoot());
        m_shootTime = 0;
    }
}

EnemyTank::EnemyTank(const int health, const int damage, floatPair position, const float rotation)
    : ITank(health, damage, std::move(position), rotation)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution randomState(0, static_cast<int>(EnemyState::COUNT) - 1);

    m_state = static_cast<EnemyState>(randomState(gen));
}

bool EnemyTank::isFacingPlayer(const std::unique_ptr<ITank> &playerTank, const float flaw) {
    const auto [x1, y1] = playerTank->getPosition();
    const auto [x2, y2] = this->getPosition();

    const float x = x1 - x2;
    const float y = y1 - y2;

    float distance = std::sqrt(x * x + y * y);
    if (distance < 0.001f) {
        return true;
    }

    float radians = this->getRotation() * M_PI / 180.0f;

    float facingX = std::cos(radians);
    float facingY = std::sin(radians);

    float directionX = x / distance;
    float directionY = y / distance;

    float dotProduct = facingX * directionX + facingY * directionY;

    float aimPrecision = std::cos(flaw * M_PI / 180.0f);

    return dotProduct >= aimPrecision;
}

void EnemyTank::rotateToPlayer(const std::unique_ptr<ITank>& playerTank, const float rotationValue) {
    if (!isFacingPlayer(playerTank, 6.0f)) {
        floatPair enemyPos = this->getPosition();
        floatPair playerPos = playerTank->getPosition();

        float x = playerPos.first - enemyPos.first;
        float y = playerPos.second - enemyPos.second;

        float radians = this->getRotation() * M_PI / 180.0f;
        float facingX = std::cos(radians);
        float facingY = std::sin(radians);

        float cross = facingX * y - facingY * x;

        if (cross > 0) {
            this->rotate(rotationValue);
        } else {
            this->rotate(-rotationValue);
        }
    }
}

void EnemyTank::update(const std::unique_ptr<ITank> &player, const float deltaTime, ProjectileCallBack onShoot) {
    switch (m_state) {
        case EnemyState::Aggressive:
            aggressiveMovement(player, deltaTime, onShoot);
            break;
        case EnemyState::Defensive:
            defensiveMovement(player, deltaTime, onShoot);
            break;
        case EnemyState::Predefined:

            break;
        default:
            break;
    }

    if (m_state == EnemyState::Aggressive) {
        aggressiveMovement(player, deltaTime, onShoot);
    }
}

bool EnemyTank::takeDamage(const int damage) {
    const int newHealth = this->getHealth() - damage;

    if (newHealth < 0) {
        return false;
    }

    this->setHealth(newHealth);
    return true;
}