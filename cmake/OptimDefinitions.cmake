
if (WIN32)
	add_compile_definitions(
		UNICODE
		NOMINMAX # Prevent Windows from defining its min & max macros, which generates conflicts
	)
endif ()

if (MSVC)
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

