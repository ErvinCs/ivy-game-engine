#pragma once

namespace Ivy 
{
	/**
	 * Base class for the render context implemented per render API.
	 */
	class Context
	{
	public:

		/**
		* Context initialization operations
		*/
		virtual void init() = 0;
		
		/**
		 * Buffer swapping operations.
		 */
		virtual void refresh() = 0;

		/**
		 * Creates a new render Context depending on the used render API
		 * @param window pointer to a window handle
		 * @returns unique_ptr<Context> pointing to the actual render Context
		 */
		static std::unique_ptr<Context> Create(void* window);
	};

}