#include "CollisionComponent.h"
#include "Actor.h"
#include <algorithm>

#

CollisionComponent::CollisionComponent(class Actor* owner)
: Component(owner)
, mWidth(0.0f)
, mHeight(0.0f)
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::Intersect(const CollisionComponent* other) const
{
	bool noIntersection = this->GetMax().x < other->GetMin().x ||
						  other->GetMax().x < this->GetMin().x ||
						  this->GetMax().y < other->GetMin().y ||
						  other->GetMax().y < this->GetMin().y;

	return !noIntersection;
}

Vector2 CollisionComponent::GetMin() const
{
	float x = GetCenter().x - (mWidth * mOwner->GetScale()) / 2.0f;
	float y = GetCenter().y - (mHeight * mOwner->GetScale()) / 2.0f;
	return Vector2(x, y);
}

Vector2 CollisionComponent::GetMax() const
{
	float x = GetCenter().x + (mWidth * mOwner->GetScale()) / 2.0f;
	float y = GetCenter().y + (mHeight * mOwner->GetScale()) / 2.0f;
	return Vector2(x, y);
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(const CollisionComponent* other, Vector2& offset) const
{
	offset = Vector2::Zero;

	//no itersections
	if (!Intersect(other))
	{
		return CollSide::None;
	}

	float topDist = other->GetMin().y - GetMax().y;
	float bottomDist = other->GetMax().y - GetMin().y;
	float leftDist = other->GetMin().x - GetMax().x;
	float rightDist = other->GetMax().x - GetMin().x;

	// Determine the minimum overlap side
	float minOverlap =
		std::min(std::abs(topDist),
				 std::min(std::abs(bottomDist), std::min(std::abs(leftDist), std::abs(rightDist))));

	if (minOverlap == std::abs(topDist))
	{
		offset.y = topDist;
		return CollSide::Top;
	}
	if (minOverlap == std::abs(bottomDist))
	{
		offset.y = bottomDist;
		return CollSide::Bottom;
	}
	if (minOverlap == std::abs(leftDist))
	{
		offset.x = leftDist;
		return CollSide::Left;
	}

	offset.x = rightDist;
	return CollSide::Right;
}
