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

	ScriptableObject::ScriptableObject(const ScriptableObject& other)
	{
		this->name = other.name;
		this->referenceCount = other.referenceCount;
		this->scriptObject = other.scriptObject;
		this->weakReferenceFlag = other.weakReferenceFlag;
		this->alive = other.alive;
	}

	ScriptableObject& ScriptableObject::operator=(const ScriptableObject& other)
	{
		this->name = other.name;
		this->referenceCount = other.referenceCount;
		this->scriptObject = other.scriptObject;
		this->weakReferenceFlag = other.weakReferenceFlag;
		this->alive = other.alive;

		return *this;
	}
	ScriptableObject::~ScriptableObject()
	{
		// Notify objects that hold weak references to this object that it has been destroyed
		if (weakReferenceFlag != NULL)
		{
			weakReferenceFlag->Set(true);
			weakReferenceFlag->Release();
		}
		// Release the script controller
		if (scriptObject != NULL)
		{
			scriptObject->Release();
		}
	}

	asILockableSharedBool* ScriptableObject::getWeakRefereneFlag()
	{
		if (!weakReferenceFlag)
			weakReferenceFlag = asCreateLockableSharedBool();

		return weakReferenceFlag;
	}

	int ScriptableObject::addReference()
	{
		return ++referenceCount;
	}

	int ScriptableObject::release()
	{
		if (--referenceCount <= 0)
		{
			delete this;
			return 0;
		}
		return referenceCount;
	}

	void ScriptableObject::destoryAndRelease()
	{
		IVY_CORE_INFO("ScriptableObject: Destroy and Release: name={0}, ownerEntity={2}, referenceCount={1}", name, referenceCount, ownerEntity);
		// Release all referrences that this object holds
		if (scriptObject)
		{
			scriptObject->Release();
			scriptObject = 0;
			weakReferenceFlag = 0;
			name = "";
			ownerEntity = 0;
			alive = false;
			referenceCount = 0;

		}
		// Then release this object
		release();
	}

	void ScriptableObject::kill()
	{
		this->alive = false;		
	}


	void ScriptableObject::onUpdate()
	{
		if (alive && scriptObject != NULL) {
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
