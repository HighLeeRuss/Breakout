SETLOCAL ENABLEEXTENSIONS
mkdir "%userprofile%\Documents\Visual Studio 2019\Templates\ItemTemplates"
mkdir "%userprofile%\Documents\Visual Studio 2019\Templates\ProjectTemplates"
copy ItemTemplates\*.* "%userprofile%\Documents\Visual Studio 2019\Templates\ItemTemplates"
copy ProjectTemplates\*.* "%userprofile%\Documents\Visual Studio 2019\Templates\ProjectTemplates"
pause
