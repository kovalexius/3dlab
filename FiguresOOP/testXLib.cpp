#include "testXLib.h"

#ifdef __linux__
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int testXLib(int argc, char **argv)
{
	Display *ourDisplay;
	int ourScreen;
	Window  myWindow, rootWindow, childWindow;
	unsigned long bgcolor;
	int myDepth;
	XSetWindowAttributes myAttr;
	Visual *myVisual;
	XSizeHints mySizeHints;
	XClassHint myClassHint;
	char *myPropertyData;
	char *myClassName = "example";
	char *myResName = "example";
	char *iconName;

	ourDisplay = XOpenDisplay(NULL);
	if (ourDisplay == NULL)
	{
		printf("�� ������� ���������� ���������� � ����������� ����������.\n");
		return 1;
	};

	/* ������� ��������������� �������� */
	ourScreen = DefaultScreen(ourDisplay);           /* ����� ��-���������        */
	rootWindow = RootWindow(ourDisplay, ourScreen);  /* �������� ����             */
	bgcolor = WhitePixel(ourDisplay, ourScreen);     /* ����� ���� ������         */
	myDepth = DefaultDepth(ourDisplay, ourScreen);   /* ������� ��������� ������  */
	myVisual = DefaultVisual(ourDisplay, ourScreen); /* ���������� �������������� */

	/* ��������� �������� ���� */
	myAttr.background_pixel = bgcolor;

	/* ������� ���� */
	myWindow = XCreateWindow(ourDisplay, rootWindow, 100, 100, 320, 200,
		0, myDepth, InputOutput, myVisual, CWBackPixel, &myAttr);

	/* ������������� ��������� ���� */
	XStoreName(ourDisplay, myWindow, "Example window");

	/* ������������� ��������� ������ */
	XSetIconName(ourDisplay, myWindow, "example");

	/* ������������� ����������� �� ������� ���� */
	mySizeHints.flags = PMinSize | PMaxSize | PResizeInc;
	mySizeHints.min_width = 192; mySizeHints.min_height = 128;
	mySizeHints.max_width = 640; mySizeHints.max_height = 480;
	mySizeHints.width_inc = 10; mySizeHints.height_inc = 10;
	XSetWMNormalHints(ourDisplay, myWindow, &mySizeHints);

	/* ������������� ������� ��������� ������ */
	XSetCommand(ourDisplay, myWindow, argv, argc);

	/* ������������� ������� ������ */
	myClassHint.res_name = myResName;
	myClassHint.res_class = myClassName;
	XSetClassHint(ourDisplay, myWindow, &myClassHint);

	/* ������ �������� ���� */
	myAttr.background_pixel = BlackPixel(ourDisplay, ourScreen);
	childWindow = XCreateWindow(ourDisplay, myWindow, 10, 10, 40, 30,
		0, myDepth, InputOutput, myVisual, CWBackPixel, &myAttr);

	myAttr.win_gravity = NorthEastGravity;
	childWindow = XCreateWindow(ourDisplay, myWindow, 270, 10, 40, 30,
		0, myDepth, InputOutput, myVisual, CWBackPixel | CWWinGravity, &myAttr);

	myAttr.win_gravity = SouthWestGravity;
	childWindow = XCreateWindow(ourDisplay, myWindow, 10, 160, 40, 30,
		0, myDepth, InputOutput, myVisual, CWBackPixel | CWWinGravity, &myAttr);

	myAttr.win_gravity = SouthEastGravity;
	childWindow = XCreateWindow(ourDisplay, myWindow, 270, 160, 40, 30,
		0, myDepth, InputOutput, myVisual, CWBackPixel | CWWinGravity, &myAttr);

	myAttr.win_gravity = CenterGravity;
	childWindow = XCreateWindow(ourDisplay, myWindow, 140, 85, 40, 30,
		0, myDepth, InputOutput, myVisual, CWBackPixel | CWWinGravity, &myAttr);

	/* ������ ���� �������� */
	XMapWindow(ourDisplay, myWindow);
	XMapSubwindows(ourDisplay, myWindow);

	/* ��� �������������� ������� ������������� ���������� �� ������ */
	XFlush(ourDisplay);

	/* ���� 50 ������ */
	sleep(10);

	/* ���������� ���� */
	XDestroyWindow(ourDisplay, myWindow);

	/* ��������� ���������� � �������� */
	XCloseDisplay(ourDisplay);

	return 0;
}

#else

int testXLib(int argc, char **argv)
{
	return 0;
}

#endif