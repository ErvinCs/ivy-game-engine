call vendor\premake\premake\premake5.exe vs2017
del IvyEngine\vendor\angelscript\AngelScript.vcxproj 
del IvyEngine\vendor\angelscript\AngelScript.vcxproj.filters 
copy IvyEngine\vendor\angelscript\projects\msvc2017\AngelScript.vcxproj IvyEngine\vendor\angelscript
copy IvyEngine\vendor\angelscript\projects\msvc2017\AngelScript.vcxproj.filters IvyEngine\vendor\angelscript
PAUSE