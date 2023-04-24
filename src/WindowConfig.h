#ifndef __WINDOWCONFIG_H__
#define __WINDOWCONFIG_H__

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD03 Ex01";
static float aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 20.;

#endif