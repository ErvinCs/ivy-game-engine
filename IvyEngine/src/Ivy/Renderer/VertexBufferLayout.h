#pragma once

// Needed by the VertexArray & its children

namespace Ivy 
{
	/**
	 * Enumeration used to determine data types used in a shader and their sizes in number of bytes.
	 */
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	/**
	 * @returns unit32_t the number of bytes used by a data type in a shader
	 */
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		return 0;	//Unknown ShaderDataType
	}

	/**
	 * An element in the VertexBuffer.
	 * Encapsulates its name, type, size and offset
	 * @see VertexBuffer
	 * @see ShaderDataType
	 */
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		// Default Constructor
		BufferElement() = default;

		/**
		 * Construct a buffer element.
		 * @param type ShaderDataType
		 * @param string name
		 * @param bool normalized
		 */
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		/**
		 * @returns uint32_t equal to the number of elements in a shader data type
		 */
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			return 0;	//Unknown ShaderDataType
		}
	};

	/**
	 * Used to determine the layout of an associated VertexBuffer.
	 * @see VertexBuffer
	 */
	class VertexBufferLayout
	{
	public:
		// Default Constructor
		VertexBufferLayout() {}

		/**
		 * Stores the elements and calculates their offsets
		 */
		VertexBufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		/**
		 * @returns uint32_t stride
		 */
		inline uint32_t GetStride() const { return stride; }

		/**
		 * @retturns vector<BufferElement> elements of the buffer
		 */
		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
	private:

		/**
		 * Calculate the offset and stride of each element in the VertexBuffer
		 */
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.Offset = offset;
				offset += element.Size;
				stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

}