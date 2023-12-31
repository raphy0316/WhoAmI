#include "DXUT.h"
#include "Entity.h"

Entity::Entity()
	:pos(0, 0),
	scale(1, 1),
	scaleCenter(0, 0),
	rotation(0.f),
	rotationCenter(0, 0),
	rect(0, 0, 0, 0),
	visibleRect(0, 0, 0, 0),
	visible(true),
	updateEnabled(true),
	renderChildrenEnabled(true),
	parent(nullptr),
	removing(false),
	deleting(false)
{
}

Entity::~Entity(void)
{
	for (auto* child : children)
		delete child;
}


void Entity::addChild(Entity* child)
{
	children.push_back(child);
	child->parent = this;
}

void Entity::removeChild(Entity* child)
{
	child->removing = true;
}

void Entity::update(float dt)
{
	if(!updateEnabled) return;

	for(auto* child : children)
		child->update(dt);

	for(auto iter = begin(children); iter != end(children); ++iter)
	{
		if(!(*iter)->removing) continue;
		
		SAFE_DELETE(*iter);
		iter = children.erase(iter);
		if(iter == children.end())
			break;
	}
}

void Entity::render()
{
	if(!visible) return;
	D3DXMatrixTransformation2D(&matrix, &scaleCenter, 0, &scale, &rotationCenter, rotation, &pos);

	if(parent)
		matrix *= parent->matrix;

	if(!renderChildrenEnabled) return;
	for(auto* child:children)
		child->render();
}

Vec2 Entity::center()
{
	return pos + rect.center();
}

Rect Entity::rectWithPos()
{
	return rect.offset(pos);
}

void Entity::setCenter(Vec2 pos)
{
	this->pos = pos - rect.center();
}
