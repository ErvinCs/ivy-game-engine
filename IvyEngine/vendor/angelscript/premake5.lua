project "AngelScript"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir   ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/angelscript.h",
        "source/**.h",
        "source/**.cpp",
        "add_on/**.h",
        "add_on/**.cpp"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        --buildcommands {
        --    'ml64.exe /c  /nologo /Fo$(OutDir)\\as_callfunc_x64_msvc_asm.obj /W3 /Zi /Ta $(InputDir)\\$(InputFileName)'
        --}
    --[[
    If the project does not build properly add the following to AngelScript.vcxproj
    <ItemGroup>
    <CustomBuild Include="source\as_callfunc_x64_msvc_asm.asm">
      <FileType>Document</FileType>
      <Command Condition="'$(Configuration)|$(Platform)'=='Release|x64'">ml64.exe /c  /nologo /Fo"$(Configuration)\as_callfunc_x64_msvc_asm.obj" /W3 /Zi /Ta "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|x64'">$(Configuration)\as_callfunc_x64_msvc_asm.obj;%(Outputs)</Outputs>
      <Command Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">ml64.exe /c  /nologo /Fo"$(Configuration)\as_callfunc_x64_msvc_asm.obj" /W3 /Zi /Ta "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Command Condition="'$(Configuration)|$(Platform)'=='clang_debug|x64'">ml64.exe /c  /nologo /Fo"$(Configuration)\as_callfunc_x64_msvc_asm.obj" /W3 /Zi /Ta "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">$(Configuration)\as_callfunc_x64_msvc_asm.obj;%(Outputs)</Outputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='clang_debug|x64'">$(Configuration)\as_callfunc_x64_msvc_asm.obj;%(Outputs)</Outputs>
    </CustomBuild>
  </ItemGroup>
  <ItemGroup>
    <None Include="source\as_callfunc_arm_gcc.S" />
    <CustomBuild Include="source\as_callfunc_arm_msvc.asm">
      <FileType>Document</FileType>
      <Command Condition="'$(Configuration)|$(Platform)'=='Debug|ARM'">armasm.exe -g -32 -o "$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj" "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Command Condition="'$(Configuration)|$(Platform)'=='clang_debug|ARM'">armasm.exe -g -32 -o "$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj" "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|ARM'">$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj;%(Outputs)</Outputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='clang_debug|ARM'">$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj;%(Outputs)</Outputs>
      <Command Condition="'$(Configuration)|$(Platform)'=='Release|ARM'">armasm.exe -32 -o "$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj" "%(RootDir)%(Directory)\%(Filename)%(Extension)"</Command>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|ARM'">$(Platform)\$(Configuration)\as_callfunc_arm_msvc.obj;%(Outputs)</Outputs>
    </CustomBuild>
    <None Include="source\as_callfunc_arm_vita.S" />
    <None Include="source\as_callfunc_arm_xcode.S" />
  </ItemGroup>
    --]]

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
