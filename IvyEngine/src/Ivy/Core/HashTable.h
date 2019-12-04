#pragma once

#include "Node.h"
#include "String.h"

namespace Ivy {

	template<typename K, typename V> class HashTable
	{
	private:
		Node<K, V>** table;
		uint32_t capacity;
		uint32_t size;
		uint32_t H = 1023;

		uint32_t currentKeyIndex;
		uint32_t currentValueIndex;

	public:
		/**
		* Default constructor;
		* Creates HashTable of capacity H
		*/
		HashTable()
		{
			this->capacity = H;
			this->size = 0;
			this->table = new Node<K, V>*[capacity];

			for (int i = 0; i < capacity; i++)
				table[i] = nullptr;
		}

		/**
		* Default destructor
		*/
		~HashTable()
		{
			for (int i = 0; i < this->capacity; i++)
			{
				Node<K, V>* node = this->table[i];
				while (node != nullptr)
				{
					Node<K, V>* previous = node;
					node = node->next;
					delete previous;
				}
			}
			delete[] this->table;
		}

		/**
		* Returns a hash code for a key using the division method
		* @param: K
		* @return: uint32_t
		*/
		uint32_t hashCode(K key)
		{
			return key % H;

			//multiplication
			//double fraction = (key*A) - ((long)(key*A));
			//return floor(this->capacity * fraction);
		}

		/**
		* Inserts a pair (key, value) into the the table
		* @param: K
		* @param: V
		*/
		void insert(K key, V value)
		{
			uint32_t hash = hashCode(key);

			if (table[hash] == nullptr)
				table[hash] = new Node<K, V>(key, value);
			else
			{
				Node<K, V>* node = table[hash];
				while (node->next != nullptr)
					node = node->next;
				node->next = new Node<K, V>(key, value);
			}
			this->size++;
		}

		/**
		* Removes a value associated with a key
		* @param: K
		* @return: bool; true if the value was removed and false otherwise
		*/
		bool removeKeyValue(K key, V value)
		{
			uint32_t hash = hashCode(key);

			Node<K, V>* aux = nullptr;
			Node<K, V>* node = table[hash];

			if (node != nullptr)
			{
				if (node->value == value)
				{
					aux = node->next;
					delete node;
					node = aux;
					size--;
					table[hash] = aux;
					return true;
				}

				while (node->next != nullptr && node->next->value != value)
					node = node->next;

				if (node->next != nullptr && node->next->value == value)
				{
					aux = node->next->next;
					delete node->next;
					node->next = aux;
					size--;
					return true;
				}
				else
					return false;
			}
			return false;
		}

		/*
		* Replaces the value at the given key with the new given value
		* @param: K
		* @param: V
		* @return: bool; true if the value was succesfully updated and false otherwse
		*/
		bool update(K key, V value, V newValue)
		{
			uint32_t hash = hashCode(key);

			Node<K, V>* node = table[hash];

			if (node != nullptr)
			{
				while (node != nullptr && node->value != value)
					node = node->next;

				if (node != nullptr && node->value == value)
				{
					node->value = newValue;
					return true;
				}
				else
					return false;
			}
			return false;
		}

		/**
		* Returns the value associated with the given key
		* @param: K
		* @throws: EntryNotFoundException if there are no entries with that key
		* @return: V
		*/
		V getValue(K key)
		{
			uint32_t hash = hashCode(key);

			Node<K, V>* node = table[hash];

			if (node != nullptr)
			{
				while ((node != nullptr && node->key != key) && (node->next != nullptr))
					node = node->next;

				if (node == NULL)
					return V{};

				return node->value;
			}
			else
				return V{};
		}

		K getKey(V value)
		{
			Node<K, V>* node = table[0];
			uint32_t counter = 0;

			while (counter < H)
			{
				while (node != NULL && node->value != value)
					node = node->next;

				if (node != NULL && node->value == value)
					return node->key;

				counter++;
				node = table[counter];
			}

			return K{};
		}

		/**
		* Returns the number of elements in the table
		* @return: uint32_t
		*/
		uint32_t getSize()
		{
			return size;
		}
	};
}