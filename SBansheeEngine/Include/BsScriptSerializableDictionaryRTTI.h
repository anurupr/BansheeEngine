#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "CmRTTIType.h"
#include "CmGameObjectManager.h"
#include "BsScriptSerializableDictionary.h"
#include "BsRuntimeScriptObjects.h"
#include "BsMonoManager.h"
#include "BsMonoClass.h"

namespace BansheeEngine
{
	class BS_SCR_BE_EXPORT ScriptSerializableDictionaryRTTI : public RTTIType<ScriptSerializableDictionary, IReflectable, ScriptSerializableDictionaryRTTI>
	{
	private:
		ScriptSerializableTypeInfoDictionaryPtr getTypeInfo(ScriptSerializableDictionary* obj) { return obj->mDictionaryTypeInfo; }
		void setTypeInfo(ScriptSerializableDictionary* obj, ScriptSerializableTypeInfoDictionaryPtr val) { obj->mDictionaryTypeInfo = val; }

		ScriptSerializableFieldDataPtr getKeyEntry(ScriptSerializableDictionary* obj, UINT32 arrayIdx) { return obj->mKeyEntries[arrayIdx]; }
		void setKeyEntry(ScriptSerializableDictionary* obj, UINT32 arrayIdx, ScriptSerializableFieldDataPtr val) { obj->mKeyEntries[arrayIdx] = val; }
		UINT32 getNumKeyEntries(ScriptSerializableDictionary* obj) { return (UINT32)obj->mKeyEntries.size(); }
		void setNumKeyEntries(ScriptSerializableDictionary* obj, UINT32 numEntries) { obj->mKeyEntries.resize(numEntries); }

		ScriptSerializableFieldDataPtr getValueEntry(ScriptSerializableDictionary* obj, UINT32 arrayIdx) { return obj->mValueEntries[arrayIdx]; }
		void setValueEntry(ScriptSerializableDictionary* obj, UINT32 arrayIdx, ScriptSerializableFieldDataPtr val) { obj->mValueEntries[arrayIdx] = val; }
		UINT32 getNumValueEntries(ScriptSerializableDictionary* obj) { return (UINT32)obj->mValueEntries.size(); }
		void setNumValueEntries(ScriptSerializableDictionary* obj, UINT32 numEntries) { obj->mValueEntries.resize(numEntries); }

	public:
		ScriptSerializableDictionaryRTTI()
		{
			addReflectablePtrField("mListTypeInfo", 0, &ScriptSerializableDictionaryRTTI::getTypeInfo, &ScriptSerializableDictionaryRTTI::setTypeInfo);
			addReflectablePtrArrayField("mKeyEntries", 1, &ScriptSerializableDictionaryRTTI::getKeyEntry, &ScriptSerializableDictionaryRTTI::getNumKeyEntries, 
				&ScriptSerializableDictionaryRTTI::setKeyEntry, &ScriptSerializableDictionaryRTTI::setNumKeyEntries);
			addReflectablePtrArrayField("mValueEntries", 2, &ScriptSerializableDictionaryRTTI::getValueEntry, &ScriptSerializableDictionaryRTTI::getNumValueEntries, 
				&ScriptSerializableDictionaryRTTI::setValueEntry, &ScriptSerializableDictionaryRTTI::setNumValueEntries);
		}

		virtual void onSerializationStarted(IReflectable* obj)
		{
			ScriptSerializableDictionary* serializableObject = static_cast<ScriptSerializableDictionary*>(obj);
			serializableObject->serializeManagedInstance();
		}

		virtual void onDeserializationStarted(IReflectable* obj)
		{
			ScriptSerializableDictionary* serializableObject = static_cast<ScriptSerializableDictionary*>(obj);

			// If we are deserializing a GameObject we need to defer deserializing actual field values
			// to ensure GameObject handles instances have been fixed up (which only happens after deserialization is done)
			if(GameObjectManager::instance().isGameObjectDeserializationActive())
				GameObjectManager::instance().registerOnDeserializationEndCallback([=] () { serializableObject->deserializeManagedInstance(); });
			else
				serializableObject->deserializeManagedInstance();
		}

		virtual const String& getRTTIName()
		{
			static String name = "ScriptSerializableDictionary";
			return name;
		}

		virtual UINT32 getRTTIId()
		{
			return TID_ScriptSerializableDictionary;
		}

		virtual std::shared_ptr<IReflectable> newRTTIObject()
		{
			return ScriptSerializableDictionary::createEmpty();
		}
	};
}