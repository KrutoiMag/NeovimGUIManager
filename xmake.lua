set_languages("c++23")

target("NeovimGUIManager")
do
    add_files("main.cpp","SourceFiles/rlImGui/*.cpp","SourceFiles/imgui/*.cpp", "SourceFiles/imgui/misc/*.cpp")
    add_includedirs("HeaderFiles","HeaderFiles/rlImGui")
    add_links("raylib")
end