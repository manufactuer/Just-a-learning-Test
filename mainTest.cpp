#ifndef __GL_WINDOW_H__
#define __GL_WINDOW H__

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

class GLWindow
{
public:
    GLWindow();

    bool Create(const char* window_title, const char *class_name,
                bool full_screen, HINSTANCE h_instance,
                LPVOID lpParam);

     void Destroy();
     bool ChangeScreenSetting();

     void ReshapeGL();

     void SwapBuffers(){::SwapBuffers(m_hDC);}

     void SetPosX(int x);
     void SetPosX(unsigned short x){SetPosX((signed short)x);}
     void SetPosY(int y);
     void SetPosY(unsigned short y){SetPosY((signed short)y);}

     int GetWidth();
     int GetHeight();

     void SetWidth(int width);
     void SetHeight(int height);

     int GetPosX();
     int GetPosY();

     void SetHiColor(){m_BitsPerPixel = 16;}
     void SetTrueColor(){m_BitsPerPixel = 32;}

     operator HWND(){return m_hWnd;}

private:
     HWND     m_hWnd;
     HDC      m_hDC;
     HGLRC    m_hRC;

     int      m_WindowPosX;
     int      m_WindowPosY;
     int      m_WindowWidth;
     int      m_WindowHeight;
     int      m_ScreenWidth;
     int      m_ScreenHeight;
     int      m_BitsPerPixel;
     bool     m_IsFullScreen;
};
#endif // __GL_WINDOW_H__

GLWindow::GLWindow()
{

        m_WindowPosX          =      0;
        m_WindowPosY          =      0;
        m_WindowWidth         =      800;
        m_WindowHeight        =      600;
        m_ScreenWidth         =      1152;
        m_ScreenHeight        =      864;
        m_BitsPerPixel        =      32;

        m_IsFullScreen        =      false;
        m_hWnd                =      0;
        m_hDC                 =      0;
        m_hRC                 =      0;

}

int GLWindow::GetWidth()
{
          if(m_IsFullScreen  ==   true)
          {
              return    m_ScreenWidth;
          }
          else
          {
              return    m_ScreenWidth;
          }
}

int GLWindow::GetHeight()
{
          if(m_IsFullScreen  ==    true)
          {
              return     m_ScreenHeight;
          }
          else
          {
              return     m_ScreenHeight;
          }
}

void GLWindow::SetWidth(int width)
{
          if(m_IsFullScreen     ==    true)
          {
              m_ScreenWidth     ==    width;
          }
          else
          {
              m_WindowWidth     ==   width;
          }
}

void GLWindow::SetHeight(int height)
{
          if(m_IsFullScreen     ==   true)
          {
              m_ScreenHeight    =     height;

          }
          else
          {
              m_ScreenHeight    =      height;
          }
}

int GLWindow::GetPosX()
{
          if(m_IsFullScreen    ==   false)
          {
              return      m_WindowPosX;
          }

          return 0;
}

int GLWindow::GetPosY()
{
          if(m_IsFullScreen    ==   false)
          {
              return      m_WindowPosY;
          }

          return 0;
}

void GLWindow::SetPosX(int x)
{
          if(m_IsFullScreen    ==     false)
          {
              m_WindowPosX    =   x;
          }
}

void GLWindow::SetPosY(int y)
{
          if(m_IsFullScreen    ==     false)
          {
              m_WindowPosY    =   y;
          }
}

void GLWindow::ReshapeGL()
{
            GLsizei  width    =   GetWidth();
            GLsizei  height   =   GetHeight();
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, (GLfloat)width / (GLfloat)height,
                           1.0f, 100.f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
}

bool GLWindow::ChangeScreenSetting()

{
           DEVMODE      dmScreenSettings;
           ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
           dmScreenSettings.dmSize     =     sizeof(DEVMODE);
           dmScreenSettings.dmPelsWidth =    GetWidth();
           dmScreenSettings.dmPelsHeight  =  GetHeight();
           dmScreenSettings.dmBitsPerPel   =    m_BitsPerPixel;

          // dmScreenSettings.dmDisplayFrequency  =  75;
           dmScreenSettings.dmFields     =  DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

           if(ChangeDisplaySettings(&dmScreenSettings, 0) !=  DISP_CHANGE_SUCCESSFUL)
           {

               return false;
           }

           return true;
}

bool GLWindow::Create(const char* window_title, const char* class_name,
                      bool fullscreen, HINSTANCE h_instance, LPVOID lpParam)

