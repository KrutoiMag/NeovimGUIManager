set_languages("c++23")

target("NeovimGUIManager")
do
    add_files("SourceFiles/NeovimGUIManager/*.cpp","SourceFiles/rlImGui/*.cpp","SourceFiles/imgui/*.cpp", "SourceFiles/imgui/misc/*.cpp", "SourceFiles/NeovimGUIManager/GUI/*.cpp")
    add_includedirs("HeaderFiles","HeaderFiles/rlImGui")
    add_links("raylib")
end