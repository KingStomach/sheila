#pragma once

#ifndef MACRO_H
#define MACRO_H

#ifdef SHEILA_BUILD
#define SHEILA_API __declspec(dllexport)
#else
#define SHEILA_API __declspec(dllimport)
#endif  // SHEILA_BUILD

#ifdef SHEILA_ENABLE_TEST

#ifdef SHEILA_BUILD
#define SHEILA_TEST_API __declspec(dllexport)
#elif SHEILA_TEST_BUILD
#define SHEILA_TEST_API __declspec(dllimport)
#else
#define SHEILA_TEST_API
#endif

#else
#define SHEILA_TEST_API
#endif

#ifdef SHEILA_ENABLE_TEST
#define SHEILA_TEST_EXPORT export
#else
#define SHEILA_TEST_EXPORT
#endif

#define NOVTABLE __declspec(novtable)
#endif  // SHEILA_H