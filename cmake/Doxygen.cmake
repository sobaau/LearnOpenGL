function(enable_doxygen)
  option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
  if(ENABLE_DOXYGEN)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXCLUDE_PATTERNS
        */docs/*
        *.md
        *.markdown
        */contrib/*
        */dependencies/sdl/*
        */scripts/*
        */samples/*
        */examples/*
        */test/*
        */tests/*
        */doc/*
        */docs/*
        */deps/*
        */build/*
        */_build/*
        */cmake/*
        */cmake-build*/*
        */util/*
        Makefile
        *.txt
        *.yml
        *.github
        */cmake-modules/*
        */assimp/*)
    set(DOXYGEN_INCLUDE_FILE_PATTERNS
        *.cpp
        *.c
        *.h
        *.hpp
        *.inl
        *.
        *.
        *.
        *.)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(doxygen ${PROJECT_SOURCE_DIR})

  endif()
endfunction()
