#include "ivypch.h"
#include "ScriptableObject.h"

#include "ScriptManager.h"
#include "../Core/Logger.h"
#include "../ECS/ECS.h"

namespace Ivy {

	void ScriptableObject::setOwner(Entity ownerEntity) 
	{
		this->ownerEntity = ownerEntity;
	}

	Entity ScriptableObject::getOwner()
	{
		return this->ownerEntity;
	}

	ScriptableObject::ScriptableObject()
	{
		this->name = "";
		this->referenceCount = 1;
		this->scriptObject = 0;
		this->weakReferenceFlag = 0;
		this->alive = true;
	}

	ScriptableObject::ScriptableObject(const std::string& name)
	{
		this->name = name;
		this->referenceCount = 1;
		this->scriptObject = 0;
		this->weakReferenceFlag = 0;
		this->alive = true;

	}

	ScriptableObject::~ScriptableObject()
	{
		//IVY_CORE_INFO("ScriptableObject: Destroying ScriptableObject: name={0}, ownerEntity={2}, referenceCount={1}", name, referenceCount, ownerEntity);
		// Notify objects that hold weak references to this object that it has been destroyed
		if (weakReferenceFlag)
		{
			weakReferenceFlag->Set(true);
			weakReferenceFlag->Release();
		}
		// Release the script controller
		if (scriptObject)
		{
			scriptObject->Release();
		}
	}

	void ScriptableObject::kill()
	{
		this->alive = false;		
	}

	int ScriptableObject::addReference()
	{
		//IVY_CORE_INFO("ScriptableObject: Adding reference: name={0}, ownerEntity={2}, referenceCount={1}", name, referenceCount, ownerEntity);
		return ++referenceCount;
	}

	int ScriptableObject::release()
	{
		//IVY_CORE_INFO("ScriptableObject: Releasing: name={0}, ownerEntity={2}, referenceCount={1}", name, referenceCount, ownerEntity);
		if (--referenceCount <= 0)
		{
			delete this;
			return 0;
		}
		return referenceCount;
	}

	asILockableSharedBool* ScriptableObject::getWeakRefereneFlag()
	{
		if (!weakReferenceFlag)
			weakReferenceFlag = asCreateLockableSharedBool();

		return weakReferenceFlag;
	}

	void ScriptableObject::destoryAndRelease()
	{
		IVY_CORE_INFO("ScriptableObject: Destroy and Release: name={0}, ownerEntity={2}, referenceCount={1}", name, referenceCount, ownerEntity);
		// Release all referrences that this object holds
		if (scriptObject)
		{
			scriptObject->Release();
			scriptObject = 0;
		}
		// Then release this object
		release();
	}

	void ScriptableObject::onUpdate()
	{
		if (scriptObject) {
			ScriptManager::GetInstance().callOnUpdate(scriptObject);
		}
	}


	void ScriptableObject::sendMessage(CScriptHandle message, ScriptableObject* target)
	{
		if (target && target->scriptObject) {
			ScriptManager::GetInstance().callOnMessage(target->scriptObject, message, this);
		}
	}
}
