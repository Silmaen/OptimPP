
if (WIN32)
	add_compile_definitions(
		UNICODE
		NOMINMAX # Prevent Windows from defining its min & max macros, which generates conflicts
	)
endif ()

if (OPP_COMPILER_MSVC)
	add_compile_definitions(
		# Prevent MSVC from emitting warnings when using deprecated CRT functions
		_CRT_SECURE_NO_WARNINGS

		# Removes warnings concerning std::[w]string_convert, deprecated in C++17 (RshString)
		_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

		# Removes warnings concerning std::iterator<T> specializations, deprecated in C++17 (TBBHelper)
		_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

		# Removes warnings concerning std::uncaught_exception, deprecated in C++17 (tbb/task_group)
		_SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING
	)
endif ()

if (NOT OPP_COMPILER_MSVC)
	# add this flag required for TBB on Linux with gcc > c+11
	#add_compile_definitions(__GXX_EXPERIMENTAL_CXX0X__)
	#add_compile_options(-Wno-deprecated-declarations)
else ()
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif ()

# add this flag to set the test files
add_compile_definitions(ROOT_TEST_FILE_PATH="${OPTIM_ROOT_DIR}")
