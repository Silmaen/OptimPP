# Exclude particular files from the project
set(CTEST_CUSTOM_COVERAGE_EXCLUDE 
	${CTEST_CUSTOM_COVERAGE_EXCLUDE}
	".*/Test/.*"
	".*/Tools/.*"
	".*/doc/.*"
)
