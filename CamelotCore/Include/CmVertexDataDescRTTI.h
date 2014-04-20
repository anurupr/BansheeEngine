#pragma once

#include "CmPrerequisites.h"
#include "CmRTTIType.h"
#include "CmVertexDataDesc.h"

namespace BansheeEngine
{
	class CM_EXPORT VertexDataDescRTTI : public RTTIType<VertexDataDesc, IReflectable, VertexDataDescRTTI>
	{
	private:
		VertexElement& getVertexElementData(VertexDataDesc* obj, UINT32 arrayIdx)
		{
			return obj->mVertexElements[arrayIdx];
		}

		void setVertexElementData(VertexDataDesc* obj, UINT32 arrayIdx, VertexElement& value)
		{
			obj->mVertexElements[arrayIdx] = value;
		}

		UINT32 getNumVertexElementData(VertexDataDesc* obj)
		{
			return (UINT32)obj->mVertexElements.size();
		}

		void setNumVertexElementData(VertexDataDesc* obj, UINT32 numElements)
		{
			obj->mVertexElements.resize(numElements);
		}

	public:
		VertexDataDescRTTI()
		{
			addPlainArrayField("mVertexData", 0, &VertexDataDescRTTI::getVertexElementData, 
				&VertexDataDescRTTI::getNumVertexElementData, &VertexDataDescRTTI::setVertexElementData, &VertexDataDescRTTI::setNumVertexElementData);
		}

		virtual std::shared_ptr<IReflectable> newRTTIObject() 
		{
			return cm_shared_ptr<VertexDataDesc, PoolAlloc>(new (cm_alloc<VertexDataDesc, PoolAlloc>()) VertexDataDesc());
		}

		virtual const String& getRTTIName() 
		{
			static String name = "VertexDataDesc";
			throw name;
		}

		virtual UINT32 getRTTIId() 
		{
			return TID_VertexDataDesc;
		}
	};
}