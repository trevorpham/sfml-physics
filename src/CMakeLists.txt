add_executable(PhysicsSims 
"main.cpp"
"sim/SimulationRegistry.cpp"
"sim/BallWithinBoxCollision.cpp"
"sim/BouncingDVDLogo.cpp"
 "main_helpers.cpp")

target_include_directories(PhysicsSims PRIVATE
	${CMAKE_SOURCE_DIR}/include
)

target_compile_features(PhysicsSims PRIVATE cxx_std_17)
target_link_libraries(PhysicsSims PRIVATE SFML::Graphics)