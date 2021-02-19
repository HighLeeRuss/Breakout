#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "XInput9_1_0.lib")
#pragma comment(lib, "opengl32.lib")
#ifdef _DEBUG
	#pragma comment(lib, "sfml-system-d.lib")
	#pragma comment(lib, "sfml-window-d.lib")
	#pragma comment(lib, "sfml-graphics-d.lib")
	#pragma comment(lib, "sfml-audio-d.lib")
	#pragma comment(lib, "sfml-network-d.lib")
	#pragma comment(lib, "kage_d.lib")
#else
	#pragma comment(lib, "sfml-system.lib")
	#pragma comment(lib, "sfml-window.lib")
	#pragma comment(lib, "sfml-graphics.lib")
	#pragma comment(lib, "sfml-audio.lib")
	#pragma comment(lib, "sfml-network.lib")
	#pragma comment(lib, "kage.lib")
#endif

