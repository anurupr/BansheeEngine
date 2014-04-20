#pragma once

#include "CmPrerequisites.h"

namespace BansheeEngine
{
	class RenderSystem;
	typedef std::shared_ptr<RenderSystem> RenderSystemPtr;

	class RenderSystemFactory
	{
	public:
		virtual void create() = 0;
		virtual const String& name() const = 0;
	};
}