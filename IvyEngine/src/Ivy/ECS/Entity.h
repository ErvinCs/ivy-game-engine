#pragma once

#include <stdint.h>
#include <map>

#include "Component.h"

#define Entity uint16_t

//namespace ivy {
//
//	class entity
//	{
//	private:
//		uint16_t entityid;
//		/*
//		std::map<uint8_t, std::shared_ptr<component>> componentrefs; // componentid to component mapping
//		*/
//
//	public:
//		entity() = default;
//		entity(const uint16_t& id) : entityid(id) {}
//		entity(const entity& other) { this->entityid = other.entityid; }
//		~entity() = default;
//		/*{
//			for (auto& pair : comprefs)
//			{
//				comprefs.erase(pair.second->getcomponentid());
//				delete pair.second;
//			}
//		}*/
//
//		inline const uint16_t getentityid() const {
//			return entityid;
//		}
//
//		/*inline void addcomponent(const std::shared_ptr<component>& component) {
//			componentrefs.insert(std::pair<uint8_t, std::shared_ptr<component>>(component->getcomponentid(), component));
//		}
//
//		inline void removecomponent(const std::shared_ptr<component>& component) {
//			componentrefs.erase(component->getcomponentid());
//		}*/
//
//		// ----- operators -----
//
//		bool operator==(const entity& other)
//		{
//			return this->entityid == other.getentityid();
//		}
//		bool operator!=(const entity& other)
//		{
//			return !(this->entityid == other.getentityid());
//		}
//
//		bool operator<(const entity& other)
//		{
//			return this->entityid < other.getentityid();
//		}
//
//		bool operator>(const entity& other)
//		{
//			return this->entityid > other.getentityid();
//		}
//
//		bool operator<=(const entity& other)
//		{
//			return this->entityid <= other.getentityid();
//		}
//
//		bool operator>=(const entity& other)
//		{
//			return this->entityid >= other.getentityid();
//		}
//	};
//}