{
         m_IsFullScreen    =   fullscreen;
         int nX            =    0;
         int nY            =    0;
         PIXELFORMATDESCRIPTOR   pfd = {sizeof(PIXELFORMATDESCRIPTOR),
                                        1,
                                        PFD_DRAW_TO_WINDOW |
                                        PFD_SUPPORT_OPENGL |
                                        PFD_STEREO         |
                                        PFD_DOUBLEBUFFER,
                                        PFD_TYPE_RGBA,
                                        m_BitsPerPixel,
                                        0, 0, 0, 0, 0, 0,
                                        0,
                                        0,
                                        0,
                                        0, 0, 0, 0,
                                        32,
                                        0,
                                        0,
                                        PFD_MAIN_PLANE,
                                        0,
                                        0, 0, 0};

          DWORD         windowStyle            =     WS_OVERLAPPEDWINDOW &
                                       ~WS_SIZEBOX   &  ~WS_MAXIMIZEBOX;
          DWORD         windowExtendedStyle    =  WS_EX_APPWINDOW;

          if(m_IsFullScreen   ==   true)
          {
              if(ChangeScreenSetting() == false)
              {
                  MessageBox(HWND_DESKTOP, "Mode switch failure\nExcute on Window？",
                             "Error", MB_OK | MB_ICONEXCLAMATION);
                  m_IsFullScreen     =   false;
              }

              else
              {

                  ShowCursor(false);
                  windowStyle   =    WS_POPUP;
                  windowExtendedStyle   =   WS_EX_TOPMOST;
              }
          }

          RECT   windowRect   =  {GetPosX(), GetPosY(), GetPosX()+GetWidth(),
                                   GetPosY()+GetHeight()};
          if(m_IsFullScreen   ==   false)
          {
              windowExtendedStyle   =    WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
              int wid               =   GetSystemMetrics(SM_CXSCREEN);
              int hei               =   GetSystemMetrics(SM_CYSCREEN);
              nX   =  (wid - GetWidth())/2;
              nY   =  (hei - GetHeight())/2;

              AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);

              if(windowRect.left < 0)
              {
                  windowRect.right -=  windowRect.left;
                  windowRect.left   =  0;
              }

              if(windowRect.top <0)
              {
                  windowRect.bottom -=  windowRect.top;
                  windowRect.top    = 0;
              }
          }

          m_hWnd  =  CreateWindowEx(windowExtendedStyle,
                                    class_name,
                                    window_title,
                                    windowStyle,
                                    nX, nY,
                                    windowRect.right - windowRect.left,
                                    windowRect.bottom - windowRect.top,
                                    HWND_DESKTOP,
                                    0,
                                    h_instance,
                                    lpParam);


         while(m_hWnd    !=   0)
         {
             m_hDC    =    GetDC(m_hWnd);
             if(m_hDC    ==    0)
             {
                 break;
             }

             GLuint        PixelFormat   =   ChoosePixelFormat(m_hDC, &pfd);
             if(PixelFormat    ==  0)
             {
                 break;
             }
             if(SetPixelFormat(m_hDC, PixelFormat, &pfd)  ==   false)
             {
                 break;
             }

              m_hRC    =   wglCreateContext(m_hDC);
              if(m_hRC   ==   0)
              {
                  break;
              }

              if(wglMakeCurrent(m_hDC, m_hRC) == false)
              {
                  break;
              }

              ShowWindow(m_hWnd, SW_NORMAL);
              ReshapeGL();

              return true;

         }

         Destroy();
         return true;
}

void GLWindow::Destroy()
{
         if(m_hWnd   !=  0)
         {
             if(m_hDC !=   0)
             {
                 wglMakeCurrent(m_hDC, 0);
                 if(m_hRC  !=  0)
                 {
                     wglDeleteContext(m_hRC);
                     m_hRC   =   0;
                 }

                 ReleaseDC(m_hWnd, m_hDC);
                 m_hDC   =  0;
             }

             DestroyWindow(m_hWnd);
             m_hWnd  =  0;
         }

         if(m_IsFullScreen)
         {
             ChangeDisplaySettings(NULL, 0);
             ShowCursor(true);
         }


}

class Keys
{
public:
    Keys(){Clear();}
    void Clear(){ZeroMemory(&m_KeyDown, sizeof(m_KeyDown));}
    bool IsPressed(unsigned int key){return (key<MAX_KEYS)?(m_KeyDown[key] == true):false;}

    void SetPressed(unsigned int key){if(key<MAX_KEYS)
                                       m_KeyDown[key] =  true;}
    void SetReleased(unsigned int key){if(key<MAX_KEYS)
                                      m_KeyDown[key] = false;}


private:
    static const unsigned int MAX_KEYS = 256;
    bool m_KeyDown[MAX_KEYS];
};


class GLApplication
{

public:
    static GLApplication * Create(const char*class_name);
    virtual ~GLApplication(){};

protected:
    virtual bool Init() = 0;
    virtual void UnInit() = 0;
    virtual void Update(DWORD milliseconds) = 0;
    virtual void Draw() = 0;


    void ToggleFullscreen();
    void TerminateApplication();
    void ResizeDraw(bool enable){m_ResizeDraw = enable;}

