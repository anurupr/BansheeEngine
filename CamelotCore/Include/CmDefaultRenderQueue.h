#pragma once

#include "CmPrerequisites.h"
#include "CmRenderQueue.h"

namespace BansheeEngine 
{
	class CM_EXPORT DefaultRenderQueue : public RenderQueue
	{
	public:
		void sort();
	};
}