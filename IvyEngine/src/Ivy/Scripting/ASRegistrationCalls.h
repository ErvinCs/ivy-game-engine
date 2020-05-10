#pragma once

#include <glm/glm.hpp>
#include <angelscript.h>

#include "MethodWrappers.h"
#include "../Core/Timestep.h"
#include "../Core/InputHandler.h"
#include "../Core/Application.h"

namespace Ivy
{
	static void RegisterTimestep(asIScriptEngine* scriptEngine)
	{
		int r;
		// Register global time variable
		r = scriptEngine->RegisterGlobalProperty("float deltatime", &Application::getInstance().globalTime); assert(r >= 0);

		// Register Timestep
		/*
		r = scriptEngine->RegisterObjectType("Timestep", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Timestep", asBEHAVE_ADDREF, "void f()", asMETHOD(Timestep, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Timestep", asBEHAVE_RELEASE, "void f()", asMETHOD(Timestep, release), asCALL_THISCALL); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opAddAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator+=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opSubAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator-=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opMulAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator*=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timestep &opDivAssign(const Timestep& in)",
			asMETHODPR(Timestep, operator/=, (const Timestep&), Timestep&), asCALL_THISCALL); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opAddAssign(const float& in)",
			asMETHODPR(Timestep, operator+=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opSubAssign(const float& in)",
			asMETHODPR(Timestep, operator-=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opMulAssign(const float& in)",
			asMETHODPR(Timestep, operator*=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float &opDivAssign(const float& in)",
			asMETHODPR(Timestep, operator/=, (const float&), float&), asCALL_THISCALL); assert(r >= 0);
		*/

		/*
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opAdd(const Timestep &in)",
			asFUNCTIONPR(operator+, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opSub(const Timestep &in)",
			asFUNCTIONPR(operator-, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opMul(const Timestep &in)",
			asFUNCTIONPR(operator*, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "Timesteop opDiv(const Timestep &in)",
			asFUNCTIONPR(operator/, (const Timestep&, const Timestep&), Timestep), asCALL_CDECL_OBJFIRST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Timestep", "float opAdd(const float &in)",
			asFUNCTIONPR(operator+, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opSub(const float &in)",
			asFUNCTIONPR(operator-, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opMul(const float &in)",
			asFUNCTIONPR(operator*, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Timestep", "float opDiv(const float &in)",
			asFUNCTIONPR(operator/, (const Timestep&, const float&), float), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		*/
	}

	static void RegisterVec2(asIScriptEngine* scriptEngine)
	{
		int r;

		// Register Vec2 GLM Type
		r = scriptEngine->RegisterObjectType("Vec2", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Vec2", "float x", asOFFSET(glm::vec2, x)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Vec2", "float y", asOFFSET(glm::vec2, y)); assert(r >= 0);

		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec2Default), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(const Vec2 &in)", asFUNCTION(Vec2Copy), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Vec2Init1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vec2Init2), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opAddAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator+=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opSubAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator-=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opMulAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator*=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opDivAssign(const Vec2& in) const",
			asMETHODPR(glm::vec2, operator/=, (const glm::vec2 &), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "bool opEquals(const Vec2& in) const",
			asFUNCTIONPR(glm::operator==, (const glm::vec2&, const glm::vec2&), bool), asCALL_CDECL_OBJFIRST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opAdd(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator+, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opSub(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator-, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opMul(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator*, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 opDiv(const Vec2 &in) const",
			asFUNCTIONPR(glm::operator/, (const glm::vec2&, const glm::vec2&), glm::vec2), asCALL_CDECL_OBJFIRST); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opAddAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator+=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opSubAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator-=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opMulAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator*=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("Vec2", "Vec2 &opDivAssign(const float& in) const",
			asMETHODPR(glm::vec2, operator/=, (const float&), glm::vec2&), asCALL_THISCALL); assert(r >= 0);
	}

	/* 
	 * Register the Transform component.
	 * Properties: position : vec2, scale : vec2, rotation: float
	 * Factory Methods: Transform(), Transform(vec2, float, vec2)
	 * Operators: assignment(=) - Invokes the copy constructor of Transform
	 * Static Methods:
	 *   void DestroyTransform(uint16) - Destroy the transform owned by the passed entity
	 *   Transform@ FindTransform(uint16) - Returns a reference to the transformed owned by the passed entity
	 */
	static void RegisterTransform(asIScriptEngine* scriptEngine)
	{
		int r;

		// Register Transform type
		r = scriptEngine->RegisterObjectType("Transform", 0, asOBJ_REF); assert(r >= 0);
		// Enable reference counting for references to a Transform component
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_ADDREF, "void f()", asMETHOD(Transform, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_RELEASE, "void f()", asMETHOD(Transform, release), asCALL_THISCALL); assert(r >= 0);

		// Constructors
		r = scriptEngine->RegisterGlobalFunction("Transform@ InitTransform()", asFUNCTION(Transform_Factory1), asCALL_CDECL); assert(r >= 0);

		// Fields
		r = scriptEngine->RegisterObjectProperty("Transform", "Vec2 position", asOFFSET(Transform, position)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Transform", "float rotation", asOFFSET(Transform, rotation)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Transform", "Vec2 scale", asOFFSET(Transform, scale)); assert(r >= 0);

		// The assignment operator for transform
		r = scriptEngine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)",
			asMETHODPR(Transform, operator=, (const Transform &), Transform &), asCALL_THISCALL); assert(r >= 0);
		// Factory methods for Transform such that it can be instantiated in script
		r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_FACTORY, "Transform@ f()", asFUNCTION(Transform_Factory1), asCALL_CDECL); assert(r >= 0);
		//r = scriptEngine->RegisterObjectBehaviour("Transform", asBEHAVE_FACTORY, "Transform@ f(Vec2, float, Vec2)", asFUNCTION(Transform_Factory2), asCALL_CDECL); assert(r >= 0);