    Keys      m_Keys;
    GLApplication(const char*class_name);

private:
    friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE
                              hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLind,
              int nCmdShow);
    friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam);
    LRESULT Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static const UINT WM_TOGGLEFULLSCREEN = (WM_USER + 1);

    GLWindow   m_Window;
    const char* m_ClassName;
    bool m_IsProgramLooping;

    bool m_CreateFullScreen;
    bool m_IsVisible;
    bool m_ResizeDraw;
    DWORD m_LastTickCount;
};


GLApplication::GLApplication(const char* class_name)
{
       m_ClassName         =     class_name;
       m_IsProgramLooping  =     true;
       m_CreateFullScreen  =     true;
       m_IsVisible         =     false;
       m_ResizeDraw        =     false;
       m_LastTickCount     =     0;
}


void GLApplication::ToggleFullscreen()
{
    PostMessage(m_Window, WM_TOGGLEFULLSCREEN, 0, 0);
}

void GLApplication::TerminateApplication()
{
      PostMessage(m_Window, WM_QUIT, 0, 0);
      m_IsProgramLooping       =    false;
}


LRESULT     GLApplication::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

         switch(uMsg)
         {
                 case WM_SYSCOMMAND:
                       switch(wParam)
                       {
                          case SC_SCREENSAVE:
                          case SC_MONITORPOWER:
                            return 0;
                            break;
                       }
                       break;
                 case WM_CLOSE:
                     TerminateApplication();
                     return 0;
                     break;
                 case WM_EXITMENULOOP:
                 case WM_EXITSIZEMOVE:
                    m_LastTickCount = GetTickCount();
                    return 0;
                    break;
                 case WM_MOVE:
                    m_Window.SetPosX(LOWORD(lParam));
                    m_Window.SetPosY(HIWORD(lParam));

                    return 0;
                    break;

                 case WM_PAINT:
                    if(m_ResizeDraw    ==  true)
                    {
                        m_Window.ReshapeGL();
                        Draw();
                        m_Window.SwapBuffers();
                    }
                    break;

                 case WM_SIZING:
                    {
                        RECT   *rect  =  (RECT*)lParam;
                        m_Window.SetWidth(rect->right - rect->left);
                        m_Window.SetHeight(rect->bottom - rect->top);

                        return TRUE;
                    }

                    break;

                 case WM_SIZE:
                       switch(wParam)
                       {
                           case SIZE_MINIMIZED:
                               m_IsVisible   =   false;
                               return 0;
                               break;

                           case SIZE_MAXIMIZED:
                           case SIZE_RESTORED:
                                m_IsVisible   =  true;
                                m_Window.SetWidth(LOWORD(lParam));

                                m_Window.SetHeight(HIWORD(lParam));
                                m_Window.ReshapeGL();
                                m_LastTickCount = GetTickCount();

                                return 0;

                                break;
                       }
                       break;

                  case WM_KEYDOWN:
                          m_Keys.SetPressed(wParam);
                          return 0;
                          break;
                  case WM_KEYUP:
                          m_Keys.SetReleased(wParam);
                          return 0;
                          break;
                  case WM_TOGGLEFULLSCREEN:
                          m_CreateFullScreen =  !m_CreateFullScreen;
                          PostMessage(hWnd, WM_QUIT, 0, 0);
                          break;

         }

         return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/*#include<windows.h>
 int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance, LPSTR lpCmdLine,int nCmdShow)
{
 MessageBox(NULL,"Temprorary","NAIVE US",MB_OK);
 return 0;
}*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
            int ret = -1;
            GLApplication * app1 = GLApplication::Create("OpenGL");
         //while(!true)
         //{


            if(app1 != 0)
            {

                ret = app1->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

                delete app1;
            }

            else
            {
                MessageBox(HWND_DESKTOP, "Bulid program Failure", "Error", MB_OK |
                                                         MB_ICONEXCLAMATION);

            }

            return  ret;
        // }

        // MessageBox(NULL,"So So hu...hu...！","NAIVE ME",MB_OK);
        // return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
         LONG     user_data   =  GetWindowLong(hWnd, GWL_USERDATA);

         if(user_data  ==  0)
         {
             if(uMsg  ==  WM_CREATE)
             {
                 CREATESTRUCT *createion = reinterpret_cast<CREATESTRUCT*>(lParam);

                 GLApplication *app1 = reinterpret_cast<GLApplication*>
                                          (createion->lpCreateParams);

                 SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(app1));

                               app1->m_IsVisible    =    true;

                 return 0;
             }
         }

         else
         {
             GLApplication *app1 = reinterpret_cast<GLApplication*>(user_data);

             return app1->Message(hWnd, uMsg, wParam, lParam);

         }

         return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

int GLApplication::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
           WNDCLASSEX      windowClass;
           ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
           windowClass.cbSize  =    sizeof(WNDCLASSEX);
           windowClass.style   =    CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
           windowClass.lpfnWndProc = (WNDPROC)(WindowProc);
           windowClass.hInstance    =   hInstance;
           windowClass.hbrBackground =  (HBRUSH)(COLOR_APPWORKSPACE);
           windowClass.hCursor      =   LoadCursor(NULL, IDC_ARROW);
           windowClass.lpszClassName  =   m_ClassName;

           if(RegisterClassEx(&windowClass)   ==  0)
           {
               MessageBox(HWND_DESKTOP, "Register Windows Failure！", "ERROR", MB_OK | MB_ICONEXCLAMATION);


               return -1;
           }

           if(MessageBox(HWND_DESKTOP, "Fullscreen？", "Yes or no？",
                            MB_YESNO | MB_ICONQUESTION == IDNO))
           {
                    m_CreateFullScreen = false;
           }

           /*while(m_IsProgramLooping)
           {
               if(m_Window.Create("OOGLTest", m_CreateFullScreen,
                                  m_ClassName, hInstance, this)  ==  true)
               {
                        if(Init() == false)
                            {
                                TerminateApplication();
                            }

                            else
                            {
                                Msg msg;
                                bool isMessagePumpActive =  true;
                            }
               }
           }*/

           while(m_IsProgramLooping)
           {
               if(m_Window.Create("Just tired of this!Boring!", m_ClassName,
                                  m_CreateFullScreen, hInstance, this)
                                   ==   true)
               {
                   if(Init()  ==  false)
                   {
                       TerminateApplication();
                   }
                   else
               {
                   MSG              msg;
                   bool             isMessagePumpActive  =  true;

                   m_LastTickCount    =  GetTickCount();
                   m_Keys.Clear();

                   while(isMessagePumpActive  ==  true)
                   {
                       if(PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
                         {
                             if(msg.message  !=  WM_QUIT)
                             {
                                 DispatchMessage(&msg);
                             }

                             else
                             {
                                 isMessagePumpActive  =  false;
                             }
                         }


                         else
                         {
                             if(m_IsVisible   ==   false)
                             {
                                 WaitMessage();
                             }

                             else
                             {
                                 DWORD tickCount    =   GetTickCount();
                                 Update(tickCount - m_LastTickCount);
                                 m_LastTickCount = tickCount;
                                 Draw();

                                 m_Window.SwapBuffers();
                             }
                         }
                   }
               }

               UnInit();
               m_Window.Destroy();


            }


           else
              {
               MessageBox(HWND_DESKTOP, "Get window Error", "Error", MB_OK|
                                                        MB_ICONEXCLAMATION);
               m_IsProgramLooping = false;
              }
        }

        UnregisterClass(m_ClassName, hInstance);

        return 0;
}


