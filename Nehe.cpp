#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>

HGLRC hRC = NULL;
HDC hDC = NULL;
HWND hWnd = NULL;
HINSTANCE hInstance;

bool keys[256];
bool active = true;
bool fullscreen = true;

GLfloat rtri;
GLfloat rquad;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) {
	if (height == 0)height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int InitGL(GLvoid) {
	glShadeModel(GL_SMOOTH);

	glClearColor(0, 0, 0, 0);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

int DrawGLScene(GLvoid) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	glTranslatef(-1.5, 0, -7);
	glRotatef(rtri, 0, 1, 0);

	glBegin(GL_TRIANGLES);                      // Drawing Using Triangles

	glColor3f(1.0f, 0.0f, 0.0f);          // Red
	glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
	glColor3f(0.0f, 1.0f, 0.0f);          // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Left Of Triangle (Front)
	glColor3f(0.0f, 0.0f, 1.0f);          // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);          // Right Of Triangle (Front)

	glColor3f(1.0f, 0.0f, 0.0f);          // Red
	glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
	glColor3f(0.0f, 0.0f, 1.0f);          // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);          // Left Of Triangle (Right)
	glColor3f(0.0f, 1.0f, 0.0f);          // Green
	glVertex3f(1.0f, -1.0f, -1.0f);         // Right Of Triangle (Right)

	glColor3f(1.0f, 0.0f, 0.0f);          // Red
	glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
	glColor3f(0.0f, 1.0f, 0.0f);          // Green
	glVertex3f(1.0f, -1.0f, -1.0f);         // Left Of Triangle (Back)
	glColor3f(0.0f, 0.0f, 1.0f);          // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);         // Right Of Triangle (Back)

	glColor3f(1.0f, 0.0f, 0.0f);          // Red
	glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
	glColor3f(0.0f, 0.0f, 1.0f);          // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Left Of Triangle (Left)
	glColor3f(0.0f, 1.0f, 0.0f);          // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Right Of Triangle (Left)

	glEnd();


	glRotatef(-rtri, 0, 1, 0);
	glTranslatef(3, 0, 0);
	glRotatef(rquad, 1, 1, 1);

	glBegin(GL_QUADS);                      // Draw A Quad

	glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Green
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
	glVertex3f(1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)

	glColor3f(1.0f, 0.5f, 0.0f);          // Set The Color To Orange
	glVertex3f(1.0f, -1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Bottom)
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Bottom)

	glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
	glVertex3f(1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
	glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Front)

	glColor3f(1.0f, 1.0f, 0.0f);          // Set The Color To Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Back)
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Back)

	glColor3f(0.0f, 0.0f, 1.0f);          // Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Left)

	glColor3f(1.0f, 0.0f, 1.0f);          // Set The Color To Violet
	glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Right)

	glEnd();


	rtri += 0.2;
	rquad += 0.15f;


	return TRUE;

}

