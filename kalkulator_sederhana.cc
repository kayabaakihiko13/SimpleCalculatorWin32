#include <windows.h>
#include <stdio.h>

#define windowClassName "myWindowClass"
#define IDC_EDIT 800

int typing = 0;
BOOL final=0;
long double num1=0.0;
long double num2=0.0;
int op=0;
BOOL shift=0;

long double getScreen(HWND hwnd){
  int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT));
  char buf[32];
  if (len>0) {
    GetDlgItemText(hwnd, IDC_EDIT, buf, len+1);
    return strtold(buf,NULL);
  }
  return 0.0;
};

void equate(HWND hwnd){
  switch (op) {
    case 110: num1 += num2; break;
    case 111: num1 -= num2; break;
    case 112: num1 *= num2; break;
    case 113: num1 /= num2; break;
  }
  char buf[32];
  sprintf(buf,"%.16Lg",num1);
  SetDlgItemText(hwnd, IDC_EDIT, buf);
}

//the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

  switch(msg) {
    case WM_CREATE:
    {

      #define errorIfNull(x) if (NULL==x) MessageBox(hwnd, "Error: WM_CREATE", "Error", MB_OK | MB_ICONERROR);

      #define makeButton(name,id,x,y,w,h) errorIfNull(CreateWindow("BUTTON",name,WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, x,y,w,h, hwnd,(HMENU)(id),GetModuleHandle(NULL),NULL))

      errorIfNull(CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "0",        // default text
        WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_RIGHT | ES_READONLY, // Disabled, right align
        10,         // x position
        10,         // y position
        206,        // width
        25,         // height
        hwnd,       // Parent window
        (HMENU)IDC_EDIT,  // menu handle = ID
        GetModuleHandle(NULL), NULL));

      makeButton(".",99, 94,178,36,36);
      makeButton("0",100,10,178,78,36);
      makeButton("1",101,10,136,36,36);
      makeButton("2",102,52,136,36,36);
      makeButton("3",103,94,136,36,36);
      makeButton("4",104,10,94,36,36);
      makeButton("5",105,52,94,36,36);
      makeButton("6",106,94,94,36,36);
      makeButton("7",107,10,52,36,36);
      makeButton("8",108,52,52,36,36);
      makeButton("9",109,94,52,36,36);

      makeButton("+",110,136,178,36,36);
      makeButton("-",111,136,136,36,36);
      makeButton("*",112,136,94,36,36);
      makeButton("/",113,136,52,36,36);

      makeButton("=",114,178,136,36,78);
      makeButton("C",115,178,94,36,36);

    }
    break;
    case WM_KEYUP:
      if (wParam==VK_SHIFT) shift=0;
    break;

    case  WM_KEYDOWN :
      if (shift) {
        if (wParam==0x38) wParam=112; // shift 8 = multiply
        else if (wParam==0xbb) wParam=110;
        else break;
      } else {
        if (wParam>=0x30 && wParam <=0x39) {
          wParam+= 100-0x30;
        } else if (wParam>=0x60 && wParam <=0x69) { //numpad
          wParam+= 100-0x60;
        } else switch (wParam){
          case VK_SHIFT: shift=1; return 0;
          case VK_MULTIPLY: wParam =112; break;
          case VK_SUBTRACT: case 0xbd: wParam =111; break;
          case VK_ADD: wParam =110; break;
          case VK_DIVIDE: case 0xbf: wParam =113; break;
          case VK_DECIMAL: case 0xbe: wParam =99; break;
          case VK_RETURN: case 0xbb: wParam = 114; break;
          case 0x2e: wParam = 115; break;

          default:
            return 0;
        }
      }

    // break; Fall through
    case WM_COMMAND:
    {
      switch (wParam) {
        case 99:
          if (typing==2) break;

        case 109:case 108:case 107:case 106:case 105:case 104:case 103:case 102:case 101:case 100:
        {
          char out[32];
          int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT));

          if (typing) {
            GetDlgItemText(hwnd, IDC_EDIT, out, len+1);
          } else {
            typing=1;
            len=0;
          }
          if (len<=16) {
            if (wParam==99) {
              if (len==0) out[len++]='0';
              out[len]='.';
              typing=2;
            } else out[len] = '0'+(wParam-100);
            out[len+1] =0;
            SetDlgItemText(hwnd, IDC_EDIT, out);
          }

          if (final) op=0;
          final=0;

        }
        break;
        case 111:
        case 110:
        case 112:
        case 113:
          if (typing && op) {
            num2 = getScreen(hwnd);
            equate(hwnd);
          } else num1 = getScreen(hwnd);
          typing=0;
          op=wParam;
          final=0;

        break;
        case 114: // =
          if (!op) break;
          if (typing)
            num2 = getScreen(hwnd);
          typing=0;

          equate(hwnd);
          final=1;

        break;
        case 115: // Clear
          num1=0.0;
          num2=0.0;
          op=0;
          final=0;
          typing=0;
          SetDlgItemText(hwnd, IDC_EDIT, "0");
        break;
      }
    }
    break;
    case WM_CLOSE:
      DestroyWindow(hwnd);
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASSEX wc;
  HWND hwnd;
  MSG Msg;

  wc.cbSize    = sizeof(WNDCLASSEX);
  wc.style     = 0;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra  = 0;
  wc.cbWndExtra  = 0;
  wc.hInstance   = hInstance;
  wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor     = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = windowClassName;
  wc.hIconSm     = LoadIcon(NULL, IDI_APPLICATION);

  if(!RegisterClassEx(&wc)) {
    MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  hwnd = CreateWindowEx(
    0,
    windowClassName,
    "Simple Calculator but code is ...",
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT, CW_USEDEFAULT, 231, 250,
    NULL, NULL, hInstance, NULL);

  if(hwnd == NULL) {
    MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  while(GetMessage(&Msg, NULL, 0, 0) > 0) {
    if (Msg.message == WM_KEYDOWN || Msg.message == WM_KEYUP) Msg.hwnd = hwnd;
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }
  return Msg.wParam;
}