class Example:GLApplication
{
public:
    bool Init();
    void UnInit();
    void Update(DWORD milliseconds);
    void Draw();

private:
    friend class GLApplication;
    Example(const char* class_name);

    float m_Angle;
};



GLApplication *GLApplication::Create(const char * class_name)
{
        Example *example  =  new Example(class_name);
        return reinterpret_cast<GLApplication*>(example);
}


Example::Example(const char *class_name):GLApplication(class_name)
{
        m_Angle    =   0.0f;
}

bool Example::Init()
{
         glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
         glClearDepth(1.0f);
         glDepthFunc(GL_LEQUAL);
         glEnable(GL_DEPTH_TEST);
         glShadeModel(GL_SMOOTH);
         glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
         ResizeDraw(true);

         return true;
}

void Example::UnInit()
{


}

void Example::Update(DWORD milliseconds)
{
    if(m_Keys.IsPressed(VK_ESCAPE) == true)
    {
        TerminateApplication();
    }
    if(m_Keys.IsPressed(VK_F1) == true)
    {
        ToggleFullscreen();
    }

    m_Angle +=  (float)(milliseconds)  / 15.0f;
}


void Example::Draw()
{
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            glTranslatef(0.0f, 0.0f, -6.0f);
            glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);

            for(int rot1 = 0; rot1<2; rot1++)
            {
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                for(int rot2 = 0; rot2<2; rot2++)
                {
                    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                    glBegin(GL_TRIANGLES);
                           glColor3f(1.0f, 0.0f, 0.0f);
                           glVertex3f(0.0f, 1.0f, 0.f);
                           glColor3f(0.0f, 1.0f, 0.0f);
                           glVertex3f(-1.0f, -1.0f, 1.0f);
                           glColor3f(0.0f, 0.0f, 1.0f);
                           glVertex3f(1.0f, -1.0f, 1.0f);
                    glEnd();

                }
            }
           // cout<<"Loop timing?"<<endl;

            glFlush();
}

/*Learing frome Book*/
