#pragma once

#include <stdint.h>

// An entity is a unique identifier
#define Entity uint16_t

// The maximum number of  entities supported by the application.
// Determines the size of ComponentContainers
#define MAX_Entities 200

// The maximum number of component types supported by the application.
// Note that for each component type a new array will be allocated
// @see ComponentContainer
#define MAX_Components 100