int KillGLWindow(GLvoid) {
	if (fullscreen) {
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if (hRC) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL, "Release of DC and RC failed", "Shutdown Error", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, "Release REndering Context Failed", "Shutdown Error", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}
	if (hDC&&!ReleaseDC(hWnd, hDC)) {
		MessageBox(NULL, "Release Device Context Failed", "Shutdown Error", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	if (hWnd&&!DestroyWindow(hWnd)) {
		MessageBox(NULL, "Could not Release hWnd", "Shutdow Error", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}
	if (!UnregisterClass("OpenGL", hInstance)) {
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
	return TRUE;
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag) {
	GLuint PixelFormat;
	WNDCLASS wc;

	DWORD       dwExStyle;
	DWORD       dwStyle;

	RECT WindowRect;                            // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;                        // Set Left Value To 0
	WindowRect.right = (long)width;                       // Set Right Value To Requested Width
	WindowRect.top = (long)0;                         // Set Top Value To 0
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;                // WndProc Handles Messages
	wc.cbClsExtra = 0;                        // No Extra Window Data
	wc.cbWndExtra = 0;                        // No Extra Window Data
	wc.hInstance = hInstance;                    // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
	wc.hbrBackground = NULL;                     // No Background Required For GL
	wc.lpszMenuName = NULL;                     // We Don't Want A Menu
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc))                        // Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Exit And Return FALSE
	}

	if (fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPanningHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH | DM_BITSPERPEL;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				fullscreen = false;
			}
			else {
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	if (!(hWnd = CreateWindowEx(dwExStyle,              // Extended Style For The Window
		"OpenGL",               // Class Name
		title,                  // Window Title
		WS_CLIPSIBLINGS |           // Required Window Style
		WS_CLIPCHILDREN |           // Required Window Style
		dwStyle,                // Selected Window Style
		0, 0,                   // Window Position
		WindowRect.right - WindowRect.left,   // Calculate Adjusted Window Width
		WindowRect.bottom - WindowRect.top,   // Calculate Adjusted Window Height
		NULL,                   // No Parent Window
		NULL,                   // No Menu
		hInstance,              // Instance
		NULL)))                 // Don't Pass Anything To WM_CREATE
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static  PIXELFORMATDESCRIPTOR pfd =                  // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
		1,                              // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
		PFD_TYPE_RGBA,                          // Request An RGBA Format
		bits,                               // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                       // Color Bits Ignored
		0,                              // No Alpha Buffer
		0,                              // Shift Bit Ignored
		0,                              // No Accumulation Buffer
		0, 0, 0, 0,                         // Accumulation Bits Ignored
		16,                             // 16Bit Z-Buffer (Depth Buffer)
		0,                              // No Stencil Buffer
		0,                              // No Auxiliary Buffer
		PFD_MAIN_PLANE,                         // Main Drawing Layer
		0,                              // Reserved
		0, 0, 0                             // Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))             // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))               // Are We Able To Set The Pixel Format?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))                   // Are We Able To Get A Rendering Context?
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))                        // Try To Activate The Rendering Context
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}


	ShowWindow(hWnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(hWnd);                      // Slightly Higher Priority
	SetFocus(hWnd);                             // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);

	if (!InitGL())                              // Initialize Our Newly Created GL Window
	{
		KillGLWindow();                         // Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                           // Return FALSE
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND    hWnd,                   // Handle For This Window
	UINT    uMsg,                   // Message For This Window
	WPARAM  wParam,                 // Additional Message Information
	LPARAM  lParam)                 // Additional Message Information
{
	switch (uMsg) {
	case WM_ACTIVATE:
	{
		if (!HIWORD(wParam))
			active = TRUE;
		else active = FALSE;
		return 0;
	}
	case WM_SYSCOMMAND:                     // Intercept System Commands
	{
		switch (wParam)                     // Check System Calls
		{
		case SC_SCREENSAVE:             // Screensaver Trying To Start?
		case SC_MONITORPOWER:               // Monitor Trying To Enter Powersave?
			return 0;                   // Prevent From Happening
		}
		break;                          // Exit
	}
	case WM_CLOSE:                          // Did We Receive A Close Message?
	{
		PostQuitMessage(0);                 // Send A Quit Message
		return 0;                       // Jump Back
	}
	case WM_KEYDOWN:                        // Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;                    // If So, Mark It As TRUE
		return 0;                       // Jump Back
	}
	case WM_KEYUP:                          // Has A Key Been Released?
	{
		keys[wParam] = FALSE;                   // If So, Mark It As FALSE
		return 0;                       // Jump Back
	}
	case WM_SIZE:                           // Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));       // LoWord=Width, HiWord=Height
		return 0;                       // Jump Back
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE   hInstance,              // Instance
	HINSTANCE   hPrevInstance,              // Previous Instance
	LPSTR       lpCmdLine,              // Command Line Parameters
	int     nCmdShow)               // Window Show State
{
	MSG msg;
	BOOL done = FALSE;

	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;                       // Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
	{
		return 0;                           // Quit If Window Was Not Created
	}

	while (!done) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				done = true;
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			if (active) {
				if (keys[VK_ESCAPE]) 
					done = true;
				else {
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			if (keys[VK_F1]) {
				keys[VK_F1] = FALSE;              // If So Make Key FALSE
				KillGLWindow();                 // Kill Our Current Window
				fullscreen = !fullscreen;             // Toggle Fullscreen / Windowed Mode
													  // Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
				{
					return 0;               // Quit If Window Was Not Created
				}
			}
		}
	}
	KillGLWindow();
	return msg.wParam;
}

