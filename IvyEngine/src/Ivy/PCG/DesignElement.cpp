#include "ivypch.h"

#include "DesignElement.h"

namespace Ivy
{
	int DesignElement::TagCounter = 0;

	DesignElement::DesignElement(const DesignElement& other)
	{
		this->transform = other.transform;
		this->tag = other.tag;
		this->elementType = other.elementType;
	}
	DesignElement::DesignElement(const DesignElement&& other)
	{
		this->transform = std::move(other.transform);
		this->tag = std::move(other.tag);
		this->elementType = std::move(other.elementType);
	}
	DesignElement::DesignElement(Tag tag, Transform transform)
	{
		this->tag = tag;
		this->transform = transform;
	}
}