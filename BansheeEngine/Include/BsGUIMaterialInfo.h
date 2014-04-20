#pragma once

#include "BsPrerequisites.h"
#include "CmGpuParam.h"

namespace BansheeEngine
{
	struct GUIMaterialInfo
	{
		HMaterial material;
		GpuParamMat4 worldTransform;
		GpuParamFloat invViewportWidth;
		GpuParamFloat invViewportHeight;
		GpuParamTexture mainTexture;
		GpuParamVec4 tint;
	};
}