		// Destroy the Transform owned by the passed entity
		r = scriptEngine->RegisterGlobalFunction("void DestroyTransform(uint16)", asFUNCTION(SelfDestroyTransform), asCALL_CDECL);
		// Provide access to the transform component of an Entity if it exists.
		r = scriptEngine->RegisterGlobalFunction("Transform@ FindTransform(uint16)", asFUNCTION(FindTransform), asCALL_CDECL); assert(r >= 0);
		// Flip the Transform of a scriptable object by 90/180/270 degrees
		r = scriptEngine->RegisterGlobalFunction("void Rotate90(Transform &)", asFUNCTION(Rotate90Transform), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void Rotate180(Transform &)", asFUNCTION(Rotate180Transform), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void Rotate270(Transform &)", asFUNCTION(Rotate270Transform), asCALL_CDECL); assert(r >= 0);
	}

	static void RegisterRenderable(asIScriptEngine* scriptEngine)
	{
		int r;

		// Register the Renderable component. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("Sprite", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", asMETHOD(Renderable, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", asMETHOD(Renderable, release), asCALL_THISCALL); assert(r >= 0);

		r = scriptEngine->RegisterGlobalFunction("Sprite@ InitSprite()", asFUNCTION(Renderable_Factory1), asCALL_CDECL); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Sprite", "Sprite &opAssign(const Sprite &in)",
			asMETHODPR(Renderable, operator=, (const Renderable &), Renderable &), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@ f()", asFUNCTION(Renderable_Factory1), asCALL_CDECL); assert(r >= 0);

		// Destroy owned Renderable
		r = scriptEngine->RegisterGlobalFunction("void DestroySprite(uint16)", asFUNCTION(SelfDestroyRenderable), asCALL_CDECL);
		// Register FindRenderable(uint16). Provides access to the renderable component of an Entity if it exists.
		r = scriptEngine->RegisterGlobalFunction("Sprite@ FindSprite(uint16)", asFUNCTION(FindRenderable), asCALL_CDECL); assert(r >= 0);
		// Register LoadNewTexture(Entity, std::string). Changes the texture a renderable of an entity displays with the texture at the given string location
		r = scriptEngine->RegisterGlobalFunction("void LoadSprite(uint16, string)", asFUNCTION(LoadNewTextureToEntity), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void LoadSprite(Sprite &, string)", asFUNCTION(LoadNewTextureToRenderable), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void FlipX(Sprite &)", asFUNCTION(FlipX), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void FlipY(Sprite &)", asFUNCTION(FlipY), asCALL_CDECL); assert(r >= 0);

	}

	static void RegisterScriptableObject(asIScriptEngine* scriptEngine)
	{
		int r;

		// Register ScriptableObject. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("ScriptableObject", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptableObject, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptableObject, release), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("ScriptableObject", asBEHAVE_GET_WEAKREF_FLAG, "int &f()", asMETHOD(ScriptableObject, getWeakRefereneFlag), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void setOwner(uint16 ownerEntity)", asMETHOD(ScriptableObject, setOwner), asCALL_THISCALL); assert(r >= 0);

		// Access the owning entity through the script. Note that getOwner() returns the entity id
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "uint16 getOwner()", asMETHOD(ScriptableObject, getOwner), asCALL_THISCALL); assert(r >= 0);

		// Kill the ScriptableObject. The alive flag is set to false and onEntityDestroyed() will be called by the ECS to destroy the object.
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void kill()", asMETHOD(ScriptableObject, kill), asCALL_THISCALL); assert(r >= 0);

		// The script can send a message to the other object through this method
		// The autohandle @+ to tell AngelScript to automatically release the handle after the call
		// The generic handle type is used to allow the script to pass any object to another script without the application having to know anything about it
		r = scriptEngine->RegisterObjectMethod("ScriptableObject", "void sendMessage(ref message, const ScriptableObject @+ to)", asMETHOD(ScriptableObject, sendMessage), asCALL_THISCALL); assert(r >= 0);
		
		// Register a method that will allow the script to find an object by its Tag.
		// The @+ that tells AngelScript to automatically increase the refcount of the returned object
		r = scriptEngine->RegisterGlobalFunction("ScriptableObject @+ FindObjectByTag(const string &in)", asFUNCTION(FindObjectByTag), asCALL_CDECL); assert(r >= 0);
	}

	static void RegisterInputHandler(asIScriptEngine* scriptEngine)
	{
		int r;

		// Register InputHandler function handles. Note that InputHandler provides only static functions which are registered as global functions.
		r = scriptEngine->RegisterGlobalFunction("bool IsKeyDown(uint)", asFUNCTION(IsKeyDown), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("bool IsMouseButtonDown(uint)", asFUNCTION(IsMouseButtonDown), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("float GetMouseX()", asFUNCTION(GetMouseX), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("float GetMouseY()", asFUNCTION(GetMouseY), asCALL_CDECL); assert(r >= 0);
	}

	static void RegisterCollision(asIScriptEngine* scriptEngine)
	{
		int r;
		// Register the Renderable component. The scripts cannot create these directly, so there is no factory function.
		r = scriptEngine->RegisterObjectType("Collidable", 0, asOBJ_REF); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Collidable", asBEHAVE_ADDREF, "void f()", asMETHOD(CollidableBox, addReference), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Collidable", asBEHAVE_RELEASE, "void f()", asMETHOD(CollidableBox, release), asCALL_THISCALL); assert(r >= 0);

		r = scriptEngine->RegisterObjectProperty("Collidable", "Vec2 centerPosition", asOFFSET(CollidableBox, centerPosition)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Collidable", "float rotation", asOFFSET(CollidableBox, rotation)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Collidable", "Vec2 halfScale", asOFFSET(CollidableBox, halfScale)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Collidable", "bool isTrigger", asOFFSET(CollidableBox, isTrigger)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Collidable", "Vec2 unitX", asOFFSET(CollidableBox, unitX)); assert(r >= 0);
		r = scriptEngine->RegisterObjectProperty("Collidable", "Vec2 unitY", asOFFSET(CollidableBox, unitY)); assert(r >= 0);

		r = scriptEngine->RegisterGlobalFunction("Collidable@ InitCollidable()", asFUNCTION(Collidable_Factory1), asCALL_CDECL); assert(r >= 0);

		r = scriptEngine->RegisterObjectMethod("Collidable", "Collidable &opAssign(const Collidable &in)",
			asMETHODPR(CollidableBox, operator=, (const CollidableBox &), CollidableBox &), asCALL_THISCALL); assert(r >= 0);
		r = scriptEngine->RegisterObjectBehaviour("Collidable", asBEHAVE_FACTORY, "Collidable@ f()", asFUNCTION(Collidable_Factory1), asCALL_CDECL); assert(r >= 0);

		// Destroy owned Collidable
		r = scriptEngine->RegisterGlobalFunction("void DestroyCollidable(uint16)", asFUNCTION(SelfDestroyCollidable), asCALL_CDECL);
		// Register FindRenderable(uint16). Provides access to the renderable component of an Entity if it exists.
		r = scriptEngine->RegisterGlobalFunction("Collidable@ FindCollidable(uint16)", asFUNCTION(FindCollidable), asCALL_CDECL); assert(r >= 0);
		// Register AreColliding functions. Checks for entity-entity and collidable-collidable and entity-collidable.
		r = scriptEngine->RegisterGlobalFunction("bool AreColliding(uint16, uint16)", asFUNCTION(AreEntitiesColliding), asCALL_CDECL);
		r = scriptEngine->RegisterGlobalFunction("bool IsColliding(uint16)", asFUNCTION(IsEntityColliding), asCALL_CDECL);
		// Flip the Transform of a scriptable object by 90/180/270 degrees
		r = scriptEngine->RegisterGlobalFunction("void Rotate90(Collidable &)", asFUNCTION(Rotate90Collidable), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void Rotate180(Collidable &)", asFUNCTION(Rotate180Collidable), asCALL_CDECL); assert(r >= 0);
		r = scriptEngine->RegisterGlobalFunction("void Rotate270(Collidable &)", asFUNCTION(Rotate270Collidable), asCALL_CDECL); assert(r >= 0);
	}
}