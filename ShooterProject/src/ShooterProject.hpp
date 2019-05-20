// ShooterProject.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// stdlib
#include <iostream>

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// internal
#include "common.hpp"
#include "world.hpp"
#include "effect.hpp"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
