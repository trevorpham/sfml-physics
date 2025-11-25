add_executable(PhysicsSims 
"main.cpp"
"sim/BallWithinBoxCollision/BallWithinBoxCollision.cpp"
"sim/BouncingDVDLogo/BouncingDVDLogo.cpp"
 "main_helpers.cpp")

target_include_directories(PhysicsSims PRIVATE
	${CMAKE_SOURCE_DIR}/include
)

target_compile_features(PhysicsSims PRIVATE cxx_std_17)
target_link_libraries(PhysicsSims PRIVATE SFML::Graphics)

add_custom_command(TARGET PhysicsSims POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${ASSETS_DIR}
		$<TARGET_FILE_DIR:PhysicsSims>/assets
)