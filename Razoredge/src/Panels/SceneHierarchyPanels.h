#pragma once

#include "Razor/Scene/Scene.h"
#include "Razor/Core/core.h"
#include "Razor/Core/Log.h"
#include "Razor/Scene/Entity.h"

namespace Razor
{
	class SceneHierarchyPanels
	{
	public:
		SceneHierarchyPanels() = default;
		SceneHierarchyPanels(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context; 
		Entity m_SelectionContext;

		
	};
}
