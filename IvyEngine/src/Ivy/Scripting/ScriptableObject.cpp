#include "ivypch.h"
#include "ScriptableObject.h"

#include "ScriptManager.h"
#include "../Core/Logger.h"

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
		this->isAlive = true;
		this->scriptObject = 0;
		this->weakReferenceFlag = 0;
	}

	ScriptableObject::ScriptableObject(const std::string& name)
	{
		this->name = name;
		this->referenceCount = 1;
		this->isAlive = true;
		this->scriptObject = 0;
		this->weakReferenceFlag = 0;
	}

	ScriptableObject::~ScriptableObject()
	{
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

	asILockableSharedBool* ScriptableObject::getWeakRefereneFlag()
	{
		if (!weakReferenceFlag)
			weakReferenceFlag = asCreateLockableSharedBool();

		return weakReferenceFlag;
	}

	void ScriptableObject::destoryAndRelease()
	{
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
			//IVY_CORE_INFO("ScriptableObject::OnUpadte. scriptObject");
			ScriptManager::GetInstance().callOnUpdate(scriptObject);
		}
	}


	void ScriptableObject::sendMessage(CScriptHandle message, ScriptableObject* target)
	{
		if (target && target->scriptObject)
			ScriptManager::GetInstance().callOnMessage(target->scriptObject, message, this);
	}

	/*void ScriptableObject::killObject()
	{
		// Just flag the object as dead.The game manager will
		// do the actual destroying at the end of the frame
		isAlive = false;
	}*/
}
