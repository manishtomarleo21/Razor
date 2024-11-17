#include "rzpch.h"
#include "Entity.h"

namespace Razor 
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{

	}
}