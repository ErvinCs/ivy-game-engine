#include "ivypch.h"
#include "GameObject.h"

#include "ScriptManager.h"

namespace Ivy {

	GameObject::GameObject()
	{
		this->referenceCount = 1;
		this->isAlive = true;
		this->scriptObject = 0;
		this->weakReferenceFlag = 0;
		//this->position = glm::vec2(1.0f);
	}

	GameObject::~GameObject()
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

	int GameObject::addReference()
	{
		return ++referenceCount;
	}

	int GameObject::release()
	{
		if (--referenceCount == 0)
		{
			delete this;
			return 0;
		}
		return referenceCount;
	}

	asILockableSharedBool* GameObject::getWeakRefereneFlag()
	{
		if (!weakReferenceFlag)
			weakReferenceFlag = asCreateLockableSharedBool();

		return weakReferenceFlag;
	}

	void GameObject::destoryAndRelease()
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

	void GameObject::onUpdate()
	{
		if (scriptObject)
			ScriptManager::GetInstance().callOnUpdate(scriptObject);
	}


	void GameObject::sendMessage(CScriptHandle message, GameObject* target)
	{
		if (target && target->scriptObject)
			ScriptManager::GetInstance().callOnMessage(target->scriptObject, message, this);
	}

	void GameObject::killObject()
	{
		// Just flag the object as dead.The game manager will
		// do the actual destroying at the end of the frame
		isAlive = false;
	}
}
