#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Ivy 
{
	/*
	 *
	 */
	class RenderAPI
	{
	public:
		/**
		 *
		 */
		enum class API
		{
			None = 0, 
			OpenGL = 1
		};
	public:
		/**
		 *
		 */
		virtual void init() = 0;

		/**
		 *
		 */
		virtual void clear() = 0;

		/**
		 *
		 */
		virtual void setClearColor(const glm::vec4& color) = 0;

		/**
		 *
		 */
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/**
		 *
		 */
		virtual void draw(const std::shared_ptr<VertexArray>& va, uint32_t indexCount = 0) = 0;

		/**
		 *
		 */
		inline static API GetAPI() { return rAPI; }

		/**
		 *
		 */
		static std::unique_ptr<RenderAPI> Create();
	private:
		//
		static API rAPI;
	};

}