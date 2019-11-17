#pragma once

namespace Ivy {

	template <typename K, typename V> class Node
	{
	public:
		K key;
		V value;
		Node* next;

		/**
		* Default constructor
		* Initialize all the fields with nullptr
		*/
		Node()
		{
			this->key = nullptr;
			this->value = nullptr;
			this->next = nullptr;
		}

		/**
		* Initialize all the fields
		*/
		Node(K key, V value, Node* node)
		{
			this->key = key;
			this->value = value;
			this->next = node;
		}

		/**
		* Initialize key & value
		* Node* next = nullptr
		*/
		Node(K key, V value)
		{
			this->key = key;
			this->value = value;
			this->next = nullptr;
		}

		/**
		* Copy constructor
		*/
		Node(Node& other)
		{
			this->key = other.key;
			this->value = other.value;
			this->next = other.next;
		}
